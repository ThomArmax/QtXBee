#-------------------------------------------------
#
# Project created by QtCreator 2015-06-08T19:44:52
#
#-------------------------------------------------

QT       += testlib
QT       -= gui

include(../tests.pri)

TARGET = tst_xbeeserialporttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_xbeeserialporttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
