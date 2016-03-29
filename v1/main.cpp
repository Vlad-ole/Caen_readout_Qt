#include "mainwindow.h"
#include <QApplication>

#include "WaveDump.h"
#include "mythread.h"
#include "myworker.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    //MyThread thread;
    //MyWorker worker;

    //worker.moveToThread(&thread);
    //thread.start();

    w.show();

    return a.exec();
}
