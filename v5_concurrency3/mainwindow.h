#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mythread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MyThread *mThread1;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

public slots:
    void onNumberChanged(int);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
