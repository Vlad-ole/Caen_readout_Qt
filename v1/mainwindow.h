#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CAENDigitizerType.h"
#include "WaveDump.h"
#include "WDplot.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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

    void QuitProgram();
    void InterruptTimeout();
    void Program_the_digitizer();
    void Restart();
    void Mask_the_channels();
    void Readout_loop();

private slots:
    void on_pushButton_clicked();

    void on_radioButton_13_clicked();

    void on_radioButton_12_clicked();

    void on_checkBox_clicked();

    void on_spinBox_3_valueChanged(int arg1);

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_spinBox_4_valueChanged(int arg1);

    void on_radioButton_15_clicked(bool checked);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
