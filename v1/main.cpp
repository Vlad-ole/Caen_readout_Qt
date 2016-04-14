#include "mainwindow.h"
#include <QApplication>

#include "WaveDump.h"
#include "mythread.h"
#include "myworker.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    qRegisterMetaType<QVector<double> >("QVector<double>");
    qRegisterMetaType<QVector< QVector<double> > >("QVector< QVector<double> >");
    return a.exec();
}
