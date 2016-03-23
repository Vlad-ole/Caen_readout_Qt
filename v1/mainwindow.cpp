#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "WaveDump.h"
#include "WDplot.h"
#include "WDconfig.h"
#include "X742CorrectionRoutines.h"
#include "fft.h"

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox_3->setEnabled(false);
    ui->groupBox_6->setEnabled(false);
    ui->groupBox_7->setEnabled(false);
    ui->pushButton->setStyleSheet("background-color: red");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int argc = 1;
    char* argv[0] = {};

    WaveDumpConfig_t   WDcfg;
    WaveDumpRun_t      WDrun;

    CAEN_DGTZ_ErrorCode ret=0;
    int  handle;

    //ret=0;

    ERROR_CODES ErrCode= ERR_NONE;
    int i, ch, Nb=0, Ne=0;

    uint32_t AllocatedSize, BufferSize, NumEvents;
//    uint32_t AllocatedSize;
//    uint32_t BufferSize;
//    uint32_t NumEvents;


    char *buffer = NULL;
    //*buffer = NULL;

    char *EventPtr = NULL;
    char ConfigFileName[100];
    int isVMEDevice= 0, MajorNumber;
    uint64_t CurrentTime, PrevRateTime, ElapsedTime;
    int nCycles= 0;
    CAEN_DGTZ_BoardInfo_t       BoardInfo;
    CAEN_DGTZ_EventInfo_t       EventInfo;

    CAEN_DGTZ_UINT16_EVENT_t    *Event16=NULL; /* generic event struct with 16 bit data (10, 12, 14 and 16 bit digitizers */

    CAEN_DGTZ_UINT8_EVENT_t     *Event8=NULL; /* generic event struct with 8 bit data (only for 8 bit digitizers) */
    CAEN_DGTZ_X742_EVENT_t       *Event742=NULL;  /* custom event struct with 8 bit data (only for 8 bit digitizers) */
    WDPlot_t                    *PlotVar=NULL;
    FILE *f_ini;
    CAEN_DGTZ_DRS4Correction_t X742Tables[MAX_X742_GROUP_SIZE];

    int ReloadCfgStatus = 0x7FFFFFFF; // Init to the bigger positive number

    printf("\n");
    printf("**************************************************************\n");
    printf("                        Wave Dump %s\n", WaveDump_Release);
    printf("**************************************************************\n");

    printf("text");

    /* *************************************************************************************** */
    /* Open and parse configuration file                                                       */
    /* *************************************************************************************** */
    memset(&WDrun, 0, sizeof(WDrun));
    if (argc > 1)
        strcpy(ConfigFileName, argv[1]);
    else
        strcpy(ConfigFileName, DEFAULT_CONFIG_FILE);
    printf("Opening Configuration File %s\n", ConfigFileName);
    f_ini = fopen(ConfigFileName, "r");
    if (f_ini == NULL ) {
        ErrCode = ERR_CONF_FILE_NOT_FOUND;
        goto QuitProgram;
    }
    ParseConfigFile(f_ini, &WDcfg);
    fclose(f_ini);


    /* *************************************************************************************** */
    /* Open the digitizer and read the board information                                       */
    /* *************************************************************************************** */
    isVMEDevice = WDcfg.BaseAddress ? 1 : 0;

    ret = CAEN_DGTZ_OpenDigitizer(WDcfg.LinkType, WDcfg.LinkNum, WDcfg.ConetNode, WDcfg.BaseAddress, &handle);
    if (ret) {
        ErrCode = ERR_DGZ_OPEN;
        goto QuitProgram;
    }

    ret = CAEN_DGTZ_GetInfo(handle, &BoardInfo);
    if (ret) {
        ErrCode = ERR_BOARD_INFO_READ;
        goto QuitProgram;
    }
    printf("Connected to CAEN Digitizer Model %s\n", BoardInfo.ModelName);
    printf("ROC FPGA Release is %s\n", BoardInfo.ROC_FirmwareRel);
    printf("AMC FPGA Release is %s\n", BoardInfo.AMC_FirmwareRel);


    // Check firmware rivision (DPP firmwares cannot be used with WaveDump */
    sscanf(BoardInfo.AMC_FirmwareRel, "%d", &MajorNumber);
    if (MajorNumber >= 128) {
        printf("This digitizer has a DPP firmware\n");
        ErrCode = ERR_INVALID_BOARD_TYPE;
        goto QuitProgram;
    }

    // Get Number of Channels, Number of bits, Number of Groups of the board */
    ret = GetMoreBoardInfo(handle, BoardInfo, &WDcfg);
    if (ret) {
        ErrCode = ERR_INVALID_BOARD_TYPE;
        goto QuitProgram;
    }

