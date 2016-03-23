/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLCDNumber *lcdNumber;
    QLabel *label;
    QCheckBox *checkBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QTextBrowser *textBrowser;
    QGroupBox *groupBox_3;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioButton_12;
    QRadioButton *radioButton_13;
    QGroupBox *groupBox;
    QSpinBox *spinBox_2;
    QGroupBox *groupBox_2;
    QSpinBox *spinBox_3;
    QSlider *verticalSlider;
    QPushButton *pushButton_2;
    QGroupBox *groupBox_8;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *radioButton_14;
    QRadioButton *radioButton_15;
    QGroupBox *groupBox_6;
    QPushButton *pushButton_3;
    QSpinBox *spinBox;
    QLabel *label_2;
    QGroupBox *groupBox_5;
    QRadioButton *radioButton_11;
    QRadioButton *radioButton_9;
    QRadioButton *radioButton_10;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QCustomPlot *widget_012;
    QSlider *verticalSlider_2;
    QGroupBox *groupBox_7;
    QLabel *label_6;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox;
    QDoubleSpinBox *doubleSpinBox_2;
    QLabel *label_8;
    QSpinBox *spinBox_4;
    QCustomPlot *widget_022;
    QCustomPlot *widget_032;
    QCustomPlot *widget_042;
    QCustomPlot *widget_052;
    QCustomPlot *widget_013;
    QCustomPlot *widget_014;
    QCustomPlot *widget_015;
    QCustomPlot *widget_024;
    QCustomPlot *widget_023;
    QCustomPlot *widget_025;
    QCustomPlot *widget_034;
    QCustomPlot *widget_033;
    QCustomPlot *widget_035;
    QCustomPlot *widget_044;
    QCustomPlot *widget_043;
    QCustomPlot *widget_045;
    QCustomPlot *widget_054;
    QCustomPlot *widget_053;
    QCustomPlot *widget_055;
    QCustomPlot *widget_011;
    QCustomPlot *widget_021;
    QCustomPlot *widget_041;
    QCustomPlot *widget_031;
    QCustomPlot *widget_051;
    QMenuBar *menuBar;
    QMenu *menuCAEN;
    QMenu *menuTriggers;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1860, 950);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(20, 650, 101, 71));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 610, 101, 16));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(160, 640, 70, 17));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 10, 121, 102));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(170, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(212, 0, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(85, 0, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(113, 0, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(212, 127, 127, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        pushButton->setPalette(palette);
        pushButton->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(pushButton);

        textBrowser = new QTextBrowser(layoutWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 130, 401, 231));
        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 30, 91, 91));
        layoutWidget1 = new QWidget(groupBox_4);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 20, 77, 61));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        radioButton_12 = new QRadioButton(layoutWidget1);
        radioButton_12->setObjectName(QStringLiteral("radioButton_12"));

        verticalLayout_2->addWidget(radioButton_12);

        radioButton_13 = new QRadioButton(layoutWidget1);
        radioButton_13->setObjectName(QStringLiteral("radioButton_13"));

        verticalLayout_2->addWidget(radioButton_13);

        groupBox = new QGroupBox(groupBox_3);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(100, 30, 81, 91));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        spinBox_2 = new QSpinBox(groupBox);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(10, 20, 61, 31));
        spinBox_2->setMaximum(7);
        groupBox_2 = new QGroupBox(groupBox_3);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(180, 30, 191, 91));
        groupBox_2->setFlat(false);
        groupBox_2->setCheckable(false);
        spinBox_3 = new QSpinBox(groupBox_2);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setGeometry(QRect(60, 50, 71, 31));
        spinBox_3->setMaximum(4095);
        verticalSlider = new QSlider(groupBox_2);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setGeometry(QRect(10, 20, 171, 31));
        verticalSlider->setMaximum(4095);
        verticalSlider->setOrientation(Qt::Horizontal);
        verticalSlider->setInvertedControls(true);
        verticalSlider->setTickPosition(QSlider::NoTicks);
        verticalSlider->setTickInterval(0);
        pushButton_2 = new QPushButton(groupBox_3);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 130, 91, 31));
        groupBox_8 = new QGroupBox(groupBox_3);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setGeometry(QRect(110, 130, 101, 91));
        layoutWidget_2 = new QWidget(groupBox_8);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 20, 77, 61));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        radioButton_14 = new QRadioButton(layoutWidget_2);
        radioButton_14->setObjectName(QStringLiteral("radioButton_14"));

        verticalLayout_4->addWidget(radioButton_14);

        radioButton_15 = new QRadioButton(layoutWidget_2);
        radioButton_15->setObjectName(QStringLiteral("radioButton_15"));

        verticalLayout_4->addWidget(radioButton_15);

        groupBox_6 = new QGroupBox(centralWidget);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(150, 10, 271, 121));
        pushButton_3 = new QPushButton(groupBox_6);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(30, 20, 75, 23));
        spinBox = new QSpinBox(groupBox_6);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(30, 70, 81, 22));
        spinBox->setMinimum(1);
        spinBox->setMaximum(10000);
        spinBox->setSingleStep(10);
        label_2 = new QLabel(groupBox_6);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 50, 81, 21));
        groupBox_5 = new QGroupBox(groupBox_6);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(120, 20, 120, 80));
        radioButton_11 = new QRadioButton(groupBox_5);
        radioButton_11->setObjectName(QStringLiteral("radioButton_11"));
        radioButton_11->setGeometry(QRect(20, 60, 82, 17));
        radioButton_9 = new QRadioButton(groupBox_5);
        radioButton_9->setObjectName(QStringLiteral("radioButton_9"));
        radioButton_9->setGeometry(QRect(20, 20, 82, 17));
        radioButton_10 = new QRadioButton(groupBox_5);
        radioButton_10->setObjectName(QStringLiteral("radioButton_10"));
        radioButton_10->setGeometry(QRect(20, 40, 82, 17));
        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget_012 = new QCustomPlot(centralWidget);
        widget_012->setObjectName(QStringLiteral("widget_012"));
        widget_012->setGeometry(QRect(760, 10, 271, 171));
        verticalSlider_2 = new QSlider(centralWidget);
        verticalSlider_2->setObjectName(QStringLiteral("verticalSlider_2"));
        verticalSlider_2->setGeometry(QRect(140, 610, 19, 160));
        verticalSlider_2->setOrientation(Qt::Vertical);
        groupBox_7 = new QGroupBox(centralWidget);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(10, 380, 401, 161));
        label_6 = new QLabel(groupBox_7);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 100, 47, 13));
        label_7 = new QLabel(groupBox_7);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 70, 47, 13));
        doubleSpinBox = new QDoubleSpinBox(groupBox_7);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(70, 70, 62, 22));
        doubleSpinBox->setMinimum(-10);
        doubleSpinBox->setMaximum(10);
        doubleSpinBox->setSingleStep(0.1);
        doubleSpinBox_2 = new QDoubleSpinBox(groupBox_7);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));
        doubleSpinBox_2->setGeometry(QRect(70, 100, 62, 22));
        doubleSpinBox_2->setMinimum(-10);
        doubleSpinBox_2->setMaximum(10);
        doubleSpinBox_2->setSingleStep(0.1);
        label_8 = new QLabel(groupBox_7);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 20, 71, 16));
        spinBox_4 = new QSpinBox(groupBox_7);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setGeometry(QRect(90, 20, 61, 22));
        spinBox_4->setMaximum(1000000);
        spinBox_4->setSingleStep(100);
        widget_022 = new QCustomPlot(centralWidget);
        widget_022->setObjectName(QStringLiteral("widget_022"));
        widget_022->setGeometry(QRect(760, 180, 271, 171));
        widget_032 = new QCustomPlot(centralWidget);
        widget_032->setObjectName(QStringLiteral("widget_032"));
        widget_032->setGeometry(QRect(760, 350, 271, 171));
        widget_042 = new QCustomPlot(centralWidget);
        widget_042->setObjectName(QStringLiteral("widget_042"));
        widget_042->setGeometry(QRect(760, 520, 271, 171));
        widget_052 = new QCustomPlot(centralWidget);
        widget_052->setObjectName(QStringLiteral("widget_052"));
        widget_052->setGeometry(QRect(760, 690, 271, 171));
        widget_013 = new QCustomPlot(centralWidget);
        widget_013->setObjectName(QStringLiteral("widget_013"));
        widget_013->setGeometry(QRect(1030, 10, 271, 171));
        widget_014 = new QCustomPlot(centralWidget);
        widget_014->setObjectName(QStringLiteral("widget_014"));
        widget_014->setGeometry(QRect(1300, 10, 271, 171));
        widget_015 = new QCustomPlot(centralWidget);
        widget_015->setObjectName(QStringLiteral("widget_015"));
        widget_015->setGeometry(QRect(1570, 10, 271, 171));
        widget_024 = new QCustomPlot(centralWidget);
        widget_024->setObjectName(QStringLiteral("widget_024"));
        widget_024->setGeometry(QRect(1300, 180, 271, 171));
        widget_023 = new QCustomPlot(centralWidget);
        widget_023->setObjectName(QStringLiteral("widget_023"));
        widget_023->setGeometry(QRect(1030, 180, 271, 171));
        widget_025 = new QCustomPlot(centralWidget);
        widget_025->setObjectName(QStringLiteral("widget_025"));
        widget_025->setGeometry(QRect(1570, 180, 271, 171));
        widget_034 = new QCustomPlot(centralWidget);
        widget_034->setObjectName(QStringLiteral("widget_034"));
        widget_034->setGeometry(QRect(1300, 350, 271, 171));
        widget_033 = new QCustomPlot(centralWidget);
        widget_033->setObjectName(QStringLiteral("widget_033"));
        widget_033->setGeometry(QRect(1030, 350, 271, 171));
        widget_035 = new QCustomPlot(centralWidget);
        widget_035->setObjectName(QStringLiteral("widget_035"));
        widget_035->setGeometry(QRect(1570, 350, 271, 171));
        widget_044 = new QCustomPlot(centralWidget);
        widget_044->setObjectName(QStringLiteral("widget_044"));
        widget_044->setGeometry(QRect(1300, 520, 271, 171));
        widget_043 = new QCustomPlot(centralWidget);
        widget_043->setObjectName(QStringLiteral("widget_043"));
        widget_043->setGeometry(QRect(1030, 520, 271, 171));
        widget_045 = new QCustomPlot(centralWidget);
        widget_045->setObjectName(QStringLiteral("widget_045"));
        widget_045->setGeometry(QRect(1570, 520, 271, 171));
        widget_054 = new QCustomPlot(centralWidget);
        widget_054->setObjectName(QStringLiteral("widget_054"));
        widget_054->setGeometry(QRect(1300, 690, 271, 171));
        widget_053 = new QCustomPlot(centralWidget);
        widget_053->setObjectName(QStringLiteral("widget_053"));
        widget_053->setGeometry(QRect(1030, 690, 271, 171));
        widget_055 = new QCustomPlot(centralWidget);
        widget_055->setObjectName(QStringLiteral("widget_055"));
        widget_055->setGeometry(QRect(1570, 690, 271, 171));
        widget_011 = new QCustomPlot(centralWidget);
        widget_011->setObjectName(QStringLiteral("widget_011"));
        widget_011->setGeometry(QRect(490, 10, 271, 171));
        widget_021 = new QCustomPlot(centralWidget);
        widget_021->setObjectName(QStringLiteral("widget_021"));
        widget_021->setGeometry(QRect(490, 180, 271, 171));
        widget_041 = new QCustomPlot(centralWidget);
        widget_041->setObjectName(QStringLiteral("widget_041"));
        widget_041->setGeometry(QRect(490, 520, 271, 171));
        widget_031 = new QCustomPlot(centralWidget);
        widget_031->setObjectName(QStringLiteral("widget_031"));
        widget_031->setGeometry(QRect(490, 350, 271, 171));
        widget_051 = new QCustomPlot(centralWidget);
        widget_051->setObjectName(QStringLiteral("widget_051"));
        widget_051->setGeometry(QRect(490, 690, 271, 171));
        MainWindow->setCentralWidget(centralWidget);
        groupBox_7->raise();
        groupBox_3->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        lcdNumber->raise();
        label->raise();
        checkBox->raise();
        groupBox_6->raise();
        widget_012->raise();
        verticalSlider_2->raise();
        widget_022->raise();
        widget_032->raise();
        widget_042->raise();
        widget_052->raise();
        widget_013->raise();
        widget_014->raise();
        widget_015->raise();
        widget_024->raise();
        widget_023->raise();
        widget_025->raise();
        widget_034->raise();
        widget_033->raise();
        widget_035->raise();
        widget_044->raise();
        widget_043->raise();
        widget_045->raise();
        widget_054->raise();
        widget_053->raise();
        widget_055->raise();
        widget_011->raise();
        widget_021->raise();
        widget_041->raise();
        widget_031->raise();
        widget_051->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1860, 21));
        menuCAEN = new QMenu(menuBar);
        menuCAEN->setObjectName(QStringLiteral("menuCAEN"));
        menuTriggers = new QMenu(menuBar);
        menuTriggers->setObjectName(QStringLiteral("menuTriggers"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuCAEN->menuAction());
        menuBar->addAction(menuTriggers->menuAction());

        retranslateUi(MainWindow);
        QObject::connect(verticalSlider, SIGNAL(valueChanged(int)), spinBox_3, SLOT(setValue(int)));
        QObject::connect(spinBox_3, SIGNAL(valueChanged(int)), verticalSlider, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CAEN readout (v 1.0)", 0));
        label->setText(QApplication::translate("MainWindow", "Transfer speed", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Read data", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Connect!", 0));
        textBrowser->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        textBrowser->setPlaceholderText(QApplication::translate("MainWindow", "Device not connected", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Trigger settings", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Choose trigger:", 0));
        radioButton_12->setText(QApplication::translate("MainWindow", "External", 0));
        radioButton_13->setText(QApplication::translate("MainWindow", "Internal", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Source", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Threshold", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Start acquisition", 0));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "Single / continious", 0));
        radioButton_14->setText(QApplication::translate("MainWindow", "Single", 0));
        radioButton_15->setText(QApplication::translate("MainWindow", "Continious", 0));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Output settings", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Write data", 0));
        label_2->setText(QApplication::translate("MainWindow", "Events per file", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Type of outputfile", 0));
        radioButton_11->setText(QApplication::translate("MainWindow", "root tree", 0));
        radioButton_9->setText(QApplication::translate("MainWindow", "ASCII", 0));
        radioButton_10->setText(QApplication::translate("MainWindow", "BINARY", 0));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Plot settings", 0));
        label_6->setText(QApplication::translate("MainWindow", "y bottom", 0));
        label_7->setText(QApplication::translate("MainWindow", "y top", 0));
        label_8->setText(QApplication::translate("MainWindow", "Record length", 0));
        menuCAEN->setTitle(QApplication::translate("MainWindow", "Main", 0));
        menuTriggers->setTitle(QApplication::translate("MainWindow", "Triggers", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
