#ifndef MYWORKER_H
#define MYWORKER_H

#include <QtCore>
#include "CAENDigitizerType.h"
#include "WaveDump.h"
#include "WDplot.h"
#include "WDconfig.h"
#include "X742CorrectionRoutines.h"
#include "fft.h"

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif


class MyWorker : public QObject
{
    Q_OBJECT
public:
    MyWorker();

    int  handle;
    CAEN_DGTZ_ErrorCode ret;
    uint32_t AllocatedSize, BufferSize, NumEvents;
    char *buffer;
    ERROR_CODES ErrCode;
    WDPlot_t *PlotVar;
    WaveDumpConfig_t   WDcfg;
    WaveDumpRun_t      WDrun;
    int i, ch, Nb, Ne;
    CAEN_DGTZ_UINT16_EVENT_t    *Event16; /* generic event struct with 16 bit data (10, 12, 14 and 16 bit digitizers */
    CAEN_DGTZ_UINT8_EVENT_t     *Event8; /* generic event struct with 8 bit data (only for 8 bit digitizers) */
    CAEN_DGTZ_X742_EVENT_t       *Event742;/* custom event struct with 8 bit data (only for 8 bit digitizers) */
    int isVMEDevice, MajorNumber;
    uint64_t CurrentTime, PrevRateTime, ElapsedTime;
    int nCycles;
    CAEN_DGTZ_BoardInfo_t       BoardInfo;
    CAEN_DGTZ_EventInfo_t       EventInfo;
    char *EventPtr;
    CAEN_DGTZ_DRS4Correction_t X742Tables[MAX_X742_GROUP_SIZE];
    FILE *f_ini;
    char ConfigFileName[100];
    int ReloadCfgStatus;

    void Program_the_digitizer();
    void Mask_the_channels();
    void InterruptTimeout();

public slots:
    void Init();

//    void Program_the_digitizer();
//    void Mask_the_channels();
    void Readout_loop();

    void Restart();

    void QuitProgram();

    void StopReadout_loop();
    void ContinuousTrigger();

signals:
    void Message(QString);
    void finished();
    void InitializationComplete();
    void RedrawGraphs();

};

#endif // MYWORKER_H