#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "WaveDump.h"
#include "WDplot.h"
#include "WDconfig.h"
#include "X742CorrectionRoutines.h"
#include "fft.h"

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    qDebug() << "Thread in MainWindow is " << QThread::currentThreadId();

    ui->setupUi(this);
    ui->groupBox_3->setEnabled(false);
    ui->groupBox_6->setEnabled(false);
    ui->groupBox_7->setEnabled(false);
    ui->pushButton->setStyleSheet("background-color: red");

    worker = new MyWorker();
    thread = new QThread();

    //connect signal and slots in different threads
    connect( worker, SIGNAL(Message(QString)), this, SLOT(Message(QString)) );
    connect( worker, SIGNAL(InitializationComplete()), this, SLOT(InitializationComplete()) );
    connect( worker, SIGNAL( RedrawGraphs() ), this, SLOT( RedrawGraphs() ) );

    connect( this, SIGNAL(Init()), worker, SLOT(Init()) );
    connect( this, SIGNAL(Readout_loop()), worker, SLOT(Readout_loop()) );
    connect( this, SIGNAL(StopReadout_loop()), worker, SLOT(StopReadout_loop()), Qt::DirectConnection );
    connect( this, SIGNAL(ContinuousTrigger()), worker, SLOT(ContinuousTrigger()), Qt::DirectConnection );
    connect( this, SIGNAL(QuitProgram()), worker, SLOT(QuitProgram()), Qt::DirectConnection );
    //connect( this, SIGNAL(Mask_the_channels()), worker, SLOT(Mask_the_channels()) );
    //connect( this, SIGNAL(Program_the_digitizer()), worker, SLOT(Program_the_digitizer()) );

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
    qDebug() << "Thread in ~MainWindow() is " << QThread::currentThreadId();
    delete ui;
    emit this->QuitProgram();
}

//connect
void MainWindow::on_pushButton_clicked()
{
    emit this->Init();
    //emit this->Mask_the_channels();
    //emit this->Program_the_digitizer();
}

