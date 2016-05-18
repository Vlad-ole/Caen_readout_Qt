#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "WaveDump.h"
#include "WDplot.h"
#include "WDconfig.h"
#include "X742CorrectionRoutines.h"
#include "fft.h"
#include <QFileDialog>
#include "QMessageBox"

#include "QTime"

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
    connect( worker, SIGNAL( RedrawGraphsFull(QVector<double>, QVector<QVector<double> >)) , this, SLOT(RedrawGraphsFull(QVector<double>, QVector<QVector<double> >)) );
    //connect( worker, SIGNAL( RedrawGraphsTest() ), this, SLOT( RedrawGraphsTest() ));
    connect( worker, SIGNAL( TransferSpeed(double) ) , this, SLOT( TransferSpeed(double)) );
    connect( worker, SIGNAL( TriggerRate(double)) , this, SLOT( TriggerRate(double)) );

    connect( this, SIGNAL(Init()), worker, SLOT(Init()) );
    connect( this, SIGNAL( SetEventsPerFile(int) ), worker, SLOT( SetEventsPerFile(int) ), Qt::DirectConnection );
    connect( this, SIGNAL( SetFolder(QString) ) , worker, SLOT( SetFolder(QString) ), Qt::DirectConnection);
    connect( this, SIGNAL( SetOutFileType(int) ), worker, SLOT( SetOutFileType(int) ) );
    connect( this, SIGNAL( CHANNEL_TRIGGER_all(bool) ), worker, SLOT( CHANNEL_TRIGGER_all(bool) ) );
    connect( this, SIGNAL(CHANNEL_TRIGGER_signal(int,bool)), worker, SLOT(CHANNEL_TRIGGER_signal(int,bool)) );
    connect( this, SIGNAL( MaskChannelAll(bool) ), worker, SLOT( MaskChannelAll(bool) ) );
    connect( this, SIGNAL(Restart()), worker, SLOT(Restart()) );
    connect( this, SIGNAL(SetTriggerValue(int,int)), worker, SLOT(SetTriggerValue(int,int)) );
    connect( this, SIGNAL(MaskChannel(int,bool)), worker, SLOT(MaskChannel(int,bool)), Qt::DirectConnection);
    connect( this, SIGNAL(EnableContinuousPlot()), worker, SLOT(EnableContinuousPlot()),Qt::DirectConnection );
    connect( this, SIGNAL(DisableContinuousPlot()), worker, SLOT(DisableContinuousPlot()), Qt::DirectConnection );
    connect( this, SIGNAL(SetRecordLength(double)), worker, SLOT(SetRecordLength(double)) );
    connect( this, SIGNAL(Readout_loop()), worker, SLOT(Readout_loop()));
    connect( this, SIGNAL(StopReadout_loop()), worker, SLOT(StopReadout_loop()), Qt::DirectConnection );
    connect( this, SIGNAL(ContinuousTrigger()), worker, SLOT(ContinuousTrigger()), Qt::DirectConnection );
    connect( this, SIGNAL(QuitProgram()), worker, SLOT(QuitProgram()), Qt::DirectConnection );
    connect( this, SIGNAL(ContinuousWrite()), worker, SLOT( ContinuousWrite()), Qt::DirectConnection ) ;
    connect( this, SIGNAL( TestPattern() ), worker, SLOT( TestPattern() ), Qt::DirectConnection ) ;
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


    on_pushButton_2_clicked_bool = false;


    ui->CHANNEL_TRIGGER_checkBox_gr0_ch0->setToolTip("ch 0");
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch1->setToolTip("ch 1");
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch2->setToolTip("ch 2");
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch3->setToolTip("ch 3");
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch4->setToolTip("ch 4");
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch5->setToolTip("ch 5");
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch6->setToolTip("ch 6");
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch7->setToolTip("ch 7");

    ui->CHANNEL_TRIGGER_checkBox_gr1_ch8->setToolTip("ch 8");
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch9->setToolTip("ch 9");
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch10->setToolTip("ch 10");
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch11->setToolTip("ch 11");
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch12->setToolTip("ch 12");
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch13->setToolTip("ch 13");
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch14->setToolTip("ch 14");
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch15->setToolTip("ch 15");

    ui->CHANNEL_TRIGGER_checkBox_gr2_ch16->setToolTip("ch 16");
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch17->setToolTip("ch 17");
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch18->setToolTip("ch 18");
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch19->setToolTip("ch 19");
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch20->setToolTip("ch 20");
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch21->setToolTip("ch 21");
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch22->setToolTip("ch 22");
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch23->setToolTip("ch 23");

    ui->CHANNEL_TRIGGER_checkBox_gr3_ch24->setToolTip("ch 24");

    x_min = 0;
    x_max = 20000;
    y_min = -1000;
    y_max = 1000;

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

void  MainWindow::TransferSpeed(double trf_spd)
{
    ui->lcdNumber->display(trf_spd);
}

void MainWindow::TriggerRate(double trg_rate)
{
    ui->lcdNumber_2->display(trg_rate);
}