Restart:
    // mask the channels not available for this model
    if ((BoardInfo.FamilyCode != CAEN_DGTZ_XX740_FAMILY_CODE) && (BoardInfo.FamilyCode != CAEN_DGTZ_XX742_FAMILY_CODE)){
        WDcfg.EnableMask &= (1<<WDcfg.Nch)-1;
    } else {
        WDcfg.EnableMask &= (1<<(WDcfg.Nch/8))-1;
    }
    if ((BoardInfo.FamilyCode == CAEN_DGTZ_XX751_FAMILY_CODE) && WDcfg.DesMode) {
        WDcfg.EnableMask &= 0xAA;
    }
    if ((BoardInfo.FamilyCode == CAEN_DGTZ_XX731_FAMILY_CODE) && WDcfg.DesMode) {
        WDcfg.EnableMask &= 0x55;
    }
    // Set plot mask
    if ((BoardInfo.FamilyCode != CAEN_DGTZ_XX740_FAMILY_CODE) && (BoardInfo.FamilyCode != CAEN_DGTZ_XX742_FAMILY_CODE)){
        WDrun.ChannelPlotMask = WDcfg.EnableMask;
    } else {
        WDrun.ChannelPlotMask = (WDcfg.FastTriggerEnabled == 0) ? 0xFF: 0x1FF;
    }

    /* *************************************************************************************** */
    /* program the digitizer                                                                   */
    /* *************************************************************************************** */
    ret = ProgramDigitizer(handle, WDcfg, BoardInfo);
    if (ret) {
        ErrCode = ERR_DGZ_PROGRAM;
        goto QuitProgram;
    }

    // Select the next enabled group for plotting
    if ((WDcfg.EnableMask) && (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE))
        if( ((WDcfg.EnableMask>>WDrun.GroupPlotIndex)&0x1)==0 )
            GoToNextEnabledGroup(&WDrun, &WDcfg);

    // Read again the board infos, just in case some of them were changed by the programming
    // (like, for example, the TSample and the number of channels if DES mode is changed)
    if(ReloadCfgStatus > 0) {
        ret = CAEN_DGTZ_GetInfo(handle, &BoardInfo);
        if (ret) {
            ErrCode = ERR_BOARD_INFO_READ;
            goto QuitProgram;
        }
        ret = GetMoreBoardInfo(handle,BoardInfo, &WDcfg);
        if (ret) {
            ErrCode = ERR_INVALID_BOARD_TYPE;
            goto QuitProgram;
        }

        // Reload Correction Tables if changed
        if(BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE && (ReloadCfgStatus & (0x1 << CFGRELOAD_CORRTABLES_BIT)) ) {
            if(WDcfg.useCorrections != -1) { // Use Manual Corrections
                uint32_t GroupMask = 0;

                // Disable Automatic Corrections
                if ((ret = CAEN_DGTZ_DisableDRS4Correction(handle)) != CAEN_DGTZ_Success)
                    goto QuitProgram;

                // Load the Correction Tables from the Digitizer flash
                if ((ret = CAEN_DGTZ_GetCorrectionTables(handle, WDcfg.DRS4Frequency, (void*)X742Tables)) != CAEN_DGTZ_Success)
                    goto QuitProgram;

                if(WDcfg.UseManualTables != -1) { // The user wants to use some custom tables
                    uint32_t gr;
                    GroupMask = WDcfg.UseManualTables;

                    for(gr = 0; gr < WDcfg.MaxGroupNumber; gr++) {
                        if (((GroupMask>>gr)&0x1) == 0)
                            continue;
                        LoadCorrectionTable(WDcfg.TablesFilenames[gr], &(X742Tables[gr]));
                    }
                }
                // Save to file the Tables read from flash
                GroupMask = (~GroupMask) & ((0x1<<WDcfg.MaxGroupNumber)-1);
                SaveCorrectionTables("X742Table", GroupMask, X742Tables);
            }
            else { // Use Automatic Corrections
                if ((ret = CAEN_DGTZ_LoadDRS4CorrectionData(handle, WDcfg.DRS4Frequency)) != CAEN_DGTZ_Success)
                    goto QuitProgram;
                if ((ret = CAEN_DGTZ_EnableDRS4Correction(handle)) != CAEN_DGTZ_Success)
                    goto QuitProgram;
            }
        }
    }

    // Allocate memory for the event data and readout buffer
    if(WDcfg.Nbit == 8)
        ret = CAEN_DGTZ_AllocateEvent(handle, (void**)&Event8);
    else {
        if (BoardInfo.FamilyCode != CAEN_DGTZ_XX742_FAMILY_CODE) {
            ret = CAEN_DGTZ_AllocateEvent(handle, (void**)&Event16);
        }
        else {
            ret = CAEN_DGTZ_AllocateEvent(handle, (void**)&Event742);
        }
    }
    if (ret != CAEN_DGTZ_Success) {
        ErrCode = ERR_MALLOC;
        goto QuitProgram;
    }
    ret = CAEN_DGTZ_MallocReadoutBuffer(handle, &buffer,&AllocatedSize); /* WARNING: This malloc must be done after the digitizer programming */
    if (ret) {
        ErrCode = ERR_MALLOC;
        goto QuitProgram;
    }







    //if (WDcfg.TestPattern) CAEN_DGTZ_DisableDRS4Correction(handle);
    //else CAEN_DGTZ_EnableDRS4Correction(handle);

    if (WDrun.Restart && WDrun.AcqRun)
        CAEN_DGTZ_SWStartAcquisition(handle);
    else
        printf("[s] start/stop the acquisition, [q] quit, [SPACE] help\n");
    WDrun.Restart = 0;
    PrevRateTime = get_time();



    ui->textBrowser->setText("Device was connected");

    ui->groupBox_3->setEnabled(true);
    ui->groupBox_6->setEnabled(true);
    ui->groupBox_7->setEnabled(true);
    ui->radioButton_13->setChecked(true);
    ui->pushButton->setStyleSheet("background-color: green");
    ui->pushButton->setEnabled(false);

