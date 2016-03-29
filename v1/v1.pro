#-------------------------------------------------
#
# Project created by QtCreator 2016-02-25T19:48:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = v1
TEMPLATE = app

INCLUDEPATH += $$PWD/inc
LIBS += -L"$$_PRO_FILE_PWD_/lib/Win32/Release/" -lCAENComm -lCAENDigitizer

QMAKE_CXXFLAGS += -fpermissive

SOURCES += main.cpp\
        mainwindow.cpp \
    src/fft.cpp \
    src/keyb.cpp \
    src/WaveDump.cpp \
    src/WDconfig.cpp \
    src/WDplot.cpp \
    src/X742CorrectionRoutines.cpp \
    src/qcustomplot.cpp \
    myworker.cpp \
    mythread.cpp


HEADERS  += mainwindow.h \
    inc/CAENComm.h \
    inc/CAENDigitizer.h \
    inc/CAENDigitizerType.h \
    inc/fft.h \
    inc/keyb.h \
    inc/WaveDump.h \
    inc/WDconfig.h \
    inc/WDplot.h \
    inc/X742CorrectionRoutines.h \
    inc/qcustomplot.h \
    myworker.h \
    mythread.h

FORMS    += mainwindow.ui