void MainWindow::InitializationComplete()
{
    ui->textBrowser->setText("Device was connected");

    ui->groupBox_3->setEnabled(true);
    ui->groupBox_7->setEnabled(true);
    ui->radioButton_13->setChecked(true);
    ui->pushButton->setStyleSheet("background-color: green");
    ui->pushButton->setEnabled(false);

///////////////
    QString x_label = "time [us]";
    QString y_label = "Amplitude [mV]";

    ui->widget_011->axisRect()->setupFullAxesBox();
    ui->widget_011->plotLayout()->insertRow(0);
    ui->widget_011->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_011, "Channel 0"));
    ui->widget_011->xAxis->setLabel(x_label);
    ui->widget_011->yAxis->setLabel(y_label);

    ui->widget_012->axisRect()->setupFullAxesBox();
    ui->widget_012->plotLayout()->insertRow(0);
    ui->widget_012->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_012, "Channel 1"));
    ui->widget_012->xAxis->setLabel(x_label);
    ui->widget_012->yAxis->setLabel(y_label);

    ui->widget_013->axisRect()->setupFullAxesBox();
    ui->widget_013->plotLayout()->insertRow(0);
    ui->widget_013->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_013, "Channel 2"));
    ui->widget_013->xAxis->setLabel(x_label);
    ui->widget_013->yAxis->setLabel(y_label);

    ui->widget_014->axisRect()->setupFullAxesBox();
    ui->widget_014->plotLayout()->insertRow(0);
    ui->widget_014->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_014, "Channel 3"));
    ui->widget_014->xAxis->setLabel(x_label);
    ui->widget_014->yAxis->setLabel(y_label);

    ui->widget_015->axisRect()->setupFullAxesBox();
    ui->widget_015->plotLayout()->insertRow(0);
    ui->widget_015->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_015, "Channel 4"));
    ui->widget_015->xAxis->setLabel(x_label);
    ui->widget_015->yAxis->setLabel(y_label);

    ///////////////
    ui->widget_021->axisRect()->setupFullAxesBox();
    ui->widget_021->plotLayout()->insertRow(0);
    ui->widget_021->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_021, "Channel 5"));
    ui->widget_021->xAxis->setLabel(x_label);
    ui->widget_021->yAxis->setLabel(y_label);

    ui->widget_022->axisRect()->setupFullAxesBox();
    ui->widget_022->plotLayout()->insertRow(0);
    ui->widget_022->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_022, "Channel 6"));
    ui->widget_022->xAxis->setLabel(x_label);
    ui->widget_022->yAxis->setLabel(y_label);

    ui->widget_023->axisRect()->setupFullAxesBox();
    ui->widget_023->plotLayout()->insertRow(0);
    ui->widget_023->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_023, "Channel 7"));
    ui->widget_023->xAxis->setLabel(x_label);
    ui->widget_023->yAxis->setLabel(y_label);

    ui->widget_024->axisRect()->setupFullAxesBox();
    ui->widget_024->plotLayout()->insertRow(0);
    ui->widget_024->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_024, "Channel 8"));
    ui->widget_024->xAxis->setLabel(x_label);
    ui->widget_024->yAxis->setLabel(y_label);


    ui->widget_025->axisRect()->setupFullAxesBox();
    ui->widget_025->plotLayout()->insertRow(0);
    ui->widget_025->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_025, "Channel 9"));
    ui->widget_025->xAxis->setLabel(x_label);
    ui->widget_025->yAxis->setLabel(y_label);

