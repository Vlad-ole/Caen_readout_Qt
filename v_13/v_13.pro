QT += core
QT -= gui

INCLUDEPATH += $$PWD/inc

LIBS += -L"$$PWD/lib/Win32/Release/" -lCAENComm -lCAENDigitizer

CONFIG += c++11

TARGET = v_13
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    src/WaveDump.c \
    src/fft.c \
    src/keyb.c \
    src/WDconfig.c \
    src/WDplot.c \
    src/X742CorrectionRoutines.c

HEADERS += \
    CAENComm.h \
    inc/CAENDigitizer.h \
    inc/CAENDigitizerType.h \
    inc/WDplot.h \
    inc/WDconfig.h \
    inc/CAENComm.h \
    inc/fft.h \
    inc/keyb.h \
    inc/WaveDump.h \
    inc/X742CorrectionRoutines.h
