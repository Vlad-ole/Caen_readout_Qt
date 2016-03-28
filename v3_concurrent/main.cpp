#include "mainwindow.h"
#include <QApplication>
#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    void run()
    {
        for(int i=0; i<=100; i++)
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

    MyThread thread;

    QObject::connect(&thread, SIGNAL(progress(int), &progressBar, SLOT(setValue(int))));

    MainWindow w;
    w.show();

    return a.exec();
}
