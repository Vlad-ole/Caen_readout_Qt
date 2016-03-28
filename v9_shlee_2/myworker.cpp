#include "myworker.h"

MyWorker::MyWorker(QObject *pobj)  : QObject(pobj), m_nValue(10)
{
    connect(&m_timer, SIGNAL(timeout()), SLOT( setNextValue() ) );
}

void MyWorker::setNextValue()
{
    for(int i=0; i < 10000000; i++)
    {
        double a = log( exp(i) * sin(i) ) * sin(log( exp(i) * sin(i) ));

    }

    emit valueChanged(--m_nValue);

    if(!m_nValue)
    {
        emit finished();
    }
}

void MyWorker::doWork()
{
    m_timer.start(1000);
}
