QT += core
QT -= gui

CONFIG += c++11

TARGET = windows-get-dll-version
#CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

win32 {
    LIBS += -lVersion
}
