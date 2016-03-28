#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QtCore>

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread();
    void run();
    QString name;
    bool Stop;

    void sendSignal();

signals:
    void NumberChanged(int);
    void doIt();
};

#endif // MYTHREAD_H