{
    //Рисуем график y=x*x

        //Сгенерируем данные
        //Для этого создадим два массива точек:
        //один для созранения x координат точек,
        //а второй для y соответственно

        double a = -1; //Начало интервала, где рисуем график по оси Ox
        double b =  1; //Конец интервала, где рисуем график по оси Ox
        double h = 0.01; //Шаг, с которым будем пробегать по оси Ox

        int N=(b-a)/h + 2; //Вычисляем количество точек, которые будем отрисовывать
        QVector<double> x(N), y(N); //Массивы координат точек

        //Вычисляем наши данные
        int i=0;
        for (double X=a; X<=b; X+=h)//Пробегаем по всем точкам
        {
            x[i] = X;
            y[i] = X*X;//Формула нашей функции
            i++;
        }

        ui->widget_011->clearGraphs();//Если нужно, но очищаем все графики
        //Добавляем один график в widget
        ui->widget_011->addGraph();
        //Говорим, что отрисовать нужно график по нашим двум массивам x и y
        ui->widget_011->graph(0)->setData(x, y);

        //Подписываем оси Ox и Oy
        ui->widget_011->xAxis->setLabel("time [us]");
        ui->widget_011->yAxis->setLabel("Amplitude [V]");

        //Установим область, которая будет показываться на графике
        ui->widget_011->xAxis->setRange(a, b);//Для оси Ox

        //Для показа границ по оси Oy сложнее, так как надо по правильному
        //вычислить минимальное и максимальное значение в векторах
        double minY = y[0], maxY = y[0];
        for (int i=1; i<N; i++)
        {
            if (y[i]<minY) minY = y[i];
            if (y[i]>maxY) maxY = y[i];
        }
        ui->widget_011->yAxis->setRange(minY, maxY);//Для оси Oy

        //И перерисуем график на нашем widget
        ui->widget_011->replot();

}










QuitProgram:
    if (ErrCode) {
        printf("\a%s\n", ErrMsg[ErrCode]);
        ui->textBrowser->setText(ErrMsg[ErrCode]);
#ifdef WIN32
        printf("Press a key to quit\n");
        getch();
#endif
    }

    /* stop the acquisition */
    CAEN_DGTZ_SWStopAcquisition(handle);

    /* close the plotter */
    if (PlotVar)
        ClosePlotter();

    /* close the output files and free histograms*/
    for(ch=0; ch<WDcfg.Nch; ch++) {
        if( WDrun.fout[ch])
            fclose(WDrun.fout[ch]);
        if( WDrun.Histogram[ch])
            free(WDrun.Histogram[ch]);
    }

    /* close the device and free the buffers */
    if(Event8)
        CAEN_DGTZ_FreeEvent(handle, (void**)&Event8);
    if(Event16)
        CAEN_DGTZ_FreeEvent(handle, (void**)&Event16);
    CAEN_DGTZ_FreeReadoutBuffer(&buffer);
    CAEN_DGTZ_CloseDigitizer(handle);

    //ui->label_3->setText("I work correct!");

}

void MainWindow::on_radioButton_13_clicked()
{
    ui->spinBox_2->setEnabled(true);
    ui->groupBox_2->setEnabled(true);
}

void MainWindow::on_radioButton_12_clicked()
{
    ui->spinBox_2->setEnabled(false);
    ui->groupBox_2->setEnabled(false);
}