void MainWindow::InitializationComplete()
{
    ui->textBrowser->setText("Device was connected");
    ui->groupBox_3->setEnabled(true);
    ui->groupBox_6->setEnabled(true);
    ui->groupBox_7->setEnabled(true);
    ui->radioButton_13->setChecked(true);
    ui->pushButton->setStyleSheet("background-color: green");
    ui->pushButton->setEnabled(false);

///////////////
    ui->widget_011->xAxis->setLabel("time [us]");
    ui->widget_011->yAxis->setLabel("Amplitude [V]");

    ui->widget_012->xAxis->setLabel("time [us]");
    ui->widget_012->yAxis->setLabel("Amplitude [V]");

    ui->widget_013->xAxis->setLabel("time [us]");
    ui->widget_013->yAxis->setLabel("Amplitude [V]");

    ui->widget_014->xAxis->setLabel("time [us]");
    ui->widget_014->yAxis->setLabel("Amplitude [V]");

    ui->widget_015->xAxis->setLabel("time [us]");
    ui->widget_015->yAxis->setLabel("Amplitude [V]");

    ///////////////
    ui->widget_021->xAxis->setLabel("time [us]");
    ui->widget_021->yAxis->setLabel("Amplitude [V]");

    ui->widget_022->xAxis->setLabel("time [us]");
    ui->widget_022->yAxis->setLabel("Amplitude [V]");

    ui->widget_023->xAxis->setLabel("time [us]");
    ui->widget_023->yAxis->setLabel("Amplitude [V]");

    ui->widget_024->xAxis->setLabel("time [us]");
    ui->widget_024->yAxis->setLabel("Amplitude [V]");

    ui->widget_025->xAxis->setLabel("time [us]");
    ui->widget_025->yAxis->setLabel("Amplitude [V]");

///////////////
    ui->widget_031->xAxis->setLabel("time [us]");
    ui->widget_031->yAxis->setLabel("Amplitude [V]");

    ui->widget_032->xAxis->setLabel("time [us]");
    ui->widget_032->yAxis->setLabel("Amplitude [V]");

    ui->widget_033->xAxis->setLabel("time [us]");
    ui->widget_033->yAxis->setLabel("Amplitude [V]");

    ui->widget_034->xAxis->setLabel("time [us]");
    ui->widget_034->yAxis->setLabel("Amplitude [V]");

    ui->widget_035->xAxis->setLabel("time [us]");
    ui->widget_035->yAxis->setLabel("Amplitude [V]");
    ///////////////

    ui->widget_041->xAxis->setLabel("time [us]");
    ui->widget_041->yAxis->setLabel("Amplitude [V]");

    ui->widget_042->xAxis->setLabel("time [us]");
    ui->widget_042->yAxis->setLabel("Amplitude [V]");

    ui->widget_043->xAxis->setLabel("time [us]");
    ui->widget_043->yAxis->setLabel("Amplitude [V]");

    ui->widget_044->xAxis->setLabel("time [us]");
    ui->widget_044->yAxis->setLabel("Amplitude [V]");

    ui->widget_045->xAxis->setLabel("time [us]");
    ui->widget_045->yAxis->setLabel("Amplitude [V]");

    ///////////////

    ui->widget_051->xAxis->setLabel("time [us]");
    ui->widget_051->yAxis->setLabel("Amplitude [V]");

    ui->widget_052->xAxis->setLabel("time [us]");
    ui->widget_052->yAxis->setLabel("Amplitude [V]");

    ui->widget_053->xAxis->setLabel("time [us]");
    ui->widget_053->yAxis->setLabel("Amplitude [V]");

    ui->widget_054->xAxis->setLabel("time [us]");
    ui->widget_054->yAxis->setLabel("Amplitude [V]");

    ui->widget_055->xAxis->setLabel("time [us]");
    ui->widget_055->yAxis->setLabel("Amplitude [V]");



    {
        //Рисуем график y=x*x

            //Сгенерируем данные
            //Для этого создадим два массива точек:
            //один для созранения x координат точек,
            //а второй для y соответственно

            double a = -1; //Начало интервала, где рисуем график по оси Ox
            double b =  1; //Конец интервала, где рисуем график по оси Ox
            double h = 0.01; //Шаг, с которым будем пробегать по оси Ox

            int N=(b-a)/h + 2; //Вычисляем количество точек, которые будем отрисовывать
            QVector<double> x(N), y(N); //Массивы координат точек

            //Вычисляем наши данные
            int i=0;
            for (double X=a; X<=b; X+=h)//Пробегаем по всем точкам
            {
                x[i] = X;
                y[i] = X*X;//Формула нашей функции
                i++;
            }

            ui->widget_011->clearGraphs();//Если нужно, но очищаем все графики
            //Добавляем один график в widget
            ui->widget_011->addGraph();
            //Говорим, что отрисовать нужно график по нашим двум массивам x и y
            ui->widget_011->graph(0)->setData(x, y);

            //Подписываем оси Ox и Oy
            ui->widget_011->xAxis->setLabel("time [us]");
            ui->widget_011->yAxis->setLabel("Amplitude [V]");

            //Установим область, которая будет показываться на графике
            ui->widget_011->xAxis->setRange(a, b);//Для оси Ox

            //Для показа границ по оси Oy сложнее, так как надо по правильному
            //вычислить минимальное и максимальное значение в векторах
            double minY = y[0], maxY = y[0];
            for (int i=1; i<N; i++)
            {
                if (y[i]<minY) minY = y[i];
                if (y[i]>maxY) maxY = y[i];
            }
            ui->widget_011->yAxis->setRange(minY, maxY);//Для оси Oy

            //И перерисуем график на нашем widget
            ui->widget_011->replot();

    }
}

void MainWindow::RedrawGraphs()
{
    ui->widget_011->clearGraphs();
    ui->widget_011->addGraph();
    //ui->widget_011->graph(0)->setData(x, y);
    //ui->widget_011->xAxis->setRange(a, b);
    //ui->widget_011->yAxis->setRange(minY, maxY);

    ui->widget_011->replot();
    ui->widget_012->replot();
    ui->widget_013->replot();
    ui->widget_014->replot();
    ui->widget_015->replot();

    ui->widget_021->replot();
    ui->widget_022->replot();
    ui->widget_023->replot();
    ui->widget_024->replot();
    ui->widget_025->replot();

    ui->widget_031->replot();
    ui->widget_032->replot();
    ui->widget_033->replot();
    ui->widget_034->replot();
    ui->widget_035->replot();

    ui->widget_041->replot();
    ui->widget_042->replot();
    ui->widget_043->replot();
    ui->widget_044->replot();
    ui->widget_045->replot();

    ui->widget_051->replot();
    ui->widget_052->replot();
    ui->widget_053->replot();
    ui->widget_054->replot();
    ui->widget_055->replot();

}

void MainWindow::Message(QString s)
{
    ui->textBrowser->setText(s);
}


void MainWindow::on_radioButton_13_clicked()
{
    ui->spinBox_2->setEnabled(true);
    ui->groupBox_2->setEnabled(true);
}

void MainWindow::on_radioButton_12_clicked()
{
    ui->spinBox_2->setEnabled(false);
    ui->groupBox_2->setEnabled(false);
}

void MainWindow::on_checkBox_clicked()
{

}

