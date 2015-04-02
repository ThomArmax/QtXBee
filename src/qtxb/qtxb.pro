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
    xbee.cpp \
    receivepacketframe.cpp \
    nodediscoveryresponseparser.cpp \
    remotenode.cpp \
    xbeepacket.cpp \
    xbeeresponse.cpp \
    atcommand.cpp \
    atcommandqueueparam.cpp \
    atcommandresponse.cpp \
    explicitadressingcommand.cpp \
    explicitrxindicator.cpp \
    modemstatus.cpp \
    nodeidentificationindicator.cpp \
    remoteatcommandresponse.cpp \
    transmitrequest.cpp \
    transmitstatus.cpp \
    remoteatcommandrequest.cpp

HEADERS += \
    global.h \
    xbee.h \
    nodediscoveryresponseparser.h \
    remotenode.h \
    xbeepacket.h \
    xbeeresponse.h \
    atcommand.h \
    atcommandqueueparam.h \
    atcommandresponse.h \
    explicitadressingcommand.h \
    explicitrxindicator.h \
    modemstatus.h \
    nodeidentificationindicator.h \
    receivepacket.h \
    remoteatcommandrequest.h \
    remoteatcommandresponse.h \
    transmitrequest.h \
    transmitstatus.h

OTHER_FILES += \
    qtxb.pri \

unix {
    target.path = /usr/lib/QtXBee
    headers.path = /usr/include/QtXbee
    headers.files = $$HEADERS
    INSTALLS += target headers
}
