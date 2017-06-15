#ifndef MYWORKER_H
#define MYWORKER_H

#include <QtCore>
#include "CAENDigitizerType.h"
#include "WaveDump.h"
#include "WDplot.h"
#include "WDconfig.h"
#include "X742CorrectionRoutines.h"
#include "fft.h"

#include <sstream>

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif




class MyWorker : public QObject
{
    Q_OBJECT
public:
    MyWorker();

    int events_per_file;
    QString output_folder;
    long unsigned int run_counter;
    long unsigned int absolute_event_counter;

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

    QVector<double> array_x_data;
    QVector< QVector <double> > array_y_data;

    //QVector<double> array_x;
    //QVector<double> array_y;


    qint64 TDrawFinished;
    qint64 UpdateTime;
    qint64 PrevPlotTime;


public slots:
    void Init();

//    void Program_the_digitizer();
//    void Mask_the_channels();
    void Readout_loop();

    void Restart();

    void QuitProgram();

    void StopReadout_loop();
    void ContinuousTrigger();
    void ContinuousWrite();
    void SetRecordLength(double value);
    void TestPattern();
    void EnableContinuousPlot();
    void DisableContinuousPlot();
    void MaskChannel(int , bool);
    void SetTriggerValue(int, int);
    void MaskChannelAll(bool);

    void CHANNEL_TRIGGER_signal(int, bool);
    void CHANNEL_TRIGGER_group(int, bool);
    void CHANNEL_TRIGGER_all(bool);

    void SetOutFileType(int);
    void SetEventsPerFile(int);
    void SetFolder(QString);

    void SetContinuousTrigger(bool);
    void SetRisingFalling(bool);
    void SetDCOffset(int, int);
    void SetExternalTrigger(bool);
    void SetTDrawFinished(long);

    void SetUpdateTime(int);
    void SetPostTrigger(int);


signals:
    void Message(QString);
    void finished();
    void InitializationComplete();
    void RedrawGraphs(QVector<double>, QVector<double> );
    void RedrawGraphsFull(QVector<double>, QVector< QVector <double> > );
    void TransferSpeed(double);
    void TriggerRate(double);
    //void GraphData(double **array, int rows, int cols);
    //void GraphData1D(double *array, int size);
    void RedrawGraphsTest();
    void PlotMask(uint);


};

#endif // MYWORKER_H
