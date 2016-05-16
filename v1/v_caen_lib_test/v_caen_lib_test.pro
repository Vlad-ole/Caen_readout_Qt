QT += core
QT -= gui

CONFIG += c++11

TARGET = v_caen_lib_test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += "D:/git_repositories/Caen_readout_Qt/v1/inc"
LIBS += -L"D:/git_repositories/Caen_readout_Qt/v1/lib/Win32/Debug"  \


