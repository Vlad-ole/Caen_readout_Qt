#include "myworker.h"
#include <QtCore>
#include <QThread>

MyWorker::MyWorker()
{
    //array_y_data.resize(8);
}

void MyWorker::Init()
{
    qDebug() << "Thread in Init() is " << QThread::currentThreadId();

    events_per_file = 10;
    output_folder = "";
    run_counter = 0;
    absolute_event_counter = 0;

    WDcfg.out_file_isheader = false;

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

    WDrun.ContinuousPlot = 1;
    WDrun.ContinuousTrigger = 1;

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
    qDebug() << "in Readout_loop() " << endl;

    WDrun.Quit = 0;


    CAEN_DGTZ_SWStartAcquisition(handle);
    WDrun.AcqRun = 1;

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
            //emit this->RedrawGraphs();

           qDebug() << "Thread in Readout_loop() is " << QThread::currentThreadId();
           qDebug() << "WDcfg.InterruptNumEvents " << WDcfg.InterruptNumEvents;
           qDebug() << "BufferSize " << BufferSize ;
           qDebug() << "handle " << handle;
           qDebug() << "WDrun.Quit " << WDrun.Quit;
           qDebug() << "WDrun.ContinuousWrite " << WDrun.ContinuousWrite;

            if (WDrun.ContinuousTrigger)
                qDebug() << "Continuous trigger is enabled\n";
            else
                qDebug() << "Continuous trigger is disabled\n";

            if (Nb == 0)
            {
                if (ret == CAEN_DGTZ_Timeout)
                {
                    //printf ("Timeout...\n");
                    qDebug() << "Timeout...\n" ;
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
                //qDebug() << "Reading at " <<  (float)Nb/((float)ElapsedTime*1048.576f) << " MB/s";
                emit this->TransferSpeed( (float)Nb/((float)ElapsedTime*1048.576f) );
                emit this->TriggerRate( (float)Ne * 1000.0f / (float)ElapsedTime );
            }

            nCycles= 0;
            Nb = 0;
            Ne = 0;
            PrevRateTime = CurrentTime;

            qDebug() << "WDcfg.Threshold[0] = " << WDcfg.Threshold[0] << endl;
            qDebug() << "WDcfg.Threshold[1] = " << WDcfg.Threshold[1] << endl;
            qDebug() << "WDcfg.Threshold[2] = " << WDcfg.Threshold[2] << endl;


            if(WDrun.ContinuousPlot)
            {
                long time_label_start = get_time();

                uint N_ch;
                switch (BoardInfo.FamilyCode)
                {
                    case CAEN_DGTZ_XX720_FAMILY_CODE:
                {
                    N_ch = 8;
                    break;
                }
                case CAEN_DGTZ_XX740_FAMILY_CODE:
                {
                    N_ch = 64;
                    break;
                }
                default:
                    qDebug() << "add device in list" << endl;

                }

                array_y_data.resize(N_ch);

                for(int i = 0; i < N_ch; i++)
                {
                    array_y_data[i].clear();
                }



                /* Analyze data */
                for(i = 0; i < (int)NumEvents; i++)
                {


                    /* Get one event from the readout buffer */
                    ret = CAEN_DGTZ_GetEventInfo(handle, buffer, BufferSize, i, &EventInfo, &EventPtr);
                    if (ret)
                    {
                        ErrCode = ERR_EVENT_BUILD;
                        //goto QuitProgram;
                        QuitProgram();
                        return;
                    }


                    /* decode the event */
                    if (WDcfg.Nbit == 8)
                        ret = CAEN_DGTZ_DecodeEvent(handle, EventPtr, (void**)&Event8);
                    else
                        if (BoardInfo.FamilyCode != CAEN_DGTZ_XX742_FAMILY_CODE)
                        {
                            ret = CAEN_DGTZ_DecodeEvent(handle, EventPtr, (void**)&Event16); // it's my case
                        }
                        else
                        {
                            ret = CAEN_DGTZ_DecodeEvent(handle, EventPtr, (void**)&Event742);
                            if (WDcfg.useCorrections != -1)
                            { // if manual corrections
                                uint32_t gr;
                                for (gr = 0; gr < WDcfg.MaxGroupNumber; gr++)
                                {
                                    if ( ((WDcfg.EnableMask >> gr) & 0x1) == 0)
                                        continue;
                                    ApplyDataCorrection( &(X742Tables[gr]), WDcfg.DRS4Frequency, WDcfg.useCorrections, &(Event742->DataGroup[gr]));
                                }
                            }
                        }


                    if (ret)
                    {
                        ErrCode = ERR_EVENT_BUILD;
                        //goto QuitProgram;
                        QuitProgram();
                        return;
                    }


                    bool flag = true;



                    for(ch=0; ch<WDcfg.Nch; ch++)
                    {
                        int Size = (WDcfg.Nbit == 8) ? Event8->ChSize[ch] : Event16->ChSize[ch];
                        if (Size <= 0)
                        {
                            continue;
                        }


                        for(int index = 0; index < Size; index++)
                        {
                            if(flag)
                            {
                                array_x_data.push_back( (index  + i * Size) * (WDcfg.Ts / 1000.0)  );
                            }

                            if(WDcfg.Nbit != 8)
                                array_y_data[ch].push_back( (2000 / pow(2.0, WDcfg.Nbit) ) * Event16->DataChannel[ch][index]  - 1000 ); // add value in mV
                            else
                                qDebug() << "add device in list" << endl;
                        }

                        flag = false;
                    }


                }

                emit this->RedrawGraphsFull(array_x_data, array_y_data);
                qDebug() << "Delta time (prepare data)= " << get_time() - time_label_start;
            }

        }//if( ElapsedTime >= 1000)






        if(WDrun.ContinuousWrite)
        {
            /* Analyze data */
            for(i = 0; i < (int)NumEvents; i++)
            {

                /* Get one event from the readout buffer */
                ret = CAEN_DGTZ_GetEventInfo(handle, buffer, BufferSize, i, &EventInfo, &EventPtr);
                if (ret)
                {
                    ErrCode = ERR_EVENT_BUILD;
                    //goto QuitProgram;
                    QuitProgram();
                    return;
                }


                /* decode the event */
                if (WDcfg.Nbit == 8)
                    ret = CAEN_DGTZ_DecodeEvent(handle, EventPtr, (void**)&Event8);
                else
                    if (BoardInfo.FamilyCode != CAEN_DGTZ_XX742_FAMILY_CODE)
                    {
                        ret = CAEN_DGTZ_DecodeEvent(handle, EventPtr, (void**)&Event16); // it's my case
                    }
                    else
                    {
                        ret = CAEN_DGTZ_DecodeEvent(handle, EventPtr, (void**)&Event742);
                        if (WDcfg.useCorrections != -1)
                        { // if manual corrections
                            uint32_t gr;
                            for (gr = 0; gr < WDcfg.MaxGroupNumber; gr++)
                            {
                                if ( ((WDcfg.EnableMask >> gr) & 0x1) == 0)
                                    continue;
                                ApplyDataCorrection( &(X742Tables[gr]), WDcfg.DRS4Frequency, WDcfg.useCorrections, &(Event742->DataGroup[gr]));
                            }
                        }
                    }
                if (ret) {
                    ErrCode = ERR_EVENT_BUILD;
                    //goto QuitProgram;
                    QuitProgram();
                    return;
                }
                

                /* Write Event data to file */
                if (WDrun.ContinuousWrite || WDrun.SingleWrite)
                {
                    //qDebug() << "Write data ..." << endl;


                    if( absolute_event_counter % events_per_file == 0 )
                    {
                        int Ch;

                        for(Ch=0; Ch<WDcfg.Nch; Ch++)
                        {
                            int Size = (WDcfg.Nbit == 8) ? Event8->ChSize[Ch] : Event16->ChSize[Ch];
                            if (Size <= 0)
                            {
                                continue;
                            }
                        }

                        qDebug() << "events_per_file  = " << events_per_file << endl;
                        qDebug() << "run_counter  = " << run_counter << endl;
                        qDebug() << "absolute_event_counter  = " << absolute_event_counter << endl;
                        for(int ch = 0; ch < Ch ;ch++)
                        {
                            WDrun.fout[ch] = NULL;
                            qDebug() << "WDrun.fout[" << ch << "] = " << WDrun.fout[ch] << endl;
                        }

                        //absolute_event_counter = 0;
                        run_counter++;
                    }



                    std::ostringstream oss_path;
                    oss_path << output_folder.toStdString() << "run_" << run_counter;
                    std::string path_string = oss_path.str();

                    // Note: use a thread here to allow parallel readout and file writing
                    if (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE) {
                        ret = WriteOutputFilesx742(&WDcfg, &WDrun, &EventInfo, Event742);
                    }
                    else if (WDcfg.Nbit == 8)
                    {
                        ret = WriteOutputFiles(&WDcfg, &WDrun, &EventInfo, Event8, path_string);
                    }
                    else
                    {
                        ret = WriteOutputFiles(&WDcfg, &WDrun, &EventInfo, Event16, path_string); //my case

                    }
                    if (ret)
                    {
                        ErrCode = ERR_OUTFILE_WRITE;
                        //goto QuitProgram;
                        QuitProgram();
                    }
                    if (WDrun.SingleWrite)
                    {
                        printf("Single Event saved to output files\n");
                        WDrun.SingleWrite = 0;
                    }

                    absolute_event_counter++;
                }

            }//for(i = 0; i < (int)NumEvents; i++)
        }


    }

}

