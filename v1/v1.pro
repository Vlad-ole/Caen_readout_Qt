#-------------------------------------------------
#
# Project created by QtCreator 2016-02-25T19:48:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = v1
TEMPLATE = app

INCLUDEPATH += $$PWD/inc
LIBS += -L"$$_PRO_FILE_PWD_/lib/Win32/Release/" -lCAENComm -lCAENDigitizer

SOURCES += main.cpp\
        mainwindow.cpp \
    src/fft.c \
    src/keyb.c \
    src/WaveDump.c \
    src/WDconfig.c \
    src/WDplot.c \
    src/X742CorrectionRoutines.c

HEADERS  += mainwindow.h \
    inc/CAENComm.h \
    inc/CAENDigitizer.h \
    inc/CAENDigitizerType.h \
    inc/fft.h \
    inc/keyb.h \
    inc/WaveDump.h \
    inc/WDconfig.h \
    inc/WDplot.h \
    inc/X742CorrectionRoutines.h

FORMS    += mainwindow.ui
