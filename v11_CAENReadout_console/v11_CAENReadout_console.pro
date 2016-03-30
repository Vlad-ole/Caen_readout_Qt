QT += core
QT -= gui

CONFIG += c++11

INCLUDEPATH += $$PWD/inc
LIBS += -L"$$PWD/lib/Win32/Release/" -lCAENComm -lCAENDigitizer

QMAKE_CXXFLAGS += -fpermissive

TARGET = v11_CAENReadout_console
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    src/fft.cpp \
    src/keyb.cpp \
    src/X742CorrectionRoutines.cpp \
    src/WDplot.cpp \
    src/WDconfig.cpp \
    src/WaveDump.cpp

HEADERS += \
    inc/fft.h \
    inc/keyb.h \
    inc/X742CorrectionRoutines.h \
    inc/WDplot.h \
    inc/WDconfig.h \
    inc/WaveDump.h \
    inc/CAENDigitizerType.h \
    inc/CAENDigitizer.h \
    inc/CAENComm.h
