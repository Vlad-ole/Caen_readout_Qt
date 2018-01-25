#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CAENDigitizerType.h"
#include "WaveDump.h"
#include "WDplot.h"
#include "mythread.h"
#include "myworker.h"

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
    MyThread *thread;
    MyWorker *worker;

    bool on_pushButton_2_clicked_bool;
    void SetRangeX();


private slots:
    void on_pushButton_clicked();

    void on_radioButton_13_clicked();

    void on_radioButton_12_clicked();

    void on_checkBox_clicked();


    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    //void on_spinBox_4_valueChanged(int arg1);

    void on_radioButton_15_clicked(bool checked);

    void on_pushButton_2_clicked();


    void on_radioButton_15_clicked();

    void on_pushButton_3_clicked();

    void on_groupBox_3_clicked();

    //void on_spinBox_4_editingFinished();

    void on_Test_Pattern_button_clicked();

    void on_checkBox_clicked(bool checked);

    void on_Test_Pattern_button_clicked(bool checked);

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

//    void on_checkBox_11_clicked(bool checked);
//    void on_checkBox_12_clicked(bool checked);
//    void on_checkBox_13_clicked(bool checked);
//    void on_checkBox_14_clicked(bool checked);
//    void on_checkBox_15_clicked(bool checked);
//    void on_checkBox_21_clicked(bool checked);
//    void on_checkBox_22_clicked(bool checked);
//    void on_checkBox_23_clicked(bool checked);




    void on_pushButton_Reprogram_clicked();

//    void on_checkBox_24_clicked(bool checked);
//    void on_checkBox_25_clicked(bool checked);
//    void on_checkBox_31_clicked(bool checked);
//    void on_checkBox_32_clicked(bool checked);
//    void on_checkBox_33_clicked(bool checked);
//    void on_checkBox_34_clicked(bool checked);
//    void on_checkBox_35_clicked(bool checked);
//    void on_checkBox_41_clicked(bool checked);
//    void on_checkBox_42_clicked(bool checked);
//    void on_checkBox_43_clicked(bool checked);
//    void on_checkBox_44_clicked(bool checked);
//    void on_checkBox_45_clicked(bool checked);
//    void on_checkBox_51_clicked(bool checked);
//    void on_checkBox_52_clicked(bool checked);
//    void on_checkBox_53_clicked(bool checked);
//    void on_checkBox_54_clicked(bool checked);
//    void on_checkBox_55_clicked(bool checked);

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    //void on_checkBox_12_clicked();



    //  //


    void on_CHANNEL_TRIGGER_checkBox_gr0_ch0_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr0_ch1_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr0_ch2_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr0_ch3_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr0_ch4_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr0_ch5_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr0_ch6_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr0_ch7_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr1_ch8_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr1_ch9_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr1_ch10_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr1_ch11_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr1_ch12_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr1_ch13_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr1_ch14_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr1_ch15_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr2_ch16_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr2_ch17_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr2_ch18_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr2_ch19_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr2_ch20_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr2_ch21_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr2_ch22_clicked(bool checked);
    void on_CHANNEL_TRIGGER_checkBox_gr2_ch23_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr3_ch24_clicked(bool checked);



    void on_radioButton_9_clicked(bool checked);

    void on_radioButton_10_clicked(bool checked);

    void on_radioButton_root_tree_clicked(bool checked);

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_choose_folder_clicked();



    void on_CHANNEL_TRIGGER_checkBox_gr3_ch25_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr3_ch26_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr3_ch27_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr3_ch28_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr3_ch29_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr3_ch30_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr3_ch31_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr4_ch32_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr4_ch33_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr4_ch34_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr4_ch35_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr4_ch36_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr4_ch37_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr4_ch38_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr4_ch39_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr5_ch40_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr5_ch41_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr5_ch42_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr5_ch43_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr5_ch44_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr5_ch45_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr5_ch46_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr5_ch47_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr6_ch48_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr6_ch49_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr6_ch50_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr6_ch51_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr6_ch52_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr6_ch53_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr6_ch54_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr6_ch55_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr7_ch56_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr7_ch57_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr7_ch58_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr7_ch59_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr7_ch60_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr7_ch61_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr7_ch62_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_gr7_ch63_clicked(bool checked);


    void on_spinBox_x_max_valueChanged(int arg1);
    void on_spinBox_x_min_valueChanged(int arg1);

    void on_MASK_CHANNEL_checkBox_gr0_ch0_clicked(bool checked);
    void on_MASK_CHANNEL_checkBox_gr0_ch1_clicked(bool checked);
    void on_MASK_CHANNEL_checkBox_gr0_ch2_clicked(bool checked);
    void on_MASK_CHANNEL_checkBox_gr0_ch3_clicked(bool checked);
    void on_MASK_CHANNEL_checkBox_gr0_ch4_clicked(bool checked);
    void on_MASK_CHANNEL_checkBox_gr0_ch5_clicked(bool checked);
    void on_MASK_CHANNEL_checkBox_gr0_ch6_clicked(bool checked);
    void on_MASK_CHANNEL_checkBox_gr0_ch7_clicked(bool checked);

    void on_MASK_CHANNEL_checkBox_gr1_ch0_clicked(bool checked);
    void on_MASK_CHANNEL_checkBox_gr2_ch0_clicked(bool checked);
    void on_MASK_CHANNEL_checkBox_gr3_ch0_clicked(bool checked);
    void on_MASK_CHANNEL_checkBox_gr4_ch0_clicked(bool checked);
    void on_MASK_CHANNEL_checkBox_gr5_ch0_clicked(bool checked);
    void on_MASK_CHANNEL_checkBox_gr6_ch0_clicked(bool checked);
    void on_MASK_CHANNEL_checkBox_gr7_ch0_clicked(bool checked);

    void on_radioButton_14_clicked(bool checked);

    void on_radioButton_clicked();

    void on_radioButton_clicked(bool checked);

    void on_lcdNumber_2_windowTitleChanged(const QString &title);

    void on_radioButton_2_clicked(bool checked);

    void on_radioButton_3_clicked(bool checked);

    void on_pushButton_9_clicked();

    void on_spinBox_dcoffset_gr0_valueChanged(int arg1);

    void on_spinBox_dcoffset_gr1_valueChanged(int arg1);

    void on_spinBox_dcoffset_gr2_valueChanged(int arg1);

    void on_spinBox_dcoffset_gr3_valueChanged(int arg1);

    void on_spinBox_dcoffset_gr4_valueChanged(int arg1);

    void on_spinBox_dcoffset_gr5_valueChanged(int arg1);

    void on_spinBox_dcoffset_gr6_valueChanged(int arg1);

    void on_spinBox_dcoffset_gr7_valueChanged(int arg1);

    void on_spinBox_4_valueChanged(int arg1);

    void on_radioButton_13_clicked(bool checked);

    void on_radioButton_12_clicked(bool checked);

    void on_pushButton_8_clicked(bool checked);

    void on_pushButton_threshold_gr_all_reset_clicked();

    void on_spinBox_threshold_gr0_valueChanged(int arg1);

    void on_spinBox_threshold_gr1_valueChanged(int arg1);

    void on_spinBox_threshold_gr2_valueChanged(int arg1);

    void on_spinBox_threshold_gr3_valueChanged(int arg1);

    void on_spinBox_threshold_gr4_valueChanged(int arg1);

    void on_spinBox_threshold_gr5_valueChanged(int arg1);

    void on_spinBox_threshold_gr6_valueChanged(int arg1);

    void on_spinBox_threshold_gr7_valueChanged(int arg1);

    void on_spinBox_UpdateTime_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_radioButton_NIM_clicked(bool checked);

    void on_radioButton_TTL_clicked(bool checked);

    void on_checkBox_sound_clicked(bool checked);

