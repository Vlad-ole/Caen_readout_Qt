#include "myworker.h"
#include <QtCore>
#include <QThread>

MyWorker::MyWorker()
{

}

void MyWorker::Init()
{
    qDebug() << "Thread in Init() is " << QThread::currentThreadId();


    int argc_my = 1;
    char* argv_my[0] = {};

    //my variant.
    //---------------------------------------------------------------
    /* *************************************************************************************** */
    /* initialization                                                      */
    /* *************************************************************************************** */
    ret=0;
    ErrCode = ERR_NONE;
    Nb=0, Ne=0;
    buffer = NULL;
    EventPtr = NULL;
    isVMEDevice= 0;
    nCycles = 0;
    Event16=NULL; /* generic event struct with 16 bit data (10, 12, 14 and 16 bit digitizers */
    Event8 = NULL; /* generic event struct with 8 bit data (only for 8 bit digitizers) */
    Event742 = NULL;  /* custom event struct with 8 bit data (only for 8 bit digitizers) */
    PlotVar = NULL;
    ReloadCfgStatus = 0x7FFFFFFF; // Init to the bigger positive number
    //---------------------------------------------------------------


    printf("\n");
    printf("**************************************************************\n");
    printf("                        Wave Dump %s\n", WaveDump_Release);
    printf("**************************************************************\n");

    printf("text");
    /* *************************************************************************************** */
    /*  end initialization                                                      */
    /* *************************************************************************************** */





    /* *************************************************************************************** */
    /* Open and parse configuration file                                                       */
    /* *************************************************************************************** */
    memset(&WDrun, 0, sizeof(WDrun));
    if (argc_my > 1)
        strcpy(ConfigFileName, argv_my[1]);
    else
        strcpy(ConfigFileName, DEFAULT_CONFIG_FILE);
    printf("Opening Configuration File %s\n", ConfigFileName);
    f_ini = fopen(ConfigFileName, "r");
    if (f_ini == NULL )
    {
        ErrCode = ERR_CONF_FILE_NOT_FOUND;
        //goto QuitProgram;
        QuitProgram();
        return;
    }
    ParseConfigFile(f_ini, &WDcfg);
    fclose(f_ini);


    /* *************************************************************************************** */
    /* Open the digitizer and read the board information                                       */
    /* *************************************************************************************** */
    isVMEDevice = WDcfg.BaseAddress ? 1 : 0;

    ret = CAEN_DGTZ_OpenDigitizer(WDcfg.LinkType, WDcfg.LinkNum, WDcfg.ConetNode, WDcfg.BaseAddress, &handle);
    if (ret)
    {
        ErrCode = ERR_DGZ_OPEN;
        //goto QuitProgram;
        QuitProgram();
        //QThread::sleep(5);
        return;
    }

    qDebug() << "handle " << handle;

    ret = CAEN_DGTZ_GetInfo(handle, &BoardInfo);
    if (ret) {
        ErrCode = ERR_BOARD_INFO_READ;
        //goto QuitProgram;
        QuitProgram();
        return;
    }
    printf("Connected to CAEN Digitizer Model %s\n", BoardInfo.ModelName);
    printf("ROC FPGA Release is %s\n", BoardInfo.ROC_FirmwareRel);
    printf("AMC FPGA Release is %s\n", BoardInfo.AMC_FirmwareRel);


    // Check firmware rivision (DPP firmwares cannot be used with WaveDump */
    sscanf(BoardInfo.AMC_FirmwareRel, "%d", &MajorNumber);
    if (MajorNumber >= 128) {
        printf("This digitizer has a DPP firmware\n");
        ErrCode = ERR_INVALID_BOARD_TYPE;
        //goto QuitProgram;
        QuitProgram();
        return;
    }

    // Get Number of Channels, Number of bits, Number of Groups of the board */
    ret = GetMoreBoardInfo(handle, BoardInfo, &WDcfg);
    if (ret)
    {
        ErrCode = ERR_INVALID_BOARD_TYPE;
        //goto QuitProgram;
        QuitProgram();
        return;
    }

    Mask_the_channels();
    Program_the_digitizer();


//    for(int i=0; i < 10000000; i++)
//    {
//        double a = log( exp(i) * sin(i) ) * sin(log( exp(i) * sin(i) ));

//    }

    emit this->InitializationComplete();

}

