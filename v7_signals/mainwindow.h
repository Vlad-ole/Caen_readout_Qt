#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void sendSignal();
    void sendSignal(int);

private:
    Ui::MainWindow *ui;

signals:
    void doIt();
    void doIt(int);

public slots:
    void slot();


};

#endif // MAINWINDOW_H
