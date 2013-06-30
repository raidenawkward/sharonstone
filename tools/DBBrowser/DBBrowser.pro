#-------------------------------------------------
#
# Project created by QtCreator 2013-06-27T20:12:27
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DBBrowser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    odbcdatabase.cpp \
    sscore/print/ssprinter.cpp \
    qtsqlcondition.cpp \
    qtsqldbvisitor.cpp

HEADERS  += mainwindow.h \
    sscore/data/ssdatabase.h \
    odbcdatabase.h \
    sscore/data/ssdatavisitor.h \
    sscore/data/ssdataprovider.h \
    sscore/data/ssdatabasefactory.h \
    sscore/data/ssdatavisitorfactory.h \
    sscore/data/ssdatavisitcmd.h \
    sscore/print/ssprintimpl.h \
    sscore/print/ssprinter.h \
    sscore/print/ssprintable.h \
    sscore/data/ssvisitcondition.h \
    qtsqlcondition.h \
    qtsqldbvisitor.h

FORMS    += mainwindow.ui
