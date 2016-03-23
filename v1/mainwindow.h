#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CAENDigitizerType.h"

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
    //int  handle;
    //CAEN_DGTZ_ErrorCode ret;
    //char *buffer;

    //uint32_t AllocatedSize;
    //uint32_t BufferSize;
    //uint32_t NumEvents;
};

#endif // MAINWINDOW_H
