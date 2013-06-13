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
    print/ssprinter.cpp \
    testprintclass.cpp \
    templeteprinterimpl.cpp

HEADERS  += mainwindow.h \
    print/ssprintable.h \
    print/ssprintimpl.h \
    print/ssprinter.h \
    testprintclass.h \
    templeteprinterimpl.h

FORMS    += mainwindow.ui

RESOURCES += \
    mlsource.qrc
