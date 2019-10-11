#-------------------------------------------------
#
# Project created by QtCreator 2019-10-10T17:02:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = treeview-decoration-example
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    model.cpp \
    treeitem.cpp

HEADERS  += widget.h \
    model.h \
    treeitem.h

FORMS    += widget.ui

RESOURCES += \
    res.qrc