///////////////
    ui->widget_031->axisRect()->setupFullAxesBox();
    ui->widget_031->plotLayout()->insertRow(0);
    ui->widget_031->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_031, "Channel 10"));
    ui->widget_031->xAxis->setLabel(x_label);
    ui->widget_031->yAxis->setLabel(y_label);


    ui->widget_032->axisRect()->setupFullAxesBox();
    ui->widget_032->plotLayout()->insertRow(0);
    ui->widget_032->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_032, "Channel 11"));
    ui->widget_032->xAxis->setLabel(x_label);
    ui->widget_032->yAxis->setLabel(y_label);

    ui->widget_033->axisRect()->setupFullAxesBox();
    ui->widget_033->plotLayout()->insertRow(0);
    ui->widget_033->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_033, "Channel 12"));
    ui->widget_033->xAxis->setLabel(x_label);
    ui->widget_033->yAxis->setLabel(y_label);

    ui->widget_034->axisRect()->setupFullAxesBox();
    ui->widget_034->plotLayout()->insertRow(0);
    ui->widget_034->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_034, "Channel 13"));
    ui->widget_034->xAxis->setLabel(x_label);
    ui->widget_034->yAxis->setLabel(y_label);

    ui->widget_035->axisRect()->setupFullAxesBox();
    ui->widget_035->plotLayout()->insertRow(0);
    ui->widget_035->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_035, "Channel 14"));
    ui->widget_035->xAxis->setLabel(x_label);
    ui->widget_035->yAxis->setLabel(y_label);
    ///////////////

    ui->widget_041->axisRect()->setupFullAxesBox();
    ui->widget_041->plotLayout()->insertRow(0);
    ui->widget_041->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_041, "Channel 15"));
    ui->widget_041->xAxis->setLabel(x_label);
    ui->widget_041->yAxis->setLabel(y_label);

    ui->widget_042->axisRect()->setupFullAxesBox();
    ui->widget_042->plotLayout()->insertRow(0);
    ui->widget_042->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_042, "Channel 16"));
    ui->widget_042->xAxis->setLabel(x_label);
    ui->widget_042->yAxis->setLabel(y_label);

    ui->widget_043->axisRect()->setupFullAxesBox();
    ui->widget_043->plotLayout()->insertRow(0);
    ui->widget_043->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_043, "Channel 17"));
    ui->widget_043->xAxis->setLabel(x_label);
    ui->widget_043->yAxis->setLabel(y_label);

    ui->widget_044->axisRect()->setupFullAxesBox();
    ui->widget_044->plotLayout()->insertRow(0);
    ui->widget_044->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_044, "Channel 18"));
    ui->widget_044->xAxis->setLabel(x_label);
    ui->widget_044->yAxis->setLabel(y_label);

    ui->widget_045->axisRect()->setupFullAxesBox();
    ui->widget_045->plotLayout()->insertRow(0);
    ui->widget_045->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_045, "Channel 19"));
    ui->widget_045->xAxis->setLabel(x_label);
    ui->widget_045->yAxis->setLabel(y_label);

    ///////////////

    ui->widget_051->axisRect()->setupFullAxesBox();
    ui->widget_051->plotLayout()->insertRow(0);
    ui->widget_051->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_051, "Channel 20"));
    ui->widget_051->xAxis->setLabel(x_label);
    ui->widget_051->yAxis->setLabel(y_label);

    ui->widget_052->axisRect()->setupFullAxesBox();
    ui->widget_052->plotLayout()->insertRow(0);
    ui->widget_052->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_052, "Channel 21"));
    ui->widget_052->xAxis->setLabel(x_label);
    ui->widget_052->yAxis->setLabel(y_label);

    ui->widget_053->axisRect()->setupFullAxesBox();
    ui->widget_053->plotLayout()->insertRow(0);
    ui->widget_053->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_053, "Channel 22"));
    ui->widget_053->xAxis->setLabel(x_label);
    ui->widget_053->yAxis->setLabel(y_label);

    ui->widget_054->axisRect()->setupFullAxesBox();
    ui->widget_054->plotLayout()->insertRow(0);
    ui->widget_054->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_054, "Channel 23"));
    ui->widget_054->xAxis->setLabel(x_label);
    ui->widget_054->yAxis->setLabel(y_label);

    ui->widget_055->axisRect()->setupFullAxesBox();
    ui->widget_055->plotLayout()->insertRow(0);
    ui->widget_055->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_055, "Channel 24"));
    ui->widget_055->xAxis->setLabel(x_label);
    ui->widget_055->yAxis->setLabel(y_label);



    //////////////////
    //ui->widget_011->graph(0)->setName("Test");
    //ui->widget_011->


//    {
//        //Рисуем график y=x*x

//            //Сгенерируем данные
//            //Для этого создадим два массива точек:
//            //один для созранения x координат точек,
//            //а второй для y соответственно

//            double a = -1; //Начало интервала, где рисуем график по оси Ox
//            double b =  1; //Конец интервала, где рисуем график по оси Ox
//            double h = 0.01; //Шаг, с которым будем пробегать по оси Ox

//            int N=(b-a)/h + 2; //Вычисляем количество точек, которые будем отрисовывать
//            QVector<double> x(N), y(N); //Массивы координат точек

//            //Вычисляем наши данные
//            int i=0;
//            for (double X=a; X<=b; X+=h)//Пробегаем по всем точкам
//            {
//                x[i] = X;
//                y[i] = X*X;//Формула нашей функции
//                i++;
//            }

//            ui->widget_011->clearGraphs();//Если нужно, но очищаем все графики
//            //Добавляем один график в widget
//            ui->widget_011->addGraph();
//            //Говорим, что отрисовать нужно график по нашим двум массивам x и y
//            ui->widget_011->graph(0)->setData(x, y);

//            //Подписываем оси Ox и Oy
//            ui->widget_011->xAxis->setLabel("time [us]");
//            ui->widget_011->yAxis->setLabel("Amplitude [V]");

//            //Установим область, которая будет показываться на графике
//            ui->widget_011->xAxis->setRange(a, b);//Для оси Ox

//            //Для показа границ по оси Oy сложнее, так как надо по правильному
//            //вычислить минимальное и максимальное значение в векторах
//            double minY = y[0], maxY = y[0];
//            for (int i=1; i<N; i++)
//            {
//                if (y[i]<minY) minY = y[i];
//                if (y[i]>maxY) maxY = y[i];
//            }
//            ui->widget_011->yAxis->setRange(minY, maxY);//Для оси Oy

