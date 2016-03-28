#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( this, SIGNAL(doIt()), this, SLOT(slot()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendSignal()
{
    emit doIt();
}

void MainWindow::sendSignal(int a)
{
    emit doIt(a);
}

void MainWindow::slot()
{
    qDebug() << sender()->objectName();
}