void MyWorker::StopReadout_loop()
{
    WDrun.Quit = 1;
    qDebug() << "in StopReadout_loop() " << endl;
    qDebug() << "WDrun.Quit = " << WDrun.Quit << endl;
}

void MyWorker::Readout_loop()
{
//    qDebug() << "in Readout_loop() " << endl;

//    CAEN_DGTZ_SendSWtrigger(handle);
//    ret = CAEN_DGTZ_ReadData(handle, CAEN_DGTZ_SLAVE_TERMINATED_READOUT_MBLT, buffer, &BufferSize);
//    if (ret)
//    {
//        ErrCode = ERR_READOUT;
//        //goto QuitProgram;
//        QuitProgram();
//        return;
//    }

//    qDebug() << "BufferSize " << BufferSize << endl;





        qDebug() << "in Readout_loop() " << endl;
    //qDebug() << "WDrun.Quit = " << WDrun.Quit << endl;

    WDrun.Quit = 0;

    //QElapsedTimer timer;
    //timer.start();

    //bool time_flag = true;
    //long int previous_time = 0;

    while(!WDrun.Quit)
    {

        /* Send a software trigger */
        if (WDrun.ContinuousTrigger)
        {
            CAEN_DGTZ_SendSWtrigger(handle);
            //qDebug() << "Continuous trigger is enabled\n";
        }

        /* Read data from the board */
        ret = CAEN_DGTZ_ReadData(handle, CAEN_DGTZ_SLAVE_TERMINATED_READOUT_MBLT, buffer, &BufferSize);
        if (ret)
        {
            ErrCode = ERR_READOUT;
            //goto QuitProgram;
            QuitProgram();
            return;
        }



        NumEvents = 0;
        if (BufferSize != 0)
        {
            ret = CAEN_DGTZ_GetNumEvents(handle, buffer, BufferSize, &NumEvents);
            if (ret)
            {
                ErrCode = ERR_READOUT;
                //goto QuitProgram;
                QuitProgram();
                return;
            }
        }
        else
        {
            uint32_t lstatus;
            ret = CAEN_DGTZ_ReadRegister(handle, CAEN_DGTZ_ACQ_STATUS_ADD, &lstatus);
            if (lstatus & (0x1 << 19))
            {
                ErrCode = ERR_OVERTEMP;
                //goto QuitProgram;
                QuitProgram();
                return;
            }
        }

        /* Calculate throughput and trigger rate (every second) */
        Nb += BufferSize;
        Ne += NumEvents;
        CurrentTime = get_time();
        ElapsedTime = CurrentTime - PrevRateTime;

        nCycles++;

        if( ElapsedTime >= 1000)
        {
            //qDebug() << "time[s] = " << ElapsedTime / 1000.0 << endl;
            emit this->RedrawGraphs();

           qDebug() << "WDcfg.InterruptNumEvents " << WDcfg.InterruptNumEvents;
           qDebug() << "BufferSize " << BufferSize ;
           qDebug() << "handle " << handle;


            if (WDrun.ContinuousTrigger)
                qDebug() << "Continuous trigger is enabled\n";
            else
                qDebug() << "Continuous trigger is disabled\n";

            if (Nb == 0)
            {
                if (ret == CAEN_DGTZ_Timeout)
                {
                    printf ("Timeout...\n");
                }
                else
                {
                    //printf("No data...\n");
                    qDebug() << "No data...\n";
                }
            }
            else
            {
                //printf("Reading at %.2f MB/s (Trg Rate: %.2f Hz)\n", (float)Nb/((float)ElapsedTime*1048.576f), (float)Ne*1000.0f/(float)ElapsedTime);
                qDebug() << "Reading at"  << endl;
            }

            nCycles= 0;
            Nb = 0;
            Ne = 0;
            PrevRateTime = CurrentTime;
        }

    }

}

