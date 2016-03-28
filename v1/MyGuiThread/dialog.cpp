#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
    mThread = new MyThread();
    connect(mThread, SIGNAL(NumberChanged(int)), this, SLOT( onNumberChanged(int) ) );
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onNumberChanged(int Number)
{
    ui->label->setText(QString::number(Number));
}

void Dialog::on_pushButton_clicked()
{

    mThread->start();
}

void Dialog::on_pushButton_2_clicked()
{
    mThread->Stop = true;
}