void MainWindow::on_checkBox_clicked()
{

}

void MainWindow::on_spinBox_3_valueChanged(int arg1)
{

}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    ui->widget_011->yAxis->setRangeUpper(arg1);
    ui->widget_012->yAxis->setRangeUpper(arg1);
    ui->widget_013->yAxis->setRangeUpper(arg1);
    ui->widget_014->yAxis->setRangeUpper(arg1);
    ui->widget_015->yAxis->setRangeUpper(arg1);

    ui->widget_021->yAxis->setRangeUpper(arg1);
    ui->widget_022->yAxis->setRangeUpper(arg1);
    ui->widget_023->yAxis->setRangeUpper(arg1);
    ui->widget_024->yAxis->setRangeUpper(arg1);
    ui->widget_025->yAxis->setRangeUpper(arg1);

    ui->widget_031->yAxis->setRangeUpper(arg1);
    ui->widget_032->yAxis->setRangeUpper(arg1);
    ui->widget_033->yAxis->setRangeUpper(arg1);
    ui->widget_034->yAxis->setRangeUpper(arg1);
    ui->widget_035->yAxis->setRangeUpper(arg1);

    ui->widget_041->yAxis->setRangeUpper(arg1);
    ui->widget_042->yAxis->setRangeUpper(arg1);
    ui->widget_043->yAxis->setRangeUpper(arg1);
    ui->widget_044->yAxis->setRangeUpper(arg1);
    ui->widget_045->yAxis->setRangeUpper(arg1);

    ui->widget_051->yAxis->setRangeUpper(arg1);
    ui->widget_052->yAxis->setRangeUpper(arg1);
    ui->widget_053->yAxis->setRangeUpper(arg1);
    ui->widget_054->yAxis->setRangeUpper(arg1);
    ui->widget_055->yAxis->setRangeUpper(arg1);

    ui->widget_011->replot();
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    ui->widget_011->yAxis->setRangeLower(arg1);
    ui->widget_012->yAxis->setRangeLower(arg1);
    ui->widget_013->yAxis->setRangeLower(arg1);
    ui->widget_014->yAxis->setRangeLower(arg1);
    ui->widget_015->yAxis->setRangeLower(arg1);

    ui->widget_021->yAxis->setRangeLower(arg1);
    ui->widget_022->yAxis->setRangeLower(arg1);
    ui->widget_023->yAxis->setRangeLower(arg1);
    ui->widget_024->yAxis->setRangeLower(arg1);
    ui->widget_025->yAxis->setRangeLower(arg1);

    ui->widget_031->yAxis->setRangeLower(arg1);
    ui->widget_032->yAxis->setRangeLower(arg1);
    ui->widget_033->yAxis->setRangeLower(arg1);
    ui->widget_034->yAxis->setRangeLower(arg1);
    ui->widget_035->yAxis->setRangeLower(arg1);

    ui->widget_041->yAxis->setRangeLower(arg1);
    ui->widget_042->yAxis->setRangeLower(arg1);
    ui->widget_043->yAxis->setRangeLower(arg1);
    ui->widget_044->yAxis->setRangeLower(arg1);
    ui->widget_045->yAxis->setRangeLower(arg1);

    ui->widget_051->yAxis->setRangeLower(arg1);
    ui->widget_052->yAxis->setRangeLower(arg1);
    ui->widget_053->yAxis->setRangeLower(arg1);
    ui->widget_054->yAxis->setRangeLower(arg1);
    ui->widget_055->yAxis->setRangeLower(arg1);

    ui->widget_011->replot();
}

void MainWindow::on_spinBox_4_valueChanged(int arg1)
{
    const double sampling_rate = 4; // ns

    ui->widget_011->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_012->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_013->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_014->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_015->xAxis->setRange(0, arg1*4.0/1000);

    ui->widget_021->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_022->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_023->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_024->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_025->xAxis->setRange(0, arg1*4.0/1000);

    ui->widget_031->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_032->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_033->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_034->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_035->xAxis->setRange(0, arg1*4.0/1000);

    ui->widget_041->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_042->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_043->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_044->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_045->xAxis->setRange(0, arg1*4.0/1000);

    ui->widget_051->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_052->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_053->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_054->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_055->xAxis->setRange(0, arg1*4.0/1000);


    ui->widget_011->replot();
}

void MainWindow::on_radioButton_15_clicked(bool checked)
{
    //CAEN_DGTZ_SendSWtrigger(handle);
}


void MainWindow::on_pushButton_2_clicked()
{
    /* Read data from the board */
    //ret = CAEN_DGTZ_ReadData(handle, CAEN_DGTZ_SLAVE_TERMINATED_READOUT_MBLT, buffer, &BufferSize);
}
