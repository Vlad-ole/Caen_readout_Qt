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
#include "myworker.h"

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
    connect( this, SIGNAL( SetDCOffset(int,int) ), worker, SLOT( SetDCOffset(int,int) ) );
    connect( this, SIGNAL( SetRisingFalling(bool) ), worker, SLOT( SetRisingFalling(bool) ) );
    connect( this, SIGNAL( SetContinuousTrigger(bool)) , worker, SLOT( SetContinuousTrigger(bool) ) );
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

    trigger_value_ch.ch = 0;
    trigger_value_ch.value = 0;

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

    //----------------------------

    ui->widget_055->axisRect()->setupFullAxesBox();
    ui->widget_055->plotLayout()->insertRow(0);
    ui->widget_055->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_055, "Channel 24"));
    ui->widget_055->xAxis->setLabel(x_label);
    ui->widget_055->yAxis->setLabel(y_label);

    ui->widget_ch_25->axisRect()->setupFullAxesBox();
    ui->widget_ch_25->plotLayout()->insertRow(0);
    ui->widget_ch_25->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_25, "Channel 25"));
    ui->widget_ch_25->xAxis->setLabel(x_label);
    ui->widget_ch_25->yAxis->setLabel(y_label);

    ui->widget_ch_26->axisRect()->setupFullAxesBox();
    ui->widget_ch_26->plotLayout()->insertRow(0);
    ui->widget_ch_26->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_26, "Channel 26"));
    ui->widget_ch_26->xAxis->setLabel(x_label);
    ui->widget_ch_26->yAxis->setLabel(y_label);

    ui->widget_ch_27->axisRect()->setupFullAxesBox();
    ui->widget_ch_27->plotLayout()->insertRow(0);
    ui->widget_ch_27->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_27, "Channel 27"));
    ui->widget_ch_27->xAxis->setLabel(x_label);
    ui->widget_ch_27->yAxis->setLabel(y_label);

    ui->widget_ch_28->axisRect()->setupFullAxesBox();
    ui->widget_ch_28->plotLayout()->insertRow(0);
    ui->widget_ch_28->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_28, "Channel 28"));
    ui->widget_ch_28->xAxis->setLabel(x_label);
    ui->widget_ch_28->yAxis->setLabel(y_label);

    ui->widget_ch_29->axisRect()->setupFullAxesBox();
    ui->widget_ch_29->plotLayout()->insertRow(0);
    ui->widget_ch_29->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_29, "Channel 29"));
    ui->widget_ch_29->xAxis->setLabel(x_label);
    ui->widget_ch_29->yAxis->setLabel(y_label);

    ui->widget_ch_30->axisRect()->setupFullAxesBox();
    ui->widget_ch_30->plotLayout()->insertRow(0);
    ui->widget_ch_30->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_30, "Channel 30"));
    ui->widget_ch_30->xAxis->setLabel(x_label);
    ui->widget_ch_30->yAxis->setLabel(y_label);

    ui->widget_ch_31->axisRect()->setupFullAxesBox();
    ui->widget_ch_31->plotLayout()->insertRow(0);
    ui->widget_ch_31->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_31, "Channel 31"));
    ui->widget_ch_31->xAxis->setLabel(x_label);
    ui->widget_ch_31->yAxis->setLabel(y_label);

    // ----------------------

    ui->widget_ch_32->axisRect()->setupFullAxesBox();
    ui->widget_ch_32->plotLayout()->insertRow(0);
    ui->widget_ch_32->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_32, "Channel 32"));
    ui->widget_ch_32->xAxis->setLabel(x_label);
    ui->widget_ch_32->yAxis->setLabel(y_label);

    ui->widget_ch_33->axisRect()->setupFullAxesBox();
    ui->widget_ch_33->plotLayout()->insertRow(0);
    ui->widget_ch_33->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_33, "Channel 33"));
    ui->widget_ch_33->xAxis->setLabel(x_label);
    ui->widget_ch_33->yAxis->setLabel(y_label);

    ui->widget_ch_34->axisRect()->setupFullAxesBox();
    ui->widget_ch_34->plotLayout()->insertRow(0);
    ui->widget_ch_34->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_34, "Channel 34"));
    ui->widget_ch_34->xAxis->setLabel(x_label);
    ui->widget_ch_34->yAxis->setLabel(y_label);

    ui->widget_ch_35->axisRect()->setupFullAxesBox();
    ui->widget_ch_35->plotLayout()->insertRow(0);
    ui->widget_ch_35->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_35, "Channel 35"));
    ui->widget_ch_35->xAxis->setLabel(x_label);
    ui->widget_ch_35->yAxis->setLabel(y_label);

    ui->widget_ch_36->axisRect()->setupFullAxesBox();
    ui->widget_ch_36->plotLayout()->insertRow(0);
    ui->widget_ch_36->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_36, "Channel 36"));
    ui->widget_ch_36->xAxis->setLabel(x_label);
    ui->widget_ch_36->yAxis->setLabel(y_label);


    ui->widget_ch_37->axisRect()->setupFullAxesBox();
    ui->widget_ch_37->plotLayout()->insertRow(0);
    ui->widget_ch_37->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_37, "Channel 37"));
    ui->widget_ch_37->xAxis->setLabel(x_label);
    ui->widget_ch_37->yAxis->setLabel(y_label);


    ui->widget_ch_38->axisRect()->setupFullAxesBox();
    ui->widget_ch_38->plotLayout()->insertRow(0);
    ui->widget_ch_38->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_38, "Channel 38"));
    ui->widget_ch_38->xAxis->setLabel(x_label);
    ui->widget_ch_38->yAxis->setLabel(y_label);

    ui->widget_ch_39->axisRect()->setupFullAxesBox();
    ui->widget_ch_39->plotLayout()->insertRow(0);
    ui->widget_ch_39->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_39, "Channel 39"));
    ui->widget_ch_39->xAxis->setLabel(x_label);
    ui->widget_ch_39->yAxis->setLabel(y_label);

    // --------------------------------

    ui->widget_ch_40->axisRect()->setupFullAxesBox();
    ui->widget_ch_40->plotLayout()->insertRow(0);
    ui->widget_ch_40->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_40, "Channel 40"));
    ui->widget_ch_40->xAxis->setLabel(x_label);
    ui->widget_ch_40->yAxis->setLabel(y_label);

    ui->widget_ch_41->axisRect()->setupFullAxesBox();
    ui->widget_ch_41->plotLayout()->insertRow(0);
    ui->widget_ch_41->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_41, "Channel 41"));
    ui->widget_ch_41->xAxis->setLabel(x_label);
    ui->widget_ch_41->yAxis->setLabel(y_label);

    ui->widget_ch_42->axisRect()->setupFullAxesBox();
    ui->widget_ch_42->plotLayout()->insertRow(0);
    ui->widget_ch_42->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_42, "Channel 42"));
    ui->widget_ch_42->xAxis->setLabel(x_label);
    ui->widget_ch_42->yAxis->setLabel(y_label);

    ui->widget_ch_43->axisRect()->setupFullAxesBox();
    ui->widget_ch_43->plotLayout()->insertRow(0);
    ui->widget_ch_43->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_43, "Channel 43"));
    ui->widget_ch_43->xAxis->setLabel(x_label);
    ui->widget_ch_43->yAxis->setLabel(y_label);

    ui->widget_ch_44->axisRect()->setupFullAxesBox();
    ui->widget_ch_44->plotLayout()->insertRow(0);
    ui->widget_ch_44->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_44, "Channel 44"));
    ui->widget_ch_44->xAxis->setLabel(x_label);
    ui->widget_ch_44->yAxis->setLabel(y_label);

    ui->widget_ch_45->axisRect()->setupFullAxesBox();
    ui->widget_ch_45->plotLayout()->insertRow(0);
    ui->widget_ch_45->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_45, "Channel 45"));
    ui->widget_ch_45->xAxis->setLabel(x_label);
    ui->widget_ch_45->yAxis->setLabel(y_label);

    ui->widget_ch_46->axisRect()->setupFullAxesBox();
    ui->widget_ch_46->plotLayout()->insertRow(0);
    ui->widget_ch_46->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_46, "Channel 46"));
    ui->widget_ch_46->xAxis->setLabel(x_label);
    ui->widget_ch_46->yAxis->setLabel(y_label);

    ui->widget_ch_47->axisRect()->setupFullAxesBox();
    ui->widget_ch_47->plotLayout()->insertRow(0);
    ui->widget_ch_47->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_47, "Channel 47"));
    ui->widget_ch_47->xAxis->setLabel(x_label);
    ui->widget_ch_47->yAxis->setLabel(y_label);

    ui->widget_ch_48->axisRect()->setupFullAxesBox();
    ui->widget_ch_48->plotLayout()->insertRow(0);
    ui->widget_ch_48->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_48, "Channel 48"));
    ui->widget_ch_48->xAxis->setLabel(x_label);
    ui->widget_ch_48->yAxis->setLabel(y_label);

    ui->widget_ch_49->axisRect()->setupFullAxesBox();
    ui->widget_ch_49->plotLayout()->insertRow(0);
    ui->widget_ch_49->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_49, "Channel 49"));
    ui->widget_ch_49->xAxis->setLabel(x_label);
    ui->widget_ch_49->yAxis->setLabel(y_label);

    ui->widget_ch_50->axisRect()->setupFullAxesBox();
    ui->widget_ch_50->plotLayout()->insertRow(0);
    ui->widget_ch_50->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_50, "Channel 50"));
    ui->widget_ch_50->xAxis->setLabel(x_label);
    ui->widget_ch_50->yAxis->setLabel(y_label);

    ui->widget_ch_51->axisRect()->setupFullAxesBox();
    ui->widget_ch_51->plotLayout()->insertRow(0);
    ui->widget_ch_51->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_51, "Channel 51"));
    ui->widget_ch_51->xAxis->setLabel(x_label);
    ui->widget_ch_51->yAxis->setLabel(y_label);

    ui->widget_ch_52->axisRect()->setupFullAxesBox();
    ui->widget_ch_52->plotLayout()->insertRow(0);
    ui->widget_ch_52->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_52, "Channel 52"));
    ui->widget_ch_52->xAxis->setLabel(x_label);
    ui->widget_ch_52->yAxis->setLabel(y_label);

    ui->widget_ch_53->axisRect()->setupFullAxesBox();
    ui->widget_ch_53->plotLayout()->insertRow(0);
    ui->widget_ch_53->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_53, "Channel 53"));
    ui->widget_ch_53->xAxis->setLabel(x_label);
    ui->widget_ch_53->yAxis->setLabel(y_label);

    ui->widget_ch_54->axisRect()->setupFullAxesBox();
    ui->widget_ch_54->plotLayout()->insertRow(0);
    ui->widget_ch_54->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_54, "Channel 54"));
    ui->widget_ch_54->xAxis->setLabel(x_label);
    ui->widget_ch_54->yAxis->setLabel(y_label);

    ui->widget_ch_55->axisRect()->setupFullAxesBox();
    ui->widget_ch_55->plotLayout()->insertRow(0);
    ui->widget_ch_55->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_55, "Channel 55"));
    ui->widget_ch_55->xAxis->setLabel(x_label);
    ui->widget_ch_55->yAxis->setLabel(y_label);

    ui->widget_ch_56->axisRect()->setupFullAxesBox();
    ui->widget_ch_56->plotLayout()->insertRow(0);
    ui->widget_ch_56->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_56, "Channel 56"));
    ui->widget_ch_56->xAxis->setLabel(x_label);
    ui->widget_ch_56->yAxis->setLabel(y_label);

    ui->widget_ch_57->axisRect()->setupFullAxesBox();
    ui->widget_ch_57->plotLayout()->insertRow(0);
    ui->widget_ch_57->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_57, "Channel 57"));
    ui->widget_ch_57->xAxis->setLabel(x_label);
    ui->widget_ch_57->yAxis->setLabel(y_label);

    ui->widget_ch_58->axisRect()->setupFullAxesBox();
    ui->widget_ch_58->plotLayout()->insertRow(0);
    ui->widget_ch_58->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_58, "Channel 58"));
    ui->widget_ch_58->xAxis->setLabel(x_label);
    ui->widget_ch_58->yAxis->setLabel(y_label);

    ui->widget_ch_59->axisRect()->setupFullAxesBox();
    ui->widget_ch_59->plotLayout()->insertRow(0);
    ui->widget_ch_59->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_59, "Channel 59"));
    ui->widget_ch_59->xAxis->setLabel(x_label);
    ui->widget_ch_59->yAxis->setLabel(y_label);

    ui->widget_ch_60->axisRect()->setupFullAxesBox();
    ui->widget_ch_60->plotLayout()->insertRow(0);
    ui->widget_ch_60->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_60, "Channel 60"));
    ui->widget_ch_60->xAxis->setLabel(x_label);
    ui->widget_ch_60->yAxis->setLabel(y_label);

    ui->widget_ch_61->axisRect()->setupFullAxesBox();
    ui->widget_ch_61->plotLayout()->insertRow(0);
    ui->widget_ch_61->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_61, "Channel 61"));
    ui->widget_ch_61->xAxis->setLabel(x_label);
    ui->widget_ch_61->yAxis->setLabel(y_label);

    ui->widget_ch_62->axisRect()->setupFullAxesBox();
    ui->widget_ch_62->plotLayout()->insertRow(0);
    ui->widget_ch_62->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_62, "Channel 62"));
    ui->widget_ch_62->xAxis->setLabel(x_label);
    ui->widget_ch_62->yAxis->setLabel(y_label);

    ui->widget_ch_63->axisRect()->setupFullAxesBox();
    ui->widget_ch_63->plotLayout()->insertRow(0);
    ui->widget_ch_63->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_ch_63, "Channel 63"));
    ui->widget_ch_63->xAxis->setLabel(x_label);
    ui->widget_ch_63->yAxis->setLabel(y_label);

    SetRangeX();


    // set mask gui according to device model

    switch (worker->BoardInfo.FamilyCode)
    {
    case CAEN_DGTZ_XX720_FAMILY_CODE:
    {

        ui->MASK_CHANNEL_checkBox_gr1_ch0->setEnabled(false);
        ui->MASK_CHANNEL_checkBox_gr2_ch0->setEnabled(false);
        ui->MASK_CHANNEL_checkBox_gr3_ch0->setEnabled(false);
        ui->MASK_CHANNEL_checkBox_gr4_ch0->setEnabled(false);
        ui->MASK_CHANNEL_checkBox_gr5_ch0->setEnabled(false);
        ui->MASK_CHANNEL_checkBox_gr6_ch0->setEnabled(false);
        ui->MASK_CHANNEL_checkBox_gr7_ch0->setEnabled(false);

        ui->CHANNEL_TRIGGER_checkBox_gr1_ch8->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr1_ch9->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr1_ch10->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr1_ch11->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr1_ch12->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr1_ch13->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr1_ch14->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr1_ch15->setEnabled(false);

        ui->CHANNEL_TRIGGER_checkBox_gr2_ch16->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr2_ch17->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr2_ch18->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr2_ch19->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr2_ch20->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr2_ch21->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr2_ch22->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr2_ch23->setEnabled(false);

        ui->CHANNEL_TRIGGER_checkBox_gr3_ch24->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr3_ch25->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr3_ch26->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr3_ch27->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr3_ch28->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr3_ch29->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr3_ch30->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr3_ch31->setEnabled(false);

        ui->CHANNEL_TRIGGER_checkBox_gr4_ch32->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr4_ch33->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr4_ch34->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr4_ch35->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr4_ch36->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr4_ch37->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr4_ch38->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr4_ch39->setEnabled(false);

        ui->CHANNEL_TRIGGER_checkBox_gr5_ch40->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr5_ch41->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr5_ch42->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr5_ch43->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr5_ch44->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr5_ch45->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr5_ch46->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr5_ch47->setEnabled(false);

        ui->CHANNEL_TRIGGER_checkBox_gr6_ch48->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr6_ch49->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr6_ch50->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr6_ch51->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr6_ch52->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr6_ch53->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr6_ch54->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr6_ch55->setEnabled(false);

        ui->CHANNEL_TRIGGER_checkBox_gr7_ch56->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr7_ch57->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr7_ch58->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr7_ch59->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr7_ch60->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr7_ch61->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr7_ch62->setEnabled(false);
        ui->CHANNEL_TRIGGER_checkBox_gr7_ch63->setEnabled(false);



        break;
    }
    case CAEN_DGTZ_XX740_FAMILY_CODE:
    {
        ui->MASK_CHANNEL_checkBox_gr0_ch1->setEnabled(false);
        ui->MASK_CHANNEL_checkBox_gr0_ch2->setEnabled(false);
        ui->MASK_CHANNEL_checkBox_gr0_ch3->setEnabled(false);
        ui->MASK_CHANNEL_checkBox_gr0_ch4->setEnabled(false);
        ui->MASK_CHANNEL_checkBox_gr0_ch5->setEnabled(false);
        ui->MASK_CHANNEL_checkBox_gr0_ch6->setEnabled(false);
        ui->MASK_CHANNEL_checkBox_gr0_ch7->setEnabled(false);
        break;
    }
    default:
        qDebug() << "Add device in list" << endl;

    }




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
    ui->widget_ch_25->clearGraphs();
    ui->widget_ch_26->clearGraphs();
    ui->widget_ch_27->clearGraphs();
    ui->widget_ch_28->clearGraphs();
    ui->widget_ch_29->clearGraphs();
    ui->widget_ch_30->clearGraphs();
    ui->widget_ch_31->clearGraphs();

    ui->widget_ch_32->clearGraphs();
    ui->widget_ch_33->clearGraphs();
    ui->widget_ch_34->clearGraphs();
    ui->widget_ch_35->clearGraphs();
    ui->widget_ch_36->clearGraphs();
    ui->widget_ch_37->clearGraphs();
    ui->widget_ch_38->clearGraphs();
    ui->widget_ch_39->clearGraphs();

    ui->widget_ch_40->clearGraphs();
    ui->widget_ch_41->clearGraphs();
    ui->widget_ch_42->clearGraphs();
    ui->widget_ch_43->clearGraphs();
    ui->widget_ch_44->clearGraphs();
    ui->widget_ch_45->clearGraphs();
    ui->widget_ch_46->clearGraphs();
    ui->widget_ch_47->clearGraphs();

    ui->widget_ch_48->clearGraphs();
    ui->widget_ch_49->clearGraphs();
    ui->widget_ch_50->clearGraphs();
    ui->widget_ch_51->clearGraphs();
    ui->widget_ch_52->clearGraphs();
    ui->widget_ch_53->clearGraphs();
    ui->widget_ch_54->clearGraphs();
    ui->widget_ch_55->clearGraphs();

    ui->widget_ch_56->clearGraphs();
    ui->widget_ch_57->clearGraphs();
    ui->widget_ch_58->clearGraphs();
    ui->widget_ch_59->clearGraphs();
    ui->widget_ch_60->clearGraphs();
    ui->widget_ch_61->clearGraphs();
    ui->widget_ch_62->clearGraphs();
    ui->widget_ch_63->clearGraphs();


    // ///////////////////
    switch (worker->BoardInfo.FamilyCode)
    {
    case CAEN_DGTZ_XX720_FAMILY_CODE:
    {
        qDebug() << "CAEN_DGTZ_XX720_FAMILY_CODE" << endl;

        if(worker->WDcfg.EnableMask & 1)
        {
            ui->widget_011->addGraph();
            ui->widget_011->graph(0)->setData(array_x, array_y[0]);
        }

        if(worker->WDcfg.EnableMask & 2)
        {
            ui->widget_012->addGraph();
            ui->widget_012->graph(0)->setData(array_x, array_y[1]);
        }

        if(worker->WDcfg.EnableMask & 4)
        {
            ui->widget_013->addGraph();
            ui->widget_013->graph(0)->setData(array_x, array_y[2]);
        }

        if(worker->WDcfg.EnableMask & 8)
        {
            ui->widget_014->addGraph();
            ui->widget_014->graph(0)->setData(array_x, array_y[3]);
        }

        if(worker->WDcfg.EnableMask & 16)
        {
            ui->widget_015->addGraph();
            ui->widget_015->graph(0)->setData(array_x, array_y[4]);
        }

        if(worker->WDcfg.EnableMask & 32)
        {
            ui->widget_021->addGraph();
            ui->widget_021->graph(0)->setData(array_x, array_y[5]);
        }

        if(worker->WDcfg.EnableMask & 64)
        {
            ui->widget_022->addGraph();
            ui->widget_022->graph(0)->setData(array_x, array_y[6]);
        }

        if(worker->WDcfg.EnableMask & 128)
        {
            ui->widget_023->addGraph();
            ui->widget_023->graph(0)->setData(array_x, array_y[7]);
        }

        break;
    }

    case CAEN_DGTZ_XX740_FAMILY_CODE:
    {
         qDebug() << "CAEN_DGTZ_XX740_FAMILY_CODE" << endl;
        if(worker->WDcfg.EnableMask & 1)
        {
            ui->widget_011->addGraph();
            ui->widget_012->addGraph();
            ui->widget_013->addGraph();
            ui->widget_014->addGraph();
            ui->widget_015->addGraph();
            ui->widget_021->addGraph();
            ui->widget_022->addGraph();
            ui->widget_023->addGraph();

            ui->widget_011->graph(0)->setData(array_x, array_y[0]);
            ui->widget_012->graph(0)->setData(array_x, array_y[1]);
            ui->widget_013->graph(0)->setData(array_x, array_y[2]);
            ui->widget_014->graph(0)->setData(array_x, array_y[3]);
            ui->widget_015->graph(0)->setData(array_x, array_y[4]);
            ui->widget_021->graph(0)->setData(array_x, array_y[5]);
            ui->widget_022->graph(0)->setData(array_x, array_y[6]);
            ui->widget_023->graph(0)->setData(array_x, array_y[7]);

            qDebug() << "worker->WDcfg.EnableMask & 1" << endl;

        }

        if(worker->WDcfg.EnableMask & 2)
        {
            ui->widget_024->addGraph();
            ui->widget_025->addGraph();
            ui->widget_031->addGraph();
            ui->widget_032->addGraph();
            ui->widget_033->addGraph();
            ui->widget_034->addGraph();
            ui->widget_035->addGraph();
            ui->widget_041->addGraph();

            ui->widget_024->graph(0)->setData(array_x, array_y[8]);
            ui->widget_025->graph(0)->setData(array_x, array_y[9]);
            ui->widget_031->graph(0)->setData(array_x, array_y[10]);
            ui->widget_032->graph(0)->setData(array_x, array_y[11]);
            ui->widget_033->graph(0)->setData(array_x, array_y[12]);
            ui->widget_034->graph(0)->setData(array_x, array_y[13]);
            ui->widget_035->graph(0)->setData(array_x, array_y[14]);
            ui->widget_041->graph(0)->setData(array_x, array_y[15]);

            qDebug() << "worker->WDcfg.EnableMask & 2" << endl;
        }

        if(worker->WDcfg.EnableMask & 4)
        {
            ui->widget_042->addGraph();
            ui->widget_043->addGraph();
            ui->widget_044->addGraph();
            ui->widget_045->addGraph();
            ui->widget_051->addGraph();
            ui->widget_052->addGraph();
            ui->widget_053->addGraph();
            ui->widget_054->addGraph();

            ui->widget_042->graph(0)->setData(array_x, array_y[16]);
            ui->widget_043->graph(0)->setData(array_x, array_y[17]);
            ui->widget_044->graph(0)->setData(array_x, array_y[18]);
            ui->widget_045->graph(0)->setData(array_x, array_y[19]);
            ui->widget_051->graph(0)->setData(array_x, array_y[20]);
            ui->widget_052->graph(0)->setData(array_x, array_y[21]);
            ui->widget_053->graph(0)->setData(array_x, array_y[22]);
            ui->widget_054->graph(0)->setData(array_x, array_y[23]);

            qDebug() << "worker->WDcfg.EnableMask & 4" << endl;

        }

        if(worker->WDcfg.EnableMask & 8)
        {
             ui->widget_055->addGraph();
             ui->widget_ch_25->addGraph();
             ui->widget_ch_26->addGraph();
             ui->widget_ch_27->addGraph();
             ui->widget_ch_28->addGraph();
             ui->widget_ch_29->addGraph();
             ui->widget_ch_30->addGraph();
             ui->widget_ch_31->addGraph();

             ui->widget_055->graph(0)->setData(array_x, array_y[24]);
             ui->widget_ch_25->graph(0)->setData(array_x, array_y[25]);
             ui->widget_ch_26->graph(0)->setData(array_x, array_y[26]);
             ui->widget_ch_27->graph(0)->setData(array_x, array_y[27]);
             ui->widget_ch_28->graph(0)->setData(array_x, array_y[28]);
             ui->widget_ch_29->graph(0)->setData(array_x, array_y[29]);
             ui->widget_ch_30->graph(0)->setData(array_x, array_y[30]);
             ui->widget_ch_31->graph(0)->setData(array_x, array_y[31]);

            qDebug() << "worker->WDcfg.EnableMask & 8" << endl;
        }

        if(worker->WDcfg.EnableMask & 16)
        {
            ui->widget_ch_32->addGraph();
            ui->widget_ch_33->addGraph();
            ui->widget_ch_34->addGraph();
            ui->widget_ch_35->addGraph();
            ui->widget_ch_36->addGraph();
            ui->widget_ch_37->addGraph();
            ui->widget_ch_38->addGraph();
            ui->widget_ch_39->addGraph();

            ui->widget_ch_32->graph(0)->setData(array_x, array_y[32]);
            ui->widget_ch_33->graph(0)->setData(array_x, array_y[33]);
            ui->widget_ch_34->graph(0)->setData(array_x, array_y[34]);
            ui->widget_ch_35->graph(0)->setData(array_x, array_y[35]);
            ui->widget_ch_36->graph(0)->setData(array_x, array_y[36]);
            ui->widget_ch_37->graph(0)->setData(array_x, array_y[37]);
            ui->widget_ch_38->graph(0)->setData(array_x, array_y[38]);
            ui->widget_ch_39->graph(0)->setData(array_x, array_y[39]);

            qDebug() << "worker->WDcfg.EnableMask & 16" << endl;
        }

        if(worker->WDcfg.EnableMask & 32)
        {
            ui->widget_ch_40->addGraph();
            ui->widget_ch_41->addGraph();
            ui->widget_ch_42->addGraph();
            ui->widget_ch_43->addGraph();
            ui->widget_ch_44->addGraph();
            ui->widget_ch_45->addGraph();
            ui->widget_ch_46->addGraph();
            ui->widget_ch_47->addGraph();

            ui->widget_ch_40->graph(0)->setData(array_x, array_y[40]);
            ui->widget_ch_41->graph(0)->setData(array_x, array_y[41]);
            ui->widget_ch_42->graph(0)->setData(array_x, array_y[42]);
            ui->widget_ch_43->graph(0)->setData(array_x, array_y[43]);
            ui->widget_ch_44->graph(0)->setData(array_x, array_y[44]);
            ui->widget_ch_45->graph(0)->setData(array_x, array_y[45]);
            ui->widget_ch_46->graph(0)->setData(array_x, array_y[46]);
            ui->widget_ch_47->graph(0)->setData(array_x, array_y[47]);

            qDebug() << "worker->WDcfg.EnableMask & 32" << endl;
        }

        if(worker->WDcfg.EnableMask & 64)
        {
            ui->widget_ch_48->addGraph();
            ui->widget_ch_49->addGraph();
            ui->widget_ch_50->addGraph();
            ui->widget_ch_51->addGraph();
            ui->widget_ch_52->addGraph();
            ui->widget_ch_53->addGraph();
            ui->widget_ch_54->addGraph();
            ui->widget_ch_55->addGraph();

            ui->widget_ch_48->graph(0)->setData(array_x, array_y[48]);
            ui->widget_ch_49->graph(0)->setData(array_x, array_y[49]);
            ui->widget_ch_50->graph(0)->setData(array_x, array_y[50]);
            ui->widget_ch_51->graph(0)->setData(array_x, array_y[51]);
            ui->widget_ch_52->graph(0)->setData(array_x, array_y[52]);
            ui->widget_ch_53->graph(0)->setData(array_x, array_y[53]);
            ui->widget_ch_54->graph(0)->setData(array_x, array_y[54]);
            ui->widget_ch_55->graph(0)->setData(array_x, array_y[55]);

            qDebug() << "worker->WDcfg.EnableMask & 64" << endl;
        }

        if(worker->WDcfg.EnableMask & 128)
        {
            ui->widget_ch_56->addGraph();
            ui->widget_ch_57->addGraph();
            ui->widget_ch_58->addGraph();
            ui->widget_ch_59->addGraph();
            ui->widget_ch_60->addGraph();
            ui->widget_ch_61->addGraph();
            ui->widget_ch_62->addGraph();
            ui->widget_ch_63->addGraph();

            ui->widget_ch_56->graph(0)->setData(array_x, array_y[56]);
            ui->widget_ch_57->graph(0)->setData(array_x, array_y[57]);
            ui->widget_ch_58->graph(0)->setData(array_x, array_y[58]);
            ui->widget_ch_59->graph(0)->setData(array_x, array_y[59]);
            ui->widget_ch_60->graph(0)->setData(array_x, array_y[60]);
            ui->widget_ch_61->graph(0)->setData(array_x, array_y[61]);
            ui->widget_ch_62->graph(0)->setData(array_x, array_y[62]);
            ui->widget_ch_63->graph(0)->setData(array_x, array_y[63]);

            qDebug() << "worker->WDcfg.EnableMask & 128" << endl;
        }

        break;
    }
    default:
        qDebug() << "add device in list" << endl;

    }




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
    ui->widget_ch_25->replot();
    ui->widget_ch_26->replot();
    ui->widget_ch_27->replot();
    ui->widget_ch_28->replot();
    ui->widget_ch_29->replot();
    ui->widget_ch_30->replot();
    ui->widget_ch_31->replot();

    ui->widget_ch_32->replot();
    ui->widget_ch_33->replot();
    ui->widget_ch_34->replot();
    ui->widget_ch_35->replot();
    ui->widget_ch_36->replot();
    ui->widget_ch_37->replot();
    ui->widget_ch_38->replot();
    ui->widget_ch_39->replot();

    ui->widget_ch_40->replot();
    ui->widget_ch_41->replot();
    ui->widget_ch_42->replot();
    ui->widget_ch_43->replot();
    ui->widget_ch_44->replot();
    ui->widget_ch_45->replot();
    ui->widget_ch_46->replot();
    ui->widget_ch_47->replot();

    ui->widget_ch_48->replot();
    ui->widget_ch_49->replot();
    ui->widget_ch_50->replot();
    ui->widget_ch_51->replot();
    ui->widget_ch_52->replot();
    ui->widget_ch_53->replot();
    ui->widget_ch_54->replot();
    ui->widget_ch_55->replot();

    ui->widget_ch_56->replot();
    ui->widget_ch_57->replot();
    ui->widget_ch_58->replot();
    ui->widget_ch_59->replot();
    ui->widget_ch_60->replot();
    ui->widget_ch_61->replot();
    ui->widget_ch_62->replot();
    ui->widget_ch_63->replot();



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
    ui->widget_ch_25->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_26->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_27->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_28->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_29->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_30->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_31->xAxis->setRange(x_min_misros, x_max_misros);

    ui->widget_ch_32->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_33->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_34->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_35->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_36->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_37->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_38->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_39->xAxis->setRange(x_min_misros, x_max_misros);

    ui->widget_ch_40->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_41->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_42->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_43->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_44->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_45->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_46->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_47->xAxis->setRange(x_min_misros, x_max_misros);

    ui->widget_ch_48->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_49->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_50->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_51->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_52->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_53->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_54->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_55->xAxis->setRange(x_min_misros, x_max_misros);

    ui->widget_ch_56->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_57->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_58->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_59->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_60->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_61->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_62->xAxis->setRange(x_min_misros, x_max_misros);
    ui->widget_ch_63->xAxis->setRange(x_min_misros, x_max_misros);


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
    ui->widget_ch_25->yAxis->setRangeLower(y_min);
    ui->widget_ch_26->yAxis->setRangeLower(y_min);
    ui->widget_ch_27->yAxis->setRangeLower(y_min);
    ui->widget_ch_28->yAxis->setRangeLower(y_min);
    ui->widget_ch_29->yAxis->setRangeLower(y_min);
    ui->widget_ch_30->yAxis->setRangeLower(y_min);
    ui->widget_ch_31->yAxis->setRangeLower(y_min);

    ui->widget_ch_32->yAxis->setRangeLower(y_min);
    ui->widget_ch_33->yAxis->setRangeLower(y_min);
    ui->widget_ch_34->yAxis->setRangeLower(y_min);
    ui->widget_ch_35->yAxis->setRangeLower(y_min);
    ui->widget_ch_36->yAxis->setRangeLower(y_min);
    ui->widget_ch_37->yAxis->setRangeLower(y_min);
    ui->widget_ch_38->yAxis->setRangeLower(y_min);
    ui->widget_ch_39->yAxis->setRangeLower(y_min);

    ui->widget_ch_40->yAxis->setRangeLower(y_min);
    ui->widget_ch_41->yAxis->setRangeLower(y_min);
    ui->widget_ch_42->yAxis->setRangeLower(y_min);
    ui->widget_ch_43->yAxis->setRangeLower(y_min);
    ui->widget_ch_44->yAxis->setRangeLower(y_min);
    ui->widget_ch_45->yAxis->setRangeLower(y_min);
    ui->widget_ch_46->yAxis->setRangeLower(y_min);
    ui->widget_ch_47->yAxis->setRangeLower(y_min);

    ui->widget_ch_48->yAxis->setRangeLower(y_min);
    ui->widget_ch_49->yAxis->setRangeLower(y_min);
    ui->widget_ch_50->yAxis->setRangeLower(y_min);
    ui->widget_ch_51->yAxis->setRangeLower(y_min);
    ui->widget_ch_52->yAxis->setRangeLower(y_min);
    ui->widget_ch_53->yAxis->setRangeLower(y_min);
    ui->widget_ch_54->yAxis->setRangeLower(y_min);
    ui->widget_ch_55->yAxis->setRangeLower(y_min);

    ui->widget_ch_56->yAxis->setRangeLower(y_min);
    ui->widget_ch_57->yAxis->setRangeLower(y_min);
    ui->widget_ch_58->yAxis->setRangeLower(y_min);
    ui->widget_ch_59->yAxis->setRangeLower(y_min);
    ui->widget_ch_60->yAxis->setRangeLower(y_min);
    ui->widget_ch_61->yAxis->setRangeLower(y_min);
    ui->widget_ch_62->yAxis->setRangeLower(y_min);
    ui->widget_ch_63->yAxis->setRangeLower(y_min);

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
    ui->widget_ch_25->yAxis->setRangeUpper(y_max);
    ui->widget_ch_26->yAxis->setRangeUpper(y_max);
    ui->widget_ch_27->yAxis->setRangeUpper(y_max);
    ui->widget_ch_28->yAxis->setRangeUpper(y_max);
    ui->widget_ch_29->yAxis->setRangeUpper(y_max);
    ui->widget_ch_30->yAxis->setRangeUpper(y_max);
    ui->widget_ch_31->yAxis->setRangeUpper(y_max);

    ui->widget_ch_32->yAxis->setRangeUpper(y_max);
    ui->widget_ch_33->yAxis->setRangeUpper(y_max);
    ui->widget_ch_34->yAxis->setRangeUpper(y_max);
    ui->widget_ch_35->yAxis->setRangeUpper(y_max);
    ui->widget_ch_36->yAxis->setRangeUpper(y_max);
    ui->widget_ch_37->yAxis->setRangeUpper(y_max);
    ui->widget_ch_38->yAxis->setRangeUpper(y_max);
    ui->widget_ch_39->yAxis->setRangeUpper(y_max);

    ui->widget_ch_40->yAxis->setRangeUpper(y_max);
    ui->widget_ch_41->yAxis->setRangeUpper(y_max);
    ui->widget_ch_42->yAxis->setRangeUpper(y_max);
    ui->widget_ch_43->yAxis->setRangeUpper(y_max);
    ui->widget_ch_44->yAxis->setRangeUpper(y_max);
    ui->widget_ch_45->yAxis->setRangeUpper(y_max);
    ui->widget_ch_46->yAxis->setRangeUpper(y_max);
    ui->widget_ch_47->yAxis->setRangeUpper(y_max);

    ui->widget_ch_48->yAxis->setRangeUpper(y_max);
    ui->widget_ch_49->yAxis->setRangeUpper(y_max);
    ui->widget_ch_50->yAxis->setRangeUpper(y_max);
    ui->widget_ch_51->yAxis->setRangeUpper(y_max);
    ui->widget_ch_52->yAxis->setRangeUpper(y_max);
    ui->widget_ch_53->yAxis->setRangeUpper(y_max);
    ui->widget_ch_54->yAxis->setRangeUpper(y_max);
    ui->widget_ch_55->yAxis->setRangeUpper(y_max);

    ui->widget_ch_56->yAxis->setRangeUpper(y_max);
    ui->widget_ch_57->yAxis->setRangeUpper(y_max);
    ui->widget_ch_58->yAxis->setRangeUpper(y_max);
    ui->widget_ch_59->yAxis->setRangeUpper(y_max);
    ui->widget_ch_60->yAxis->setRangeUpper(y_max);
    ui->widget_ch_61->yAxis->setRangeUpper(y_max);
    ui->widget_ch_62->yAxis->setRangeUpper(y_max);
    ui->widget_ch_63->yAxis->setRangeUpper(y_max);


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
    emit this->SetContinuousTrigger(true);
}

