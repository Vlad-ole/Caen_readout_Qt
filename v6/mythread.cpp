#include "mythread.h"
#include <QtCore>
#include <QDebug>
#include <iostream>

MyThread::MyThread()
{

}

void MyThread::run()
{
    //qDebug() << this->name << " Running" ;
    std::cout << this->name.toStdString()<< " Running";

    for(int i=0; i<10; i++)
    {
        //qDebug() << this->name << i ;
        std::cout << this->name.toStdString()<< i << "\n";
    }
}
