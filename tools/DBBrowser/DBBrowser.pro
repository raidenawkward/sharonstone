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
    qtdatavisitor.cpp

HEADERS  += mainwindow.h \
    sscore/data/ssdatabase.h \
    odbcdatabase.h \
    sscore/data/ssdatavisitor.h \
    sscore/data/ssdataprovider.h \
    qtdatavisitor.h \
    sscore/data/ssdatabasefactory.h \
    sscore/data/ssdatavisitorfactory.h \
    sscore/data/ssdatavisitcmd.h

FORMS    += mainwindow.ui