void MainWindow::PlotMask(uint value)
{
    plot_mask = value;
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

//void MainWindow::on_spinBox_4_editingFinished()
//{

//}

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
    ui->MASK_CHANNEL_checkBox_gr0_ch0->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr0_ch1->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr0_ch2->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr0_ch3->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr0_ch4->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr0_ch5->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr0_ch6->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr0_ch7->setChecked(false);

    ui->MASK_CHANNEL_checkBox_gr1_ch0->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr2_ch0->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr3_ch0->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr4_ch0->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr5_ch0->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr6_ch0->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr7_ch0->setChecked(false);

    emit this->MaskChannelAll(false);

}

void MainWindow::on_pushButton_4_clicked()
{

    ui->MASK_CHANNEL_checkBox_gr0_ch0->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr0_ch1->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr0_ch2->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr0_ch3->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr0_ch4->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr0_ch5->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr0_ch6->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr0_ch7->setChecked(false);

    ui->MASK_CHANNEL_checkBox_gr1_ch0->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr2_ch0->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr3_ch0->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr4_ch0->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr5_ch0->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr6_ch0->setChecked(false);
    ui->MASK_CHANNEL_checkBox_gr7_ch0->setChecked(false);


    emit this->MaskChannelAll(true);


}



void MainWindow::on_MASK_CHANNEL_checkBox_gr0_ch0_clicked(bool checked)
{
    emit this->MaskChannel(0, checked);
}

