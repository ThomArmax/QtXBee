#-------------------------------------------------
#
# Project created by QtCreator 2015-03-15T16:38:16
#
#-------------------------------------------------

QT       -= gui

TARGET = QtXBee
TEMPLATE = lib

DEFINES += QTXBEE_LIBRARY

include(../../common.pri)

DESTDIR = ../../usr/lib/QtXBee

QT += serialport

SOURCES += \
    digimeshpacket.cpp \
    atcommandqueueparam.cpp \
    atcommand.cpp \
    txrequest.cpp \
    txrequestexplicit.cpp \
    atcommandremote.cpp \
    atcommandresponse.cpp \
    modemstatus.cpp \
    transmitstatus.cpp \
    rxindicator.cpp \
    remotecommandrequest.cpp \
    rxindicatorexplicit.cpp \
    nodeidentificationindicator.cpp \
    remotecommandresponse.cpp \
    digimeshpacketresponse.cpp \
    xbee.cpp

HEADERS += \
    digimeshpacket.h \
    atcommandqueueparam.h \
    atcommand.h \
    txrequest.h \
    txrequestexplicit.h \
    atcommandremote.h \
    atcommandresponse.h \
    modemstatus.h \
    transmitstatus.h \
    rxindicator.h \
    remotecommandrequest.h \
    rxindicatorexplicit.h \
    nodeidentificationindicator.h \
    remotecommandresponse.h \
    digimeshpacketresponse.h \
    xbee.h

OTHER_FILES += \
    qtxb.pri \

unix {
    target.path = /usr/lib/QtXBee
    headers.path = /usr/include/QtXbee
    headers.files = $$HEADERS
    INSTALLS += target headers
}
