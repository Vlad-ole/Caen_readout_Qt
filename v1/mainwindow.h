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


    void on_radioButton_15_clicked();

    void on_pushButton_3_clicked();

    void on_groupBox_3_clicked();

    void on_spinBox_4_editingFinished();

    void on_Test_Pattern_button_clicked();

    void on_checkBox_clicked(bool checked);

    void on_Test_Pattern_button_clicked(bool checked);

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_checkBox_11_clicked(bool checked);

    void on_checkBox_12_clicked(bool checked);

    void on_checkBox_13_clicked(bool checked);

    void on_checkBox_14_clicked(bool checked);

    void on_checkBox_15_clicked(bool checked);

    void on_checkBox_21_clicked(bool checked);

    void on_checkBox_22_clicked(bool checked);

    void on_checkBox_23_clicked(bool checked);

    void on_verticalSlider_valueChanged(int value);

    void on_spinBox_2_valueChanged(int arg1);

    void on_pushButton_6_clicked();

    void on_pushButton_Reprogram_clicked();

    void on_checkBox_24_clicked(bool checked);

    void on_checkBox_25_clicked(bool checked);

    void on_checkBox_31_clicked(bool checked);

    void on_checkBox_32_clicked(bool checked);

    void on_checkBox_33_clicked(bool checked);

    void on_checkBox_34_clicked(bool checked);

    void on_checkBox_35_clicked(bool checked);

    void on_checkBox_41_clicked(bool checked);

    void on_checkBox_42_clicked(bool checked);

    void on_checkBox_43_clicked(bool checked);

    void on_checkBox_44_clicked(bool checked);

    void on_checkBox_45_clicked(bool checked);

    void on_checkBox_51_clicked(bool checked);

    void on_checkBox_52_clicked(bool checked);

    void on_checkBox_53_clicked(bool checked);

    void on_checkBox_54_clicked(bool checked);

    void on_checkBox_55_clicked(bool checked);

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_checkBox_12_clicked();

    void on_CHANNEL_TRIGGER_checkBox_11_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_12_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_13_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_14_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_15_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_21_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_22_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_23_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_24_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_25_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_31_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_32_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_33_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_34_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_35_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_41_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_42_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_43_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_44_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_45_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_51_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_52_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_53_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_54_clicked(bool checked);

    void on_CHANNEL_TRIGGER_checkBox_55_clicked(bool checked);

    void on_radioButton_9_clicked(bool checked);

    void on_radioButton_10_clicked(bool checked);

    void on_radioButton_root_tree_clicked(bool checked);

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_choose_folder_clicked();

public slots:
    void Message(QString);
    void InitializationComplete();
    void RedrawGraphsFull(QVector<double> , QVector< QVector<double> > );
    void TransferSpeed(double);
    void TriggerRate(double);
    void GraphData(double **array, int rows, int cols);
    //void GraphData1D(double *array, int size);
    //void RedrawGraphsTest();

private:
    Ui::MainWindow *ui;
    struct TriggerValueCh
    {
        int value;
        int ch;
    };



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
    void CHANNEL_TRIGGER_signal(int, bool);
    void CHANNEL_TRIGGER_all(bool);
    void SetOutFileType(int);
    void SetEventsPerFile(int);
    void SetFolder(QString);

};

#endif // MAINWINDOW_H
