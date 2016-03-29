#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qDebug() << "Thread in main1 is " << QThread::currentThreadId();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
