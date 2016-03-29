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

    return a.exec();
}