public slots:
    void Message(QString);
    void InitializationComplete();
    void RedrawGraphsFull(QVector<double> , QVector< QVector<double> > );
    void TransferSpeed(double);
    void TriggerRate(double);
    void GraphData(double **array, int rows, int cols);
    void PlotMask(uint);
    //void GraphData1D(double *array, int size);
    //void RedrawGraphsTest();

private:
    Ui::MainWindow *ui;
    struct TriggerValueCh
    {
        int value;
        int ch;
    };

    double x_min;
    double x_max;
    double y_min;
    double y_max;
    uint plot_mask;


    TriggerValueCh trigger_value_ch;

signals:
    void Init();
    void QuitProgram();
    void InterruptTimeout();
    void Program_the_digitizer();
    void Restart();
    void Mask_the_channels();
    void Readout_loop();

    void StopReadout_loop();
    void ContinuousTrigger();

    void ContinuousWrite();
    void SetRecordLength(double value);
    void TestPattern();

    void EnableContinuousPlot();
    void DisableContinuousPlot();
    void MaskChannel(int, bool);
    void SetTriggerValue(int, int);
    void MaskChannelAll(bool);
    void EnableSound(bool val);

    void CHANNEL_TRIGGER_signal(int, bool);
    void CHANNEL_TRIGGER_group(int, bool);
    void CHANNEL_TRIGGER_all(bool);


    void SetOutFileType(int);
    void SetEventsPerFile(int);
    void SetFolder(QString);

    void SetContinuousTrigger(bool);
    void SetRisingFalling(bool);
    void SetIsNIM(bool);
    void SetDCOffset(int, int);

    void SetExternalTrigger(bool);
    void SetTDrawFinished(long);

    void SetUpdateTime(int);
    void SetPostTrigger(int);

};

#endif // MAINWINDOW_H