void MainWindow::on_MASK_CHANNEL_checkBox_gr0_ch1_clicked(bool checked)
{
    emit this->MaskChannel(1, checked);
}

void MainWindow::on_MASK_CHANNEL_checkBox_gr0_ch2_clicked(bool checked)
{
    emit this->MaskChannel(2, checked);
}

void MainWindow::on_MASK_CHANNEL_checkBox_gr0_ch3_clicked(bool checked)
{
    emit this->MaskChannel(3, checked);
}

void MainWindow::on_MASK_CHANNEL_checkBox_gr0_ch4_clicked(bool checked)
{
    emit this->MaskChannel(4, checked);
}

void MainWindow::on_MASK_CHANNEL_checkBox_gr0_ch5_clicked(bool checked)
{
    emit this->MaskChannel(5, checked);
}

void MainWindow::on_MASK_CHANNEL_checkBox_gr0_ch6_clicked(bool checked)
{
    emit this->MaskChannel(6, checked);
}

void MainWindow::on_MASK_CHANNEL_checkBox_gr0_ch7_clicked(bool checked)
{
    emit this->MaskChannel(7, checked);
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
    qDebug() << "SetTriggerValue_clicked() " << trigger_value_ch.ch << "   " << trigger_value_ch.value  << endl;
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



//void MainWindow::on_checkBox_25_clicked(bool checked)
//{
//    emit this->MaskChannel(9, checked);
//}

//void MainWindow::on_checkBox_31_clicked(bool checked)
//{
//    emit this->MaskChannel(10, checked);
//}

//void MainWindow::on_checkBox_32_clicked(bool checked)
//{
//    emit this->MaskChannel(11, checked);
//}

//void MainWindow::on_checkBox_33_clicked(bool checked)
//{
//    emit this->MaskChannel(12, checked);
//}

//void MainWindow::on_checkBox_34_clicked(bool checked)
//{
//    emit this->MaskChannel(13, checked);
//}

//void MainWindow::on_checkBox_35_clicked(bool checked)
//{
//    emit this->MaskChannel(14, checked);
//}



//void MainWindow::on_checkBox_41_clicked(bool checked)
//{
//    emit this->MaskChannel(15, checked);
//}

//void MainWindow::on_checkBox_42_clicked(bool checked)
//{
//    emit this->MaskChannel(16, checked);
//}



//void MainWindow::on_checkBox_43_clicked(bool checked)
//{
//    emit this->MaskChannel(17, checked);
//}

//void MainWindow::on_checkBox_44_clicked(bool checked)
//{
//    emit this->MaskChannel(18, checked);
//}



//void MainWindow::on_checkBox_45_clicked(bool checked)
//{
//    emit this->MaskChannel(19, checked);
//}



//void MainWindow::on_checkBox_51_clicked(bool checked)
//{
//    emit this->MaskChannel(20, checked);
//}



//void MainWindow::on_checkBox_52_clicked(bool checked)
//{
//    emit this->MaskChannel(21, checked);
//}



//void MainWindow::on_checkBox_53_clicked(bool checked)
//{
//    emit this->MaskChannel(22, checked);
//}



//void MainWindow::on_checkBox_54_clicked(bool checked)
//{
//    emit this->MaskChannel(23, checked);
//}



//void MainWindow::on_checkBox_55_clicked(bool checked)
//{
//    emit this->MaskChannel(24, checked);
//}

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

//void MainWindow::on_checkBox_12_clicked()
//{

//}

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

void MainWindow::on_MASK_CHANNEL_checkBox_gr1_ch0_clicked(bool checked)
{
    emit this->MaskChannel(1, checked); // mask the group, not channel
}

void MainWindow::on_MASK_CHANNEL_checkBox_gr2_ch0_clicked(bool checked)
{
    emit this->MaskChannel(2, checked); // mask the group, not channel
}

void MainWindow::on_MASK_CHANNEL_checkBox_gr3_ch0_clicked(bool checked)
{
    emit this->MaskChannel(3, checked); // mask the group, not channel
}

void MainWindow::on_MASK_CHANNEL_checkBox_gr4_ch0_clicked(bool checked)
{
    emit this->MaskChannel(4, checked); // mask the group, not channel
}

void MainWindow::on_MASK_CHANNEL_checkBox_gr5_ch0_clicked(bool checked)
{
    emit this->MaskChannel(5, checked); // mask the group, not channel
}

void MainWindow::on_MASK_CHANNEL_checkBox_gr6_ch0_clicked(bool checked)
{
    emit this->MaskChannel(6, checked); // mask the group, not channel
}

void MainWindow::on_MASK_CHANNEL_checkBox_gr7_ch0_clicked(bool checked)
{
    emit this->MaskChannel(7, checked); // mask the group, not channel
}

void MainWindow::on_radioButton_14_clicked(bool checked)
{

}

void MainWindow::on_radioButton_clicked()
{

}

void MainWindow::on_radioButton_clicked(bool checked)
{
    emit this->SetContinuousTrigger(false);
}

void MainWindow::on_pushButton_6_clicked(bool checked)
{

}

void MainWindow::on_lcdNumber_2_windowTitleChanged(const QString &title)
{

}

void MainWindow::on_radioButton_2_clicked(bool checked)
{
    emit this->SetRisingFalling(true);
}

void MainWindow::on_radioButton_3_clicked(bool checked)
{
    emit this->SetRisingFalling(false);
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->spinBox_dcoffset_gr0->setValue(0);
    ui->spinBox_dcoffset_gr1->setValue(0);
    ui->spinBox_dcoffset_gr2->setValue(0);
    ui->spinBox_dcoffset_gr3->setValue(0);
    ui->spinBox_dcoffset_gr4->setValue(0);
    ui->spinBox_dcoffset_gr5->setValue(0);
    ui->spinBox_dcoffset_gr6->setValue(0);
    ui->spinBox_dcoffset_gr7->setValue(0);
}

void MainWindow::on_spinBox_dcoffset_gr0_valueChanged(int arg1)
{
    emit this->SetDCOffset(0, arg1);
}

void MainWindow::on_spinBox_dcoffset_gr1_valueChanged(int arg1)
{
    emit this->SetDCOffset(1, arg1);
}

void MainWindow::on_spinBox_dcoffset_gr2_valueChanged(int arg1)
{
    emit this->SetDCOffset(2, arg1);
}

void MainWindow::on_spinBox_dcoffset_gr3_valueChanged(int arg1)
{
    emit this->SetDCOffset(3, arg1);
}

void MainWindow::on_spinBox_dcoffset_gr4_valueChanged(int arg1)
{
    emit this->SetDCOffset(4, arg1);
}

void MainWindow::on_spinBox_dcoffset_gr5_valueChanged(int arg1)
{
    emit this->SetDCOffset(5, arg1);
}

void MainWindow::on_spinBox_dcoffset_gr6_valueChanged(int arg1)
{
    emit this->SetDCOffset(6, arg1);
}

void MainWindow::on_spinBox_dcoffset_gr7_valueChanged(int arg1)
{
    emit this->SetDCOffset(7, arg1);
}

void MainWindow::on_spinBox_4_valueChanged(int arg1)
{
    emit this->SetRecordLength(arg1);

    ui->spinBox_5->setValue(worker->WDcfg.Ts * arg1);
}
