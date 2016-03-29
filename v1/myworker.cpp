#include "myworker.h"
#include <QtCore>
#include <QThread>

MyWorker::MyWorker()
{

}

void MyWorker::Init()
{
    qDebug() << "Thread in Init() is " << QThread::currentThreadId();

    int argc = 1;
    char* argv[0] = {};

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
    if (argc > 1)
        strcpy(ConfigFileName, argv[1]);
    else
        strcpy(ConfigFileName, DEFAULT_CONFIG_FILE);
    printf("Opening Configuration File %s\n", ConfigFileName);
    f_ini = fopen(ConfigFileName, "r");
    if (f_ini == NULL ) {
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
    if (ret) {
        ErrCode = ERR_INVALID_BOARD_TYPE;
        //goto QuitProgram;
        QuitProgram();
        return;
    }

    //Mask_the_channels();
    //Program_the_digitizer();


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
    qDebug() << "in Readout_loop() " << endl;
    //qDebug() << "WDrun.Quit = " << WDrun.Quit << endl;

    WDrun.Quit = 0;


    while(!WDrun.Quit)
    {

        // Check for keyboard commands (key pressed)
        CheckKeyboardCommands(handle, &WDrun, &WDcfg, BoardInfo);
        if (WDrun.Restart)
        {
            CAEN_DGTZ_SWStopAcquisition(handle);
            CAEN_DGTZ_FreeReadoutBuffer(&buffer);
            ClosePlotter();
            PlotVar = NULL;
            if(WDcfg.Nbit == 8)
                CAEN_DGTZ_FreeEvent(handle, (void**)&Event8);
            else
                if (BoardInfo.FamilyCode != CAEN_DGTZ_XX742_FAMILY_CODE)
                {
                    CAEN_DGTZ_FreeEvent(handle, (void**)&Event16);
                }
                else
                {
                    CAEN_DGTZ_FreeEvent(handle, (void**)&Event742);
                }
                f_ini = fopen(ConfigFileName, "r");
                ReloadCfgStatus = ParseConfigFile(f_ini, &WDcfg);
                fclose(f_ini);
                //goto Restart;
                Restart();
        }


        if (WDrun.AcqRun == 0)
        {
            //Sleep(1000);
            continue;
        }


        /* Wait for interrupt (if enabled) */
        //--------------------------------------------------------------------
        if (WDcfg.InterruptNumEvents > 0)
        {
            int32_t boardId;
            int VMEHandle;
            int InterruptMask = (1 << VME_INTERRUPT_LEVEL);

            BufferSize = 0;
            NumEvents = 0;
            // Interrupt handling
            if (isVMEDevice)
            {
                ret = CAEN_DGTZ_VMEIRQWait ((CAEN_DGTZ_ConnectionType)WDcfg.LinkType, WDcfg.LinkNum, WDcfg.ConetNode, (uint8_t)InterruptMask, INTERRUPT_TIMEOUT, &VMEHandle);
            }
            else
                ret = CAEN_DGTZ_IRQWait(handle, INTERRUPT_TIMEOUT);
            if (ret == CAEN_DGTZ_Timeout)  // No active interrupt requests
            {
                //goto InterruptTimeout;
                InterruptTimeout();
            }
            if (ret != CAEN_DGTZ_Success)
            {
                ErrCode = ERR_INTERRUPT;
                //goto QuitProgram;
                QuitProgram();
                return;
            }
            // Interrupt Ack
            if (isVMEDevice)
            {
                ret = CAEN_DGTZ_VMEIACKCycle(VMEHandle, VME_INTERRUPT_LEVEL, &boardId);
                if ((ret != CAEN_DGTZ_Success) || (boardId != VME_INTERRUPT_STATUS_ID))
                {
                    //goto InterruptTimeout;
                    InterruptTimeout();
                }
                else
                {
                    if (INTERRUPT_MODE == CAEN_DGTZ_IRQ_MODE_ROAK)
                        ret = CAEN_DGTZ_RearmInterrupt(handle);
                }
            }
        }
        //--------------------------------------------------------------------


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

    }

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


}


void MyWorker::InterruptTimeout()
{
    /* Calculate throughput and trigger rate (every second) */
    Nb += BufferSize;
    Ne += NumEvents;
    CurrentTime = get_time();
    ElapsedTime = CurrentTime - PrevRateTime;

    nCycles++;
    if (ElapsedTime > 1000)
    {
        if (Nb == 0)
            if (ret == CAEN_DGTZ_Timeout) printf ("Timeout...\n"); else printf("No data...\n");
        else
            printf("Reading at %.2f MB/s (Trg Rate: %.2f Hz)\n", (float)Nb/((float)ElapsedTime*1048.576f), (float)Ne*1000.0f/(float)ElapsedTime);
        nCycles= 0;
        Nb = 0;
        Ne = 0;
        PrevRateTime = CurrentTime;
    }

    /* Analyze data */
    for(i = 0; i < (int)NumEvents; i++)
    {

        /* Get one event from the readout buffer */
        ret = CAEN_DGTZ_GetEventInfo(handle, buffer, BufferSize, i, &EventInfo, &EventPtr);
        if (ret) {
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
                ret = CAEN_DGTZ_DecodeEvent(handle, EventPtr, (void**)&Event16);
            }
            else
            {
                ret = CAEN_DGTZ_DecodeEvent(handle, EventPtr, (void**)&Event742);
                if (WDcfg.useCorrections != -1) { // if manual corrections
                    uint32_t gr;
                    for (gr = 0; gr < WDcfg.MaxGroupNumber; gr++) {
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

            /* Update Histograms */
            if (WDrun.RunHisto) {
                for(ch=0; ch<WDcfg.Nch; ch++) {
                    int chmask = ((BoardInfo.FamilyCode == CAEN_DGTZ_XX740_FAMILY_CODE) || (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE) )? (ch/8) : ch;
                    if (!(EventInfo.ChannelMask & (1<<chmask)))
                        continue;
                    if (WDrun.Histogram[ch] == NULL) {
                        if ((WDrun.Histogram[ch] = malloc((uint64_t)(1<<WDcfg.Nbit) * sizeof(uint32_t))) == NULL)
                        {
                            ErrCode = ERR_HISTO_MALLOC;
                            //goto QuitProgram;
                            QuitProgram();
                            return;
                        }
                        memset(WDrun.Histogram[ch], 0, (uint64_t)(1<<WDcfg.Nbit) * sizeof(uint32_t));
                    }
                    if (WDcfg.Nbit == 8)
                        for(i=0; i<(int)Event8->ChSize[ch]; i++)
                            WDrun.Histogram[ch][Event8->DataChannel[ch][i]]++;
                    else {
                        if (BoardInfo.FamilyCode != CAEN_DGTZ_XX742_FAMILY_CODE) {
                            for(i=0; i<(int)Event16->ChSize[ch]; i++)
                                WDrun.Histogram[ch][Event16->DataChannel[ch][i]]++;
                        }
                        else {
                            printf("Can't build samples histogram for this board: it has float samples.\n");
                            WDrun.RunHisto = 0;
                            break;
                        }
                    }
                }
            }

            /* Write Event data to file */
            if (WDrun.ContinuousWrite || WDrun.SingleWrite) {
                // Note: use a thread here to allow parallel readout and file writing
                if (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE) {
                    ret = WriteOutputFilesx742(&WDcfg, &WDrun, &EventInfo, Event742);
                }
                else if (WDcfg.Nbit == 8) {
                    ret = WriteOutputFiles(&WDcfg, &WDrun, &EventInfo, Event8);
                }
                else {
                    ret = WriteOutputFiles(&WDcfg, &WDrun, &EventInfo, Event16);
                }
                if (ret) {
                    ErrCode = ERR_OUTFILE_WRITE;
                    //goto QuitProgram;
                    QuitProgram();
                    return;
                }
                if (WDrun.SingleWrite) {
                    printf("Single Event saved to output files\n");
                    WDrun.SingleWrite = 0;
                }
            }

            /* Plot Waveforms */
            if ((WDrun.ContinuousPlot || WDrun.SinglePlot) && !IsPlotterBusy()) {
                int Ntraces = (BoardInfo.FamilyCode == CAEN_DGTZ_XX740_FAMILY_CODE) ? 8 : WDcfg.Nch;
                if (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE) Ntraces = 9;
                if (PlotVar == NULL) {
                    int TraceLength = max(WDcfg.RecordLength, (uint32_t)(1 << WDcfg.Nbit));
                    PlotVar = OpenPlotter(WDcfg.GnuPlotPath, Ntraces, TraceLength);
                    WDrun.SetPlotOptions = 1;
                }
                if (PlotVar == NULL) {
                    printf("Can't open the plotter\n");
                    WDrun.ContinuousPlot = 0;
                    WDrun.SinglePlot = 0;
                } else {
                    int Tn = 0;
                    if (WDrun.SetPlotOptions) {
                        if ((WDrun.PlotType == PLOT_WAVEFORMS) && (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE)) {
                            strcpy(PlotVar->Title, "Waveform");
                            PlotVar->Xscale = WDcfg.Ts;
                            strcpy(PlotVar->Xlabel, "ns");
                            strcpy(PlotVar->Ylabel, "ADC counts");
                            PlotVar->Yautoscale = 0;
                            PlotVar->Ymin = 0;
                            PlotVar->Ymax = (float)(1<<WDcfg.Nbit);
                            PlotVar->Xautoscale = 1;
                        } else if (WDrun.PlotType == PLOT_WAVEFORMS) {
                            strcpy(PlotVar->Title, "Waveform");
                            PlotVar->Xscale = WDcfg.Ts * WDcfg.DecimationFactor/1000;
                            strcpy(PlotVar->Xlabel, "us");
                            strcpy(PlotVar->Ylabel, "ADC counts");
                            PlotVar->Yautoscale = 0;
                            PlotVar->Ymin = 0;
                            PlotVar->Ymax = (float)(1<<WDcfg.Nbit);
                            PlotVar->Xautoscale = 1;
                        }  else if (WDrun.PlotType == PLOT_FFT) {
                            strcpy(PlotVar->Title, "FFT");
                            strcpy(PlotVar->Xlabel, "MHz");
                            strcpy(PlotVar->Ylabel, "dB");
                            PlotVar->Yautoscale = 1;
                            PlotVar->Ymin = -160;
                            PlotVar->Ymax = 0;
                            PlotVar->Xautoscale = 1;
                        } else if (WDrun.PlotType == PLOT_HISTOGRAM) {
                            PlotVar->Xscale = 1.0;
                            strcpy(PlotVar->Xlabel, "ADC channels");
                            strcpy(PlotVar->Ylabel, "Counts");
                            PlotVar->Yautoscale = 1;
                            PlotVar->Xautoscale = 1;
                        }
                        SetPlotOptions();
                        WDrun.SetPlotOptions = 0;
                    }
                    for(ch=0; ch<Ntraces; ch++) {
                        int absCh = WDrun.GroupPlotIndex * 8 + ch;

                        if (!((WDrun.ChannelPlotMask >> ch) & 1))
                            continue;
                        if ((BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE) && ((ch != 0) && (absCh % 8) == 0)) sprintf(PlotVar->TraceName[Tn], "TR %d", (int)((absCh-1) / 16));
                        else sprintf(PlotVar->TraceName[Tn], "CH %d", absCh);
                        if (WDrun.PlotType == PLOT_WAVEFORMS) {
                            if (WDcfg.Nbit == 8) {
                                PlotVar->TraceSize[Tn] = Event8->ChSize[absCh];
                                memcpy(PlotVar->TraceData[Tn], Event8->DataChannel[absCh], Event8->ChSize[absCh]);
                                PlotVar->DataType = PLOT_DATA_UINT8;
                            } else if (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE) {
                                if (Event742->GrPresent[WDrun.GroupPlotIndex]) {
                                    PlotVar->TraceSize[Tn] = Event742->DataGroup[WDrun.GroupPlotIndex].ChSize[ch];
                                    memcpy(PlotVar->TraceData[Tn], Event742->DataGroup[WDrun.GroupPlotIndex].DataChannel[ch], Event742->DataGroup[WDrun.GroupPlotIndex].ChSize[ch] * sizeof(float));
                                    PlotVar->DataType = PLOT_DATA_FLOAT;
                                }
                            }
                            else {
                                PlotVar->TraceSize[Tn] = Event16->ChSize[absCh];
                                memcpy(PlotVar->TraceData[Tn], Event16->DataChannel[absCh], Event16->ChSize[absCh] * 2);
                                PlotVar->DataType = PLOT_DATA_UINT16;
                            }
                        } else if (WDrun.PlotType == PLOT_FFT) {
                            int FFTns;
                            PlotVar->DataType = PLOT_DATA_DOUBLE;
                            if(WDcfg.Nbit == 8)
                                FFTns = FFT(Event8->DataChannel[absCh], PlotVar->TraceData[Tn], Event8->ChSize[absCh], HANNING_FFT_WINDOW, SAMPLETYPE_UINT8);
                            else if (BoardInfo.FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE) {
                                FFTns = FFT(Event742->DataGroup[WDrun.GroupPlotIndex].DataChannel[ch], PlotVar->TraceData[Tn],
                                    Event742->DataGroup[WDrun.GroupPlotIndex].ChSize[ch], HANNING_FFT_WINDOW, SAMPLETYPE_FLOAT);
                            }
                            else
                                FFTns = FFT(Event16->DataChannel[absCh], PlotVar->TraceData[Tn], Event16->ChSize[absCh], HANNING_FFT_WINDOW, SAMPLETYPE_UINT16);
                            PlotVar->Xscale = (1000/WDcfg.Ts)/(2*FFTns);
                            PlotVar->TraceSize[Tn] = FFTns;
                        } else if (WDrun.PlotType == PLOT_HISTOGRAM) {
                            PlotVar->DataType = PLOT_DATA_UINT32;
                            strcpy(PlotVar->Title, "Histogram");
                            PlotVar->TraceSize[Tn] = 1<<WDcfg.Nbit;
                            memcpy(PlotVar->TraceData[Tn], WDrun.Histogram[absCh], (uint64_t)(1<<WDcfg.Nbit) * sizeof(uint32_t));
                        }
                        Tn++;
                        if (Tn >= MAX_NUM_TRACES)
                            break;
                    }
                    PlotVar->NumTraces = Tn;
                    if( PlotWaveforms() < 0) {
                        WDrun.ContinuousPlot = 0;
                        printf("Plot Error\n");
                    }
                    WDrun.SinglePlot = 0;
                }
            }
    }
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

    emit this->finished();
}
