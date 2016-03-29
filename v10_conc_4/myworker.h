#ifndef MYWORKER_H
#define MYWORKER_H

#include <QtCore>

class MyWorker : public QObject
{
    Q_OBJECT
public:
    MyWorker();

public slots:
    void work();
    void work_2();
signals:
    void finished();
};

#endif // MYWORKER_H
