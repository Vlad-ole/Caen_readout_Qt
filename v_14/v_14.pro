QT += core
QT -= gui

CONFIG += c++11

INCLUDEPATH += $$PWD/inc

LIBS += -L"$$PWD/lib/Win32/Release/" -lCAENComm -lCAENDigitizer

TARGET = v_14
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    src/fft.c \
    src/keyb.c \
    src/WaveDump.c \
    src/WDconfig.c \
    src/WDplot.c \
    src/X742CorrectionRoutines.c

HEADERS += \
    inc/CAENComm.h \
    inc/CAENDigitizer.h \
    inc/CAENDigitizerType.h \
    inc/fft.h \
    inc/keyb.h \
    inc/WaveDump.h \
    inc/WDconfig.h \
    inc/WDplot.h \
    inc/X742CorrectionRoutines.h