void MyWorker::ContinuousTrigger()
{
     //WDrun.ContinuousTrigger = 1;
    WDrun.ContinuousTrigger ^= 1;
}

 void MyWorker::SetRecordLength(double value)
 {
    WDcfg.RecordLength = value;
 }

void MyWorker::Restart()
{
    StopReadout_loop();
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

void MyWorker::ContinuousWrite()
{
    WDrun.ContinuousWrite ^= 1;
}

void MyWorker::TestPattern()
{
    if(WDcfg.TestPattern)
    {
        WDcfg.TestPattern = 0;
        Program_the_digitizer();
    }
    else
    {
        WDcfg.TestPattern = 1;
        Program_the_digitizer();
    }
}

void MyWorker::EnableContinuousPlot()
{
    WDrun.ContinuousPlot = 1;
}

void MyWorker::DisableContinuousPlot()
{
    WDrun.ContinuousPlot = 0;
}

void MyWorker::MaskChannel(int ch, bool Enable)
{
    if(Enable)
    {
        WDcfg.EnableMask |= (1 << ch);
        qDebug() << " WDcfg.EnableMask |= (1 << ch) " << endl;
    }
    else
    {
        WDcfg.EnableMask &= ~(1 << ch);
        qDebug() << " WDcfg.EnableMask &= ~(1 << ch) " << endl;
    }

    QString myStringOfBits( QString::number( WDcfg.EnableMask, 2 ) );
    qDebug() << " WDcfg.EnableMask = " << myStringOfBits << endl;

    Restart();
    //Sleep(5000);
}

void MyWorker::MaskChannelAll(bool value)
{
    for(int ch = 0; ch < 25; ch++)
    {
        if(value)
            WDcfg.EnableMask |= (1 << ch);
        else
            WDcfg.EnableMask &= ~(1 << ch);
    }

    qDebug() << " MaskChannelAll " << value << endl;
    Restart();
}

void MyWorker::SetTriggerValue(int ch, int val)
{
    qDebug() << "in SetTriggerValue slot" << endl;

    double Vpp = 2000; // mV

    switch (BoardInfo.FamilyCode)
    {
    case CAEN_DGTZ_XX720_FAMILY_CODE:
    case CAEN_DGTZ_XX740_FAMILY_CODE:
    {
        WDcfg.Threshold[ch] = ( pow(2.0, BoardInfo.ADC_NBits) - 1 ) * (val / Vpp + 0.5);
        qDebug() << "WDcfg.Threshold[" << ch << "] = " << WDcfg.Threshold[ch] << endl;
        break;
    }
    default:
        qDebug() << "add device in list" << endl;
    }



    Restart();
}

void MyWorker::CHANNEL_TRIGGER_signal(int ch, bool value)
{

    switch(BoardInfo.FamilyCode)
    {
    case CAEN_DGTZ_XX720_FAMILY_CODE:
    {
        CAEN_DGTZ_TriggerMode_t tm;

        if(value)
        {
            tm = CAEN_DGTZ_TRGMODE_ACQ_ONLY;
            qDebug() << " WDcfg.ChannelTriggerMode[" << ch << "] = CAEN_DGTZ_TRGMODE_ACQ_ONLY" << endl;
        }
        else
        {
            tm = CAEN_DGTZ_TRGMODE_DISABLED;
            qDebug() << " WDcfg.ChannelTriggerMode[" << ch << "] = CAEN_DGTZ_TRGMODE_DISABLED" << endl;
        }

        WDcfg.ChannelTriggerMode[ch] = tm;
        break;
    }
    case CAEN_DGTZ_XX740_FAMILY_CODE:
    {
        int group = ch / 8;

        if(value)
            WDcfg.GroupTrgEnableMask[group] |= 1 << (ch - group * 8);
        else
            WDcfg.GroupTrgEnableMask[group] &= ~(1 << (ch - group * 8));

        for(int i = 0; i < 8; i++)
        {
            qDebug() << " WDcfg.GroupTrgEnableMask[" << i << "] = " << QString::number( WDcfg.GroupTrgEnableMask[i], 2 )  << endl;
        }
        break;
    }
    default:
        qDebug() << "Add this device in list" << endl;
    }

    Restart();
}

void MyWorker::CHANNEL_TRIGGER_all(bool value)
{
    for(int ch = 0; ch < 8; ch++)
    {
        if(value)
        {
            WDcfg.ChannelTriggerMode[ch] = CAEN_DGTZ_TRGMODE_ACQ_ONLY;
            WDcfg.GroupTrgEnableMask[ch] = 0xFF;
        }
        else
        {
            WDcfg.ChannelTriggerMode[ch] = CAEN_DGTZ_TRGMODE_DISABLED;
            WDcfg.GroupTrgEnableMask[ch] = 0;
        }

        qDebug() << " WDcfg.GroupTrgEnableMask[" << ch << "] = " <<  QString::number( WDcfg.GroupTrgEnableMask[ch], 2 ) << endl;

    }


    qDebug() << "CHANNEL_TRIGGER_all = " << value << endl;

    Restart();
}

void MyWorker::SetOutFileType(int value)
{
    switch(value)
    {
    case ASCII:
    {
        WDcfg.out_file_type = ASCII;
        Restart();
        qDebug() << "WDcfg.out_file_type = ASCII" << endl;
        break;
    }
    case BINARY:
    {
        WDcfg.out_file_type = BINARY;
        Restart();
        qDebug() << "WDcfg.out_file_type = BINARY" << endl;
        break;
    }
    case ROOT_TREE:
    {
        WDcfg.out_file_type = ROOT_TREE;
        Restart();
        qDebug() << "WDcfg.out_file_type = ROOT_TREE" << endl;
        break;
    }
    default:
        qDebug() << "SetOutFileType error!" << endl;
    }

}

void MyWorker::SetEventsPerFile(int value)
{
    events_per_file = value;
}

void MyWorker::SetFolder(QString value)
{
    output_folder = value;
}

void MyWorker::CHANNEL_TRIGGER_group(int group, bool val)
{

}

void MyWorker::SetContinuousTrigger(bool value)
{
    if(value)
        WDrun.ContinuousTrigger = 1;
    else
        WDrun.ContinuousTrigger = 0;

    qDebug() << "WDrun.ContinuousTrigger = " << WDrun.ContinuousTrigger << endl;

    Restart();
}
