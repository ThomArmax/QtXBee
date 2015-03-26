#-------------------------------------------------
#
# Project created by QtCreator 2015-03-24T18:12:45
#
#-------------------------------------------------

QT       += core gui
include(../examples.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = xbee_terminal
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
