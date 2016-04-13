#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QVector<double> array_x_data;

    for(int j = 0; j < 1023; j++)
    {
        array_x_data.resize(20000);
        for(int i = 0; i < 20000; i++)
        {
            array_x_data[i] = i;
        }
    }

    return a.exec();
}
