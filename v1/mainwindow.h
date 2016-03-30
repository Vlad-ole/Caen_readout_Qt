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

    void on_pushButton_4_clicked();

    void on_radioButton_15_clicked();

public slots:
    void Message(QString);
    void InitializationComplete();
    void RedrawGraphs();

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

};

#endif // MAINWINDOW_H