//            //И перерисуем график на нашем widget
//            ui->widget_011->replot();

//    }
}



void MainWindow::RedrawGraphsFull(QVector<double> array_x, QVector< QVector<double> > array_y)
{
    long time_label_start = get_time();

    ui->widget_011->clearGraphs();
    ui->widget_012->clearGraphs();
    ui->widget_013->clearGraphs();
    ui->widget_014->clearGraphs();
    ui->widget_015->clearGraphs();

    ui->widget_021->clearGraphs();
    ui->widget_022->clearGraphs();
    ui->widget_023->clearGraphs();
    ui->widget_024->clearGraphs();
    ui->widget_025->clearGraphs();

    ui->widget_031->clearGraphs();
    ui->widget_032->clearGraphs();
    ui->widget_033->clearGraphs();
    ui->widget_034->clearGraphs();
    ui->widget_035->clearGraphs();

    ui->widget_041->clearGraphs();
    ui->widget_042->clearGraphs();
    ui->widget_043->clearGraphs();
    ui->widget_044->clearGraphs();
    ui->widget_045->clearGraphs();

    ui->widget_051->clearGraphs();
    ui->widget_052->clearGraphs();
    ui->widget_053->clearGraphs();
    ui->widget_054->clearGraphs();
    ui->widget_055->clearGraphs();

    // ///////////////////
    ui->widget_011->addGraph();
    ui->widget_012->addGraph();
    ui->widget_013->addGraph();
    ui->widget_014->addGraph();
    ui->widget_015->addGraph();

    ui->widget_021->addGraph();
    ui->widget_022->addGraph();
    ui->widget_023->addGraph();
    ui->widget_024->addGraph();
    ui->widget_025->addGraph();

    ui->widget_031->addGraph();
    ui->widget_032->addGraph();
    ui->widget_033->addGraph();
    ui->widget_034->addGraph();
    ui->widget_035->addGraph();

    ui->widget_041->addGraph();
    ui->widget_042->addGraph();
    ui->widget_043->addGraph();
    ui->widget_044->addGraph();
    ui->widget_045->addGraph();

    ui->widget_051->addGraph();
    ui->widget_052->addGraph();
    ui->widget_053->addGraph();
    ui->widget_054->addGraph();
    ui->widget_055->addGraph();

    // /////////////////////////

//    QVector<double> array_x(100);
//    QVector<double> array_y(100);
//    for(int i = 0; i<100; i++)
//    {
//        array_x[i] = i;
//        array_y[i] = sin(qrand());
//    }

//    QVector<double> aa;
//    QVector<double> bb;
//    QVector<double> xx;

//    for(int i = 0 ; i < array_y[0].size(); i++)
//    {
//        aa.push_back(i);
//        bb.push_back(i);
//        xx.push_back(i);
//    }

    ui->widget_011->graph(0)->setData(array_x, array_y[0]);
    ui->widget_012->graph(0)->setData(array_x, array_y[1]);
    ui->widget_013->graph(0)->setData(array_x, array_y[2]);
    ui->widget_014->graph(0)->setData(array_x, array_y[3]);
    ui->widget_015->graph(0)->setData(array_x, array_y[4]);

    ui->widget_021->graph(0)->setData(array_x, array_y[5]);
    ui->widget_022->graph(0)->setData(array_x, array_y[6]);
    ui->widget_023->graph(0)->setData(array_x, array_y[7]);
    ui->widget_024->graph(0)->setData(array_x, array_y[1]);
    ui->widget_025->graph(0)->setData(array_x, array_y[1]);

    ui->widget_031->graph(0)->setData(array_x, array_y[1]);
    ui->widget_032->graph(0)->setData(array_x, array_y[1]);
    ui->widget_033->graph(0)->setData(array_x, array_y[1]);
    ui->widget_034->graph(0)->setData(array_x, array_y[1]);
    ui->widget_035->graph(0)->setData(array_x, array_y[1]);

    ui->widget_041->graph(0)->setData(array_x, array_y[1]);
    ui->widget_042->graph(0)->setData(array_x, array_y[1]);
    ui->widget_043->graph(0)->setData(array_x, array_y[1]);
    ui->widget_044->graph(0)->setData(array_x, array_y[1]);
    ui->widget_045->graph(0)->setData(array_x, array_y[1]);

    ui->widget_051->graph(0)->setData(array_x, array_y[1]);
    ui->widget_052->graph(0)->setData(array_x, array_y[1]);
    ui->widget_053->graph(0)->setData(array_x, array_y[1]);
    ui->widget_054->graph(0)->setData(array_x, array_y[1]);
    ui->widget_055->graph(0)->setData(array_x, array_y[1]);



    ///////////////////
    //ui->widget_011->graph(0)->setName("Ch 0");


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

    qDebug() << "in RedrawGraphs (time)" << get_time() - time_label_start << endl;
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

void MainWindow::GraphData(double **array, int rows, int cols)
{

}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    y_max = arg1;
    SetRangeX();
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    y_min = arg1;
    SetRangeX();
}

