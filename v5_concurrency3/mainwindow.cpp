#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
#include <iostream>
#include <math.h>

#include "mythread.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mThread1 = new MyThread();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    //ui->pushButton->setStyleSheet("background-color: red");

    //msleep(1000);


    mThread1->start();



//    ui->pushButton->setStyleSheet("background-color: green");
}

void MainWindow::on_pushButton_2_clicked()
{
    mThread1->Stop = true;
}

void MainWindow::onNumberChanged(int Number)
{
    ui->lcdNumber->display(Number);
}

