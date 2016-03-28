#include "mythread.h"
#include <QtCore>
#include <QDebug>

MyThread::MyThread()
{

}

void MyThread::run()
{
    qDebug() << this->name << " Running" ;
    for(int i=0; i < 10000000; i++)
    {
        double a = log( exp(i) * sin(i) ) * sin(log( exp(i) * sin(i) ));

    }

    int b = 10;

    emit NumberChanged(b);

}