void MainWindow::on_spinBox_x_max_valueChanged(int arg1)
{
    x_max = arg1;
    SetRangeX();
}

void MainWindow::SetRangeX()
{
    const double x_max_misros = x_max / 1000.0;
    const double x_min_misros = x_min / 1000.0;

    //emit this->SetRecordLength(arg1);

    ui->widget_011->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_012->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_013->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_014->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_015->xAxis->setRange(x_min_misros, x_max_misros);

    ui->widget_021->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_022->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_023->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_024->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_025->xAxis->setRange(x_min_misros, x_max_misros);

    ui->widget_031->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_032->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_033->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_034->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_035->xAxis->setRange(x_min_misros, x_max_misros);

    ui->widget_041->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_042->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_043->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_044->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_045->xAxis->setRange(x_min_misros, x_max_misros);

    ui->widget_051->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_052->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_053->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_054->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_055->xAxis->setRange(x_min_misros, x_max_misros);

    ui->widget_011->yAxis->setRangeLower(y_min);
    ui->widget_012->yAxis->setRangeLower(y_min);
    ui->widget_013->yAxis->setRangeLower(y_min);
    ui->widget_014->yAxis->setRangeLower(y_min);
    ui->widget_015->yAxis->setRangeLower(y_min);

    ui->widget_021->yAxis->setRangeLower(y_min);
    ui->widget_022->yAxis->setRangeLower(y_min);
    ui->widget_023->yAxis->setRangeLower(y_min);
    ui->widget_024->yAxis->setRangeLower(y_min);
    ui->widget_025->yAxis->setRangeLower(y_min);

    ui->widget_031->yAxis->setRangeLower(y_min);
    ui->widget_032->yAxis->setRangeLower(y_min);
    ui->widget_033->yAxis->setRangeLower(y_min);
    ui->widget_034->yAxis->setRangeLower(y_min);
    ui->widget_035->yAxis->setRangeLower(y_min);

    ui->widget_041->yAxis->setRangeLower(y_min);
    ui->widget_042->yAxis->setRangeLower(y_min);
    ui->widget_043->yAxis->setRangeLower(y_min);
    ui->widget_044->yAxis->setRangeLower(y_min);
    ui->widget_045->yAxis->setRangeLower(y_min);

    ui->widget_051->yAxis->setRangeLower(y_min);
    ui->widget_052->yAxis->setRangeLower(y_min);
    ui->widget_053->yAxis->setRangeLower(y_min);
    ui->widget_054->yAxis->setRangeLower(y_min);
    ui->widget_055->yAxis->setRangeLower(y_min);

     // ------------------------------------------
    ui->widget_011->yAxis->setRangeUpper(y_max);
    ui->widget_012->yAxis->setRangeUpper(y_max);
    ui->widget_013->yAxis->setRangeUpper(y_max);
    ui->widget_014->yAxis->setRangeUpper(y_max);
    ui->widget_015->yAxis->setRangeUpper(y_max);

    ui->widget_021->yAxis->setRangeUpper(y_max);
    ui->widget_022->yAxis->setRangeUpper(y_max);
    ui->widget_023->yAxis->setRangeUpper(y_max);
    ui->widget_024->yAxis->setRangeUpper(y_max);
    ui->widget_025->yAxis->setRangeUpper(y_max);

    ui->widget_031->yAxis->setRangeUpper(y_max);
    ui->widget_032->yAxis->setRangeUpper(y_max);
    ui->widget_033->yAxis->setRangeUpper(y_max);
    ui->widget_034->yAxis->setRangeUpper(y_max);
    ui->widget_035->yAxis->setRangeUpper(y_max);

    ui->widget_041->yAxis->setRangeUpper(y_max);
    ui->widget_042->yAxis->setRangeUpper(y_max);
    ui->widget_043->yAxis->setRangeUpper(y_max);
    ui->widget_044->yAxis->setRangeUpper(y_max);
    ui->widget_045->yAxis->setRangeUpper(y_max);

    ui->widget_051->yAxis->setRangeUpper(y_max);
    ui->widget_052->yAxis->setRangeUpper(y_max);
    ui->widget_053->yAxis->setRangeUpper(y_max);
    ui->widget_054->yAxis->setRangeUpper(y_max);
    ui->widget_055->yAxis->setRangeUpper(y_max);


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

void MainWindow::on_radioButton_15_clicked(bool checked)
{
    //CAEN_DGTZ_SendSWtrigger(handle);
}


void MainWindow::on_pushButton_2_clicked()
{
    if(!on_pushButton_2_clicked_bool)
    {
        ui->pushButton_2->setStyleSheet("background-color: yellow");
        emit this->Readout_loop();
        qDebug() << "worker->WDrun.Quit == 0" << endl;
        on_pushButton_2_clicked_bool = true;

        ui->pushButton_3->setEnabled(true);
        ui->groupBox_6->setEnabled(true);
    }
    else
    {
        ui->pushButton_2->setStyleSheet("");
        emit this->StopReadout_loop();

        Sleep(1);
        ui->lcdNumber->display(0);
        ui->lcdNumber_2->display(0);

        on_pushButton_2_clicked_bool = false;
        ui->pushButton_3->setEnabled(false);
    }


}



void MainWindow::on_radioButton_15_clicked()
{
    emit this->ContinuousTrigger();
}

void MainWindow::on_pushButton_3_clicked()
{
    if(!worker->WDrun.ContinuousWrite)
        ui->pushButton_3->setStyleSheet("background-color: yellow");
    else
        ui->pushButton_3->setStyleSheet("");

    emit this->ContinuousWrite();
}

void MainWindow::on_groupBox_3_clicked()
{

}

void MainWindow::on_spinBox_4_editingFinished()
{

}

void MainWindow::on_Test_Pattern_button_clicked()
{

    if(!worker->WDcfg.TestPattern )
        ui->Test_Pattern_button->setStyleSheet("background-color: yellow");
    else
        ui->Test_Pattern_button->setStyleSheet("");

    emit this->TestPattern();


}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        emit this->EnableContinuousPlot();
        qDebug() << "EnableContinuousPlot()" << endl;
    }
    else
    {
        emit this->DisableContinuousPlot();
         qDebug() << "DisableContinuousPlot()" << endl;
    }
}

