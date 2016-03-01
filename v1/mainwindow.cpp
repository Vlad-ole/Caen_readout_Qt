#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "WaveDump.h"
#include "WDplot.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    WaveDumpConfig_t   WDcfg;
    WaveDumpRun_t      WDrun;
    CAEN_DGTZ_ErrorCode ret=0;
    int  handle;
    ERROR_CODES ErrCode= ERR_NONE;
    int i, ch, Nb=0, Ne=0;
    uint32_t AllocatedSize, BufferSize, NumEvents;
    char *buffer = NULL;
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

//    /* *************************************************************************************** */
//    /* Open and parse configuration file                                                       */
//    /* *************************************************************************************** */
//    memset(&WDrun, 0, sizeof(WDrun));
//    if (argc > 1)
//        strcpy(ConfigFileName, argv[1]);
//    else
//        strcpy(ConfigFileName, DEFAULT_CONFIG_FILE);
//    printf("Opening Configuration File %s\n", ConfigFileName);
//    f_ini = fopen(ConfigFileName, "r");
//    if (f_ini == NULL ) {
//        ErrCode = ERR_CONF_FILE_NOT_FOUND;
//        goto QuitProgram;
//    }
//    ParseConfigFile(f_ini, &WDcfg);
//    fclose(f_ini);

    ui->label_3->setText("I work correct!");

}
