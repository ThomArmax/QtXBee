#-------------------------------------------------
#
# Project created by QtCreator 2015-04-16T19:38:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../examples.pri)

TARGET = xbee_chat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