void MainWindow::on_Test_Pattern_button_clicked(bool checked)
{

}

void MainWindow::on_pushButton_5_clicked()
{
    ui->checkBox_11->setChecked(false);
    ui->checkBox_12->setChecked(false);
    ui->checkBox_13->setChecked(false);
    ui->checkBox_14->setChecked(false);
    ui->checkBox_15->setChecked(false);

    ui->checkBox_21->setChecked(false);
    ui->checkBox_22->setChecked(false);
    ui->checkBox_23->setChecked(false);
    ui->checkBox_24->setChecked(false);
    ui->checkBox_25->setChecked(false);

    ui->checkBox_31->setChecked(false);
    ui->checkBox_32->setChecked(false);
    ui->checkBox_33->setChecked(false);
    ui->checkBox_34->setChecked(false);
    ui->checkBox_35->setChecked(false);

    ui->checkBox_41->setChecked(false);
    ui->checkBox_42->setChecked(false);
    ui->checkBox_43->setChecked(false);
    ui->checkBox_44->setChecked(false);
    ui->checkBox_45->setChecked(false);

    ui->checkBox_51->setChecked(false);
    ui->checkBox_52->setChecked(false);
    ui->checkBox_53->setChecked(false);
    ui->checkBox_54->setChecked(false);
    ui->checkBox_55->setChecked(false);

    emit this->MaskChannelAll(false);

}

void MainWindow::on_pushButton_4_clicked()
{
    ui->checkBox_11->setChecked(true);
    ui->checkBox_12->setChecked(true);
    ui->checkBox_13->setChecked(true);
    ui->checkBox_14->setChecked(true);
    ui->checkBox_15->setChecked(true);

    ui->checkBox_21->setChecked(true);
    ui->checkBox_22->setChecked(true);
    ui->checkBox_23->setChecked(true);
    ui->checkBox_24->setChecked(true);
    ui->checkBox_25->setChecked(true);

    ui->checkBox_31->setChecked(true);
    ui->checkBox_32->setChecked(true);
    ui->checkBox_33->setChecked(true);
    ui->checkBox_34->setChecked(true);
    ui->checkBox_35->setChecked(true);

    ui->checkBox_41->setChecked(true);
    ui->checkBox_42->setChecked(true);
    ui->checkBox_43->setChecked(true);
    ui->checkBox_44->setChecked(true);
    ui->checkBox_45->setChecked(true);

    ui->checkBox_51->setChecked(true);
    ui->checkBox_52->setChecked(true);
    ui->checkBox_53->setChecked(true);
    ui->checkBox_54->setChecked(true);
    ui->checkBox_55->setChecked(true);


    emit this->MaskChannelAll(true);


}

void MainWindow::on_checkBox_11_clicked(bool checked)
{
    emit this->MaskChannel(0, checked);
}

void MainWindow::on_checkBox_12_clicked(bool checked)
{
    emit this->MaskChannel(1, checked);
}

void MainWindow::on_checkBox_13_clicked(bool checked)
{
    emit this->MaskChannel(2, checked);
}

void MainWindow::on_checkBox_14_clicked(bool checked)
{
    emit this->MaskChannel(3, checked);
}

void MainWindow::on_checkBox_15_clicked(bool checked)
{
    emit this->MaskChannel(4, checked);
}

////////////////////////////////////////

void MainWindow::on_checkBox_21_clicked(bool checked)
{
    emit this->MaskChannel(5, checked);
}

void MainWindow::on_checkBox_22_clicked(bool checked)
{
    emit this->MaskChannel(6, checked);
}

void MainWindow::on_checkBox_23_clicked(bool checked)
{
    emit this->MaskChannel(7, checked);
}

void MainWindow::on_checkBox_24_clicked(bool checked)
{
    emit this->MaskChannel(8, checked);
}

