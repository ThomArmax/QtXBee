#-------------------------------------------------
#
# Project created by QtCreator 2015-03-18T12:26:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_xbee_configuration
TEMPLATE = app

include(../tests.pri)

LIBS += -L/usr/lib/QtArmax-1.0/
LIBS += -lQtArmaxCore

SOURCES += main.cpp\
        mainwindow.cpp \
    xbeeparamitem.cpp \
    xbeeparamstablemodel.cpp

HEADERS  += mainwindow.h \
    xbeeparamitem.h \
    xbeeparamstablemodel.h

FORMS    += mainwindow.ui
