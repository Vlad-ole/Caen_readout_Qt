#include "mainwindow.h"
#include <QApplication>
#include <QProgressBar>
#include <QtCore>

class MyThread : public QThread
{
    Q_OBJECT

public:
    //MyThread();


    void run()
    {
        for(int i = 0; i<=100; i++)
        {
            usleep(100000);
            emit progress(i);
        }
    }
signals:
    void progress(int);

};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QProgressBar prb;
    MyThread thread;

    QObject::connect(&thread, SIGNAL(progress(int)), &prb, SLOT(setValue(int)) );

    prb.show();
    thread.start();

    return a.exec();
}

#include "main.moc"