////////////////////////////////////////

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    trigger_value_ch.value = value;
    qDebug() << "trigger_value_ch.value = " << value << endl;
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    trigger_value_ch.ch = arg1;
    qDebug() << "trigger_value_ch.ch = " << arg1 << endl;
}

void MainWindow::on_pushButton_6_clicked()
{
    emit this->SetTriggerValue(trigger_value_ch.ch, trigger_value_ch.value);
    qDebug() << "SetTriggerValue_clicked()" << endl;
}

void MainWindow::on_pushButton_Reprogram_clicked()
{
    if(on_pushButton_2_clicked_bool)
    {
        ui->pushButton_2->setStyleSheet("");
        emit this->StopReadout_loop();

        Sleep(1);
        ui->lcdNumber->display(0);
        ui->lcdNumber_2->display(0);

        on_pushButton_2_clicked_bool = false;
        ui->groupBox_6->setEnabled(false);
    }

    emit this->Restart();

    qDebug() << "on_pushButton_Reprogram_clicked" << endl;
}



void MainWindow::on_checkBox_25_clicked(bool checked)
{
    emit this->MaskChannel(9, checked);
}

void MainWindow::on_checkBox_31_clicked(bool checked)
{
    emit this->MaskChannel(10, checked);
}

void MainWindow::on_checkBox_32_clicked(bool checked)
{
    emit this->MaskChannel(11, checked);
}

void MainWindow::on_checkBox_33_clicked(bool checked)
{
    emit this->MaskChannel(12, checked);
}

void MainWindow::on_checkBox_34_clicked(bool checked)
{
    emit this->MaskChannel(13, checked);
}

void MainWindow::on_checkBox_35_clicked(bool checked)
{
    emit this->MaskChannel(14, checked);
}



void MainWindow::on_checkBox_41_clicked(bool checked)
{
    emit this->MaskChannel(15, checked);
}

void MainWindow::on_checkBox_42_clicked(bool checked)
{
    emit this->MaskChannel(16, checked);
}



void MainWindow::on_checkBox_43_clicked(bool checked)
{
    emit this->MaskChannel(17, checked);
}

void MainWindow::on_checkBox_44_clicked(bool checked)
{
    emit this->MaskChannel(18, checked);
}



void MainWindow::on_checkBox_45_clicked(bool checked)
{
    emit this->MaskChannel(19, checked);
}



void MainWindow::on_checkBox_51_clicked(bool checked)
{
    emit this->MaskChannel(20, checked);
}



void MainWindow::on_checkBox_52_clicked(bool checked)
{
    emit this->MaskChannel(21, checked);
}



void MainWindow::on_checkBox_53_clicked(bool checked)
{
    emit this->MaskChannel(22, checked);
}



void MainWindow::on_checkBox_54_clicked(bool checked)
{
    emit this->MaskChannel(23, checked);
}



void MainWindow::on_checkBox_55_clicked(bool checked)
{
    emit this->MaskChannel(24, checked);
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch0->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch1->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch2->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch3->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch4->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch5->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch6->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch7->setChecked(true);

    ui->CHANNEL_TRIGGER_checkBox_gr1_ch8->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch9->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch10->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch11->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch12->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch13->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch14->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch15->setChecked(true);

    ui->CHANNEL_TRIGGER_checkBox_gr2_ch16->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch17->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch18->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch19->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch20->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch21->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch22->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch23->setChecked(true);

    ui->CHANNEL_TRIGGER_checkBox_gr3_ch24->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr3_ch25->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr3_ch26->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr3_ch27->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr3_ch28->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr3_ch29->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr3_ch30->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr3_ch31->setChecked(true);

    ui->CHANNEL_TRIGGER_checkBox_gr4_ch32->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr4_ch33->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr4_ch34->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr4_ch35->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr4_ch36->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr4_ch37->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr4_ch38->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr4_ch39->setChecked(true);

    ui->CHANNEL_TRIGGER_checkBox_gr5_ch40->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr5_ch41->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr5_ch42->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr5_ch43->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr5_ch44->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr5_ch45->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr5_ch46->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr5_ch47->setChecked(true);

    ui->CHANNEL_TRIGGER_checkBox_gr6_ch48->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr6_ch49->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr6_ch50->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr6_ch51->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr6_ch52->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr6_ch53->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr6_ch54->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr6_ch55->setChecked(true);

    ui->CHANNEL_TRIGGER_checkBox_gr7_ch56->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr7_ch57->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr7_ch58->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr7_ch59->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr7_ch60->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr7_ch61->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr7_ch62->setChecked(true);
    ui->CHANNEL_TRIGGER_checkBox_gr7_ch63->setChecked(true);

    emit this->CHANNEL_TRIGGER_all(true);
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch0->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch1->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch2->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch3->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch4->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch5->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch6->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr0_ch7->setChecked(false);

    ui->CHANNEL_TRIGGER_checkBox_gr1_ch8->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch9->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch10->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch11->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch12->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch13->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch14->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr1_ch15->setChecked(false);

    ui->CHANNEL_TRIGGER_checkBox_gr2_ch16->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch17->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch18->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch19->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch20->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch21->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch22->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr2_ch23->setChecked(false);

    ui->CHANNEL_TRIGGER_checkBox_gr3_ch24->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr3_ch25->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr3_ch26->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr3_ch27->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr3_ch28->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr3_ch29->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr3_ch30->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr3_ch31->setChecked(false);

    ui->CHANNEL_TRIGGER_checkBox_gr4_ch32->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr4_ch33->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr4_ch34->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr4_ch35->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr4_ch36->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr4_ch37->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr4_ch38->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr4_ch39->setChecked(false);

    ui->CHANNEL_TRIGGER_checkBox_gr5_ch40->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr5_ch41->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr5_ch42->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr5_ch43->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr5_ch44->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr5_ch45->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr5_ch46->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr5_ch47->setChecked(false);

    ui->CHANNEL_TRIGGER_checkBox_gr6_ch48->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr6_ch49->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr6_ch50->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr6_ch51->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr6_ch52->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr6_ch53->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr6_ch54->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr6_ch55->setChecked(false);

    ui->CHANNEL_TRIGGER_checkBox_gr7_ch56->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr7_ch57->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr7_ch58->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr7_ch59->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr7_ch60->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr7_ch61->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr7_ch62->setChecked(false);
    ui->CHANNEL_TRIGGER_checkBox_gr7_ch63->setChecked(false);

    emit this->CHANNEL_TRIGGER_all(false);
}

