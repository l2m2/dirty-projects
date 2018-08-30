#-------------------------------------------------
#
# Project created by QtCreator 2018-08-29T13:21:36
#
#-------------------------------------------------

QT       += core gui
#CONFIG += luser32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WinAppHelper
TEMPLATE = app

LIBS += -luser32

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