void MyWorker::ContinuousTrigger()
{
     //WDrun.ContinuousTrigger = 1;
    WDrun.ContinuousTrigger ^= 1;
}



void MyWorker::Restart()
{
    Mask_the_channels();
    Program_the_digitizer();
}

void MyWorker::Mask_the_channels()
{
    qDebug() << "Thread in Mask_the_channels() is " << QThread::currentThreadId();

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
}

void MyWorker::Program_the_digitizer()
{
    qDebug() << "Thread in Program_the_digitizer() is " << QThread::currentThreadId();

    /* *************************************************************************************** */
    /* program the digitizer                                                                   */
    /* *************************************************************************************** */
    ret = ProgramDigitizer(handle, WDcfg, BoardInfo);
    if (ret) {
        ErrCode = ERR_DGZ_PROGRAM;
        //goto QuitProgram;
        QuitProgram();
        return;
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
            //goto QuitProgram;
            QuitProgram();
            return;
        }
        ret = GetMoreBoardInfo(handle,BoardInfo, &WDcfg);
        if (ret) {
            ErrCode = ERR_INVALID_BOARD_TYPE;
            //goto QuitProgram;
            QuitProgram();
            return;
        }

        // Reload Correction Tables if changed
        if(BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE && (ReloadCfgStatus & (0x1 << CFGRELOAD_CORRTABLES_BIT)) ) {
            if(WDcfg.useCorrections != -1) { // Use Manual Corrections
                uint32_t GroupMask = 0;

                // Disable Automatic Corrections
                if ((ret = CAEN_DGTZ_DisableDRS4Correction(handle)) != CAEN_DGTZ_Success)
                {
                    //goto QuitProgram;
                    QuitProgram();
                    return;
                }

                // Load the Correction Tables from the Digitizer flash
                if ((ret = CAEN_DGTZ_GetCorrectionTables(handle, WDcfg.DRS4Frequency, (void*)X742Tables)) != CAEN_DGTZ_Success)
                {
                    //goto QuitProgram;
                    QuitProgram();
                    return;
                }

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
                {
                    //goto QuitProgram;
                    QuitProgram();
                    return;
                }
                if ((ret = CAEN_DGTZ_EnableDRS4Correction(handle)) != CAEN_DGTZ_Success)
                {
                   // goto QuitProgram;
                    QuitProgram();
                    return;
                }
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
        //goto QuitProgram;
        QuitProgram();
        return;
    }
    ret = CAEN_DGTZ_MallocReadoutBuffer(handle, &buffer,&AllocatedSize); /* WARNING: This malloc must be done after the digitizer programming */
    if (ret) {
        ErrCode = ERR_MALLOC;
        //goto QuitProgram;
        QuitProgram();
        return;
    }

    //if (WDcfg.TestPattern) CAEN_DGTZ_DisableDRS4Correction(handle);
    //else CAEN_DGTZ_EnableDRS4Correction(handle);

    if (WDrun.Restart && WDrun.AcqRun)
        CAEN_DGTZ_SWStartAcquisition(handle);
    else
        printf("[s] start/stop the acquisition, [q] quit, [SPACE] help\n");
    WDrun.Restart = 0;
    PrevRateTime = get_time();
    /* *************************************************************************************** */
    /* *************************************************************************************** */
    /* end program the digitizer                                                                   */
    /* *************************************************************************************** */

    qDebug() << "Thread in Program_the_digitizer() over is " << QThread::currentThreadId();

}


void MyWorker::InterruptTimeout()
{

}


void MyWorker::QuitProgram()
{

    qDebug() << "Thread in QuitProgram() is " << QThread::currentThreadId();
    if (ErrCode)
    {
        printf("\a%s\n", ErrMsg[ErrCode]);
        emit this->Message(ErrMsg[ErrCode]);
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
    for(ch=0; ch<WDcfg.Nch; ch++)
    {
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

    emit this->finished();
}
