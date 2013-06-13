#-------------------------------------------------
#
# Project created by QtCreator 2013-06-11T09:05:32
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MLBrowser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sscore/print/ssprinter.cpp \
    testprintclass.cpp \
    sscore/sstemplete.cpp \
    templeteprintingbrowser.cpp

HEADERS  += mainwindow.h \
    sscore/print/ssprintable.h \
    sscore/print/ssprintimpl.h \
    sscore/print/ssprinter.h \
    testprintclass.h \
    sscore/sstemplete.h \
    templeteprintingbrowser.h

FORMS    += mainwindow.ui

RESOURCES += \
    mlsource.qrc
