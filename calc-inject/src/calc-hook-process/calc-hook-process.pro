#-------------------------------------------------
#
# Project created by QtCreator 2019-09-08T08:59:39
#
#-------------------------------------------------

QT       += gui widgets

TARGET = $$qtLibraryTarget(calc-hook-process)
TEMPLATE = lib

DEFINES += CALCHOOKPROCESS_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        calchookprocess.cpp

HEADERS += \
        calchookprocess.h \
        calc-hook-process_global.h 

win32 {
    LIBS += -ldbghelp
    LIBS += -luser32
}

DIST_DIR = $$PWD/../../dist
include(../shared/shared.pri)
