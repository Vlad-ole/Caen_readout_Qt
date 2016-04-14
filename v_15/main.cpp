#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QVector< QVector<double> > array_x_data;

    array_x_data.resize(2);
    array_x_data[0].resize(10);
    array_x_data[1].resize(10);

    for(int j = 0; j < 2; j++)
    {
        for(int i = 0; i < 10; i++)
        {
            array_x_data[j][i] = i + j;
        }
    }

    qDebug() << "array_x_data.size() " << array_x_data.size() << endl;
    qDebug() << "array_x_data[0].size() " << array_x_data[0].size() << endl;
    qDebug() << "array_x_data[1].size() " << array_x_data[1].size() << endl;
    qDebug() << array_x_data[0][0] << endl;
    qDebug() << array_x_data[1][0] << endl;


    return a.exec();
}