void MainWindow::on_spinBox_3_valueChanged(int arg1)
{

}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    ui->widget_011->yAxis->setRangeUpper(arg1);
    ui->widget_012->yAxis->setRangeUpper(arg1);
    ui->widget_013->yAxis->setRangeUpper(arg1);
    ui->widget_014->yAxis->setRangeUpper(arg1);
    ui->widget_015->yAxis->setRangeUpper(arg1);

    ui->widget_021->yAxis->setRangeUpper(arg1);
    ui->widget_022->yAxis->setRangeUpper(arg1);
    ui->widget_023->yAxis->setRangeUpper(arg1);
    ui->widget_024->yAxis->setRangeUpper(arg1);
    ui->widget_025->yAxis->setRangeUpper(arg1);

    ui->widget_031->yAxis->setRangeUpper(arg1);
    ui->widget_032->yAxis->setRangeUpper(arg1);
    ui->widget_033->yAxis->setRangeUpper(arg1);
    ui->widget_034->yAxis->setRangeUpper(arg1);
    ui->widget_035->yAxis->setRangeUpper(arg1);

    ui->widget_041->yAxis->setRangeUpper(arg1);
    ui->widget_042->yAxis->setRangeUpper(arg1);
    ui->widget_043->yAxis->setRangeUpper(arg1);
    ui->widget_044->yAxis->setRangeUpper(arg1);
    ui->widget_045->yAxis->setRangeUpper(arg1);

    ui->widget_051->yAxis->setRangeUpper(arg1);
    ui->widget_052->yAxis->setRangeUpper(arg1);
    ui->widget_053->yAxis->setRangeUpper(arg1);
    ui->widget_054->yAxis->setRangeUpper(arg1);
    ui->widget_055->yAxis->setRangeUpper(arg1);

    ui->widget_011->replot();
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    ui->widget_011->yAxis->setRangeLower(arg1);
    ui->widget_012->yAxis->setRangeLower(arg1);
    ui->widget_013->yAxis->setRangeLower(arg1);
    ui->widget_014->yAxis->setRangeLower(arg1);
    ui->widget_015->yAxis->setRangeLower(arg1);

    ui->widget_021->yAxis->setRangeLower(arg1);
    ui->widget_022->yAxis->setRangeLower(arg1);
    ui->widget_023->yAxis->setRangeLower(arg1);
    ui->widget_024->yAxis->setRangeLower(arg1);
    ui->widget_025->yAxis->setRangeLower(arg1);

    ui->widget_031->yAxis->setRangeLower(arg1);
    ui->widget_032->yAxis->setRangeLower(arg1);
    ui->widget_033->yAxis->setRangeLower(arg1);
    ui->widget_034->yAxis->setRangeLower(arg1);
    ui->widget_035->yAxis->setRangeLower(arg1);

    ui->widget_041->yAxis->setRangeLower(arg1);
    ui->widget_042->yAxis->setRangeLower(arg1);
    ui->widget_043->yAxis->setRangeLower(arg1);
    ui->widget_044->yAxis->setRangeLower(arg1);
    ui->widget_045->yAxis->setRangeLower(arg1);

    ui->widget_051->yAxis->setRangeLower(arg1);
    ui->widget_052->yAxis->setRangeLower(arg1);
    ui->widget_053->yAxis->setRangeLower(arg1);
    ui->widget_054->yAxis->setRangeLower(arg1);
    ui->widget_055->yAxis->setRangeLower(arg1);

    ui->widget_011->replot();
}

void MainWindow::on_spinBox_4_valueChanged(int arg1)
{
    const double sampling_rate = 4; // ns

    ui->widget_011->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_012->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_013->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_014->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_015->xAxis->setRange(0, arg1*4.0/1000);

    ui->widget_021->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_022->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_023->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_024->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_025->xAxis->setRange(0, arg1*4.0/1000);

    ui->widget_031->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_032->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_033->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_034->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_035->xAxis->setRange(0, arg1*4.0/1000);

    ui->widget_041->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_042->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_043->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_044->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_045->xAxis->setRange(0, arg1*4.0/1000);

    ui->widget_051->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_052->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_053->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_054->xAxis->setRange(0, arg1*4.0/1000);
    ui->widget_055->xAxis->setRange(0, arg1*4.0/1000);


    ui->widget_011->replot();
}

void MainWindow::on_radioButton_15_clicked(bool checked)
{
    //CAEN_DGTZ_SendSWtrigger(handle);
}


void MainWindow::on_pushButton_2_clicked()
{
    emit this->Readout_loop();
}

void MainWindow::on_pushButton_4_clicked()
{
    emit this->StopReadout_loop();
}

void MainWindow::on_radioButton_15_clicked()
{
    emit this->ContinuousTrigger();
}
