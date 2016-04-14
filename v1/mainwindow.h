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

};

#endif // MAINWINDOW_H