void MainWindow::on_checkBox_12_clicked()
{

}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr0_ch0_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(0, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr0_ch1_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(1, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr0_ch2_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(2, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr0_ch3_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(3, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr0_ch4_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(4, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr0_ch5_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(5, checked);
}



void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr0_ch6_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(6, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr0_ch7_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(7, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr1_ch8_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(8, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr1_ch9_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(9, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr1_ch10_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(10, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr1_ch11_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(11, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr1_ch12_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(12, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr1_ch13_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(13, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr1_ch14_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(14, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr1_ch15_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(15, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr2_ch16_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(16, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr2_ch17_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(17, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr2_ch18_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(18, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr2_ch19_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(19, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr2_ch20_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(20, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr2_ch21_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(21, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr2_ch22_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(22, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr2_ch23_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(23, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr3_ch24_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(24, checked);
}

void MainWindow::on_radioButton_9_clicked(bool checked)
{
    if(checked)
        emit this->SetOutFileType(ASCII);
}

void MainWindow::on_radioButton_10_clicked(bool checked)
{
    if(checked)
        emit this->SetOutFileType(BINARY);
}

void MainWindow::on_radioButton_root_tree_clicked(bool checked)
{
    if(checked)
        emit this->SetOutFileType(ROOT_TREE);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    qDebug() << "events_per_file on_spinBox_valueChanged = " << arg1 << endl;
    emit this->SetEventsPerFile(arg1);
}

void MainWindow::on_pushButton_choose_folder_clicked()
{
    //QString filename = QFileDialog::getOpenFileName(this, tr("Open file"), "C://", "All files (*.*)");
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    dir.replace("/","\\");
    dir += "\\";
    //dir = QDir::fromNativeSeparators(dir);
    qDebug() << "dir = " << dir << endl;

    emit this->SetFolder(dir);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr3_ch25_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(25, checked);
}



void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr3_ch26_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(26, checked);
}



void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr3_ch27_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(27, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr3_ch28_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(28, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr3_ch29_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(29, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr3_ch30_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(30, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr3_ch31_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(31, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr4_ch32_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(32, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr4_ch33_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(33, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr4_ch34_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(34, checked);
}



void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr4_ch35_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(35, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr4_ch36_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(36, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr4_ch37_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(37, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr4_ch38_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(38, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr4_ch39_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(39, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr5_ch40_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(40, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr5_ch41_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(41, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr5_ch42_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(42, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr5_ch43_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(43, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr5_ch44_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(44, checked);
}



void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr5_ch45_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(45, checked);
}



void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr5_ch46_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(46, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr5_ch47_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(47, checked);
}



void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr6_ch48_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(48, checked);
}



void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr6_ch49_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(49, checked);
}



void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr6_ch50_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(50, checked);
}



void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr6_ch51_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(51, checked);
}


void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr6_ch52_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(52, checked);
}



void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr6_ch53_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(53, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr6_ch54_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(54, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr6_ch55_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(55, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr7_ch56_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(56, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr7_ch57_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(57, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr7_ch58_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(58, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr7_ch59_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(59, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr7_ch60_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(60, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr7_ch61_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(61, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr7_ch62_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(62, checked);
}

void MainWindow::on_CHANNEL_TRIGGER_checkBox_gr7_ch63_clicked(bool checked)
{
    emit this->CHANNEL_TRIGGER_signal(63, checked);
}



void MainWindow::on_spinBox_x_min_valueChanged(int arg1)
{
    x_min = arg1;
    SetRangeX();
}
