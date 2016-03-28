#include <QApplication>
#include <QtCore>
#include <QLCDNumber>
#include "myworker.h"

class MyThread : public QThread
{
    Q_OBJECT

public:
    MyThread()
    {

    }

    void run()
    {
        exec();
    }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLCDNumber lcd;
    MyThread thread;
    MyWorker worker;


    QObject::connect(&worker, SIGNAL( valueChanged(int) ), &lcd, SLOT( display(int) ) );

    lcd.setSegmentStyle(QLCDNumber::Filled);
    lcd.display(10);
    lcd.resize(220, 90);
    lcd.show();

    worker.moveToThread(&thread);

    QObject::connect(&worker, SIGNAL( finished() ) , &thread, SLOT( quit() ) );
    QObject::connect(&thread, SIGNAL( finished() ) , &thread, SLOT( quit() ) );

    thread.start();
    worker.doWork();

    return a.exec();
}


#include "main.moc"
