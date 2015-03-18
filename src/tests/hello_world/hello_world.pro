#-------------------------------------------------
#
# Project created by QtCreator 2015-03-15T16:48:52
#
#-------------------------------------------------

QT       += core

QT       -= gui

include(../tests.pri)

TARGET = hello_world
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
LIBS += -lQtXBee

message("hello_world : libs =  $$LIBS")
