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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_3;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;
    QRadioButton *radioButton_8;
    QRadioButton *radioButton_9;
    QRadioButton *radioButton_10;
    QLCDNumber *lcdNumber;
    QLabel *label;
    QRadioButton *radioButton_11;
    QSpinBox *spinBox;
    QLabel *label_2;
    QCheckBox *checkBox;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QLabel *label_3;
    QTextEdit *textEdit;
    QLabel *label_4;
    QMenuBar *menuBar;
    QMenu *menuCAEN;
    QMenu *menuTriggers;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(959, 544);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(170, 10, 75, 23));
        radioButton = new QRadioButton(centralWidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(420, 40, 82, 17));
        radioButton_2 = new QRadioButton(centralWidget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(420, 60, 82, 17));
        radioButton_3 = new QRadioButton(centralWidget);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(420, 80, 82, 17));
        radioButton_4 = new QRadioButton(centralWidget);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(420, 100, 82, 17));
        radioButton_5 = new QRadioButton(centralWidget);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        radioButton_5->setGeometry(QRect(420, 120, 82, 17));
        radioButton_6 = new QRadioButton(centralWidget);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));
        radioButton_6->setGeometry(QRect(420, 140, 82, 17));
        radioButton_7 = new QRadioButton(centralWidget);
        radioButton_7->setObjectName(QStringLiteral("radioButton_7"));
        radioButton_7->setGeometry(QRect(420, 160, 82, 17));
        radioButton_8 = new QRadioButton(centralWidget);
        radioButton_8->setObjectName(QStringLiteral("radioButton_8"));
        radioButton_8->setGeometry(QRect(420, 180, 82, 17));
        radioButton_9 = new QRadioButton(centralWidget);
        radioButton_9->setObjectName(QStringLiteral("radioButton_9"));
        radioButton_9->setGeometry(QRect(180, 140, 82, 17));
        radioButton_10 = new QRadioButton(centralWidget);
        radioButton_10->setObjectName(QStringLiteral("radioButton_10"));
        radioButton_10->setGeometry(QRect(180, 160, 82, 17));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(640, 30, 101, 71));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(640, 10, 101, 16));
        radioButton_11 = new QRadioButton(centralWidget);
        radioButton_11->setObjectName(QStringLiteral("radioButton_11"));
        radioButton_11->setGeometry(QRect(180, 180, 82, 17));
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(170, 80, 81, 22));
        spinBox->setMinimum(1);
        spinBox->setMaximum(10000);
        spinBox->setSingleStep(10);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(170, 60, 81, 21));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(30, 130, 70, 17));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(400, 10, 81, 201));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 10, 106, 44));
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

        verticalLayout->addWidget(pushButton);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QPalette palette1;
        QBrush brush9(QColor(0, 255, 0, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush2);
        QBrush brush10(QColor(240, 240, 240, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush10);
        label_3->setPalette(palette1);

        verticalLayout->addWidget(label_3);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(460, 270, 471, 211));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(550, 230, 291, 31));
        QFont font;
        font.setPointSize(16);
        label_4->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        groupBox->raise();
        pushButton_3->raise();
        radioButton->raise();
        radioButton_2->raise();
        radioButton_3->raise();
        radioButton_4->raise();
        radioButton_5->raise();
        radioButton_6->raise();
        radioButton_7->raise();
        radioButton_8->raise();
        radioButton_9->raise();
        radioButton_10->raise();
        lcdNumber->raise();
        label->raise();
        radioButton_11->raise();
        spinBox->raise();
        label_2->raise();
        checkBox->raise();
        textEdit->raise();
        label_4->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 959, 21));
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

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CAEN readout (v 1.0)", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Write data", 0));
        radioButton->setText(QApplication::translate("MainWindow", "ch 0", 0));
        radioButton_2->setText(QApplication::translate("MainWindow", "ch 1", 0));
        radioButton_3->setText(QApplication::translate("MainWindow", "ch 2", 0));
        radioButton_4->setText(QApplication::translate("MainWindow", "ch 3", 0));
        radioButton_5->setText(QApplication::translate("MainWindow", "ch 4", 0));
        radioButton_6->setText(QApplication::translate("MainWindow", "ch 5", 0));
        radioButton_7->setText(QApplication::translate("MainWindow", "ch 6", 0));
        radioButton_8->setText(QApplication::translate("MainWindow", "ch 7", 0));
        radioButton_9->setText(QApplication::translate("MainWindow", "ASCII", 0));
        radioButton_10->setText(QApplication::translate("MainWindow", "BINARY", 0));
        label->setText(QApplication::translate("MainWindow", "Transfer speed", 0));
        radioButton_11->setText(QApplication::translate("MainWindow", "root tree", 0));
        label_2->setText(QApplication::translate("MainWindow", "Events per file", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Read data", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Source", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Connect!", 0));
        label_3->setText(QApplication::translate("MainWindow", "Device not connected", 0));
        label_4->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">WaveDump output</p></body></html>", 0));
        menuCAEN->setTitle(QApplication::translate("MainWindow", "Main", 0));
        menuTriggers->setTitle(QApplication::translate("MainWindow", "Triggers", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
