#include "myworker.h"

MyWorker::MyWorker(QObject *pobj)  : QObject(pobj), m_nValue(10)
{
    connect(&m_timer, SIGNAL(timeout()), SLOT( setNextValue() ) );
}

void MyWorker::setNextValue()
{
    qDebug() << "Thread in setNextValue1 is " << QThread::currentThreadId();

    for(int i=0; i < 10000000; i++)
    {
        double a = log( exp(i) * sin(i) ) * sin(log( exp(i) * sin(i) ));

    }

    emit valueChanged(--m_nValue);

    if(!m_nValue)
    {
        emit finished();
    }

    qDebug() << "Thread in setNextValue2 is " << QThread::currentThreadId();
}

void MyWorker::doWork()
{
    qDebug() << "Thread in doWork1 is " << QThread::currentThreadId();
    m_timer.start(1000);
    qDebug() << "Thread in doWork2 is " << QThread::currentThreadId();
}
