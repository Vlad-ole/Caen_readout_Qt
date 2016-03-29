#include "myworker.h"
#include <QtCore>

MyWorker::MyWorker()
{

}

void MyWorker::work()
{
    qDebug() << "Thread in work is " << QThread::currentThreadId();

    for(int i=0; i < 10000000; i++)
    {
        double a = log( exp(i) * sin(i) ) * sin(log( exp(i) * sin(i) ));

    }

    //qDebug() << "Thread in work2 is " << QThread::currentThreadId();
    emit finished();

    qDebug() << "Caclucations finished! ";
}

void MyWorker::work_2()
{
    qDebug() << "Thread in work_2 is " << QThread::currentThreadId();

    for(int i=0; i < 10000000; i++)
    {
        double a = log( exp(i) * sin(i) ) * sin(log( exp(i) * sin(i) ));

    }

    qDebug() << "Caclucations 2 finished! ";
}
