#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "WaveDump.h"
#include "WDplot.h"
#include "WDconfig.h"
#include "X742CorrectionRoutines.h"
#include "fft.h"

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



    //////////////////
    //ui->widget_011->graph(0)->setName("Test");
    //ui->widget_011->


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

    emit this->SetRecordLength(arg1);

    ui->widget_011->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_012->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_013->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_014->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_015->xAxis->setRange(0, arg1*sampling_rate/1000);

    ui->widget_021->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_022->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_023->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_024->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_025->xAxis->setRange(0, arg1*sampling_rate/1000);

    ui->widget_031->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_032->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_033->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_034->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_035->xAxis->setRange(0, arg1*sampling_rate/1000);

    ui->widget_041->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_042->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_043->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_044->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_045->xAxis->setRange(0, arg1*sampling_rate/1000);

    ui->widget_051->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_052->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_053->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_054->xAxis->setRange(0, arg1*sampling_rate/1000);
    ui->widget_055->xAxis->setRange(0, arg1*sampling_rate/1000);


    ui->widget_011->replot();
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
        ui->groupBox_6->setEnabled(false);
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
