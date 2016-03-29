#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore>
#include "myworker.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug() << "Thread in MainWindow is " << QThread::currentThreadId();
    ui->setupUi(this);

    worker = new MyWorker();
    thread = new QThread();

    connect( this, SIGNAL(Start_work()), worker, SLOT(work()) );
    connect( this, SIGNAL(Start_work_2()), worker, SLOT(work_2()) );

    // delete the worker obj whenever this obj is destroyed
    connect( this, SIGNAL(destroyed()), worker, SLOT(deleteLater()) );

    // stop the thread whenever the worker is destroyed
    connect( worker, SIGNAL(destroyed()), thread, SLOT(quit()) );

    // clean up the thread
    connect( thread, SIGNAL(finished()), thread, SLOT(deleteLater()) );

    worker->moveToThread( thread );
    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    emit this->Start_work();
}

void MainWindow::on_pushButton_2_clicked()
{
    emit this->Start_work_2();

}
