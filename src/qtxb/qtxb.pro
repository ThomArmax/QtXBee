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
    nodediscoveryresponseparser.cpp \
    remotenode.cpp \
    xbeepacket.cpp \
    xbeeresponse.cpp \
    atcommand.cpp \
    atcommandqueueparam.cpp \
    atcommandresponse.cpp \
    modemstatus.cpp \
    remoteatcommandresponse.cpp \
    remoteatcommandrequest.cpp \
    byteutils.cpp \
    wpan/txrequest16.cpp \
    wpan/txrequest64.cpp \
    wpan/txstatusresponse.cpp \
    wpan/rxbaseresponse.cpp \
    wpan/rxresponse16.cpp \
    wpan/rxresponse64.cpp \
    wpan/rxresponseiosamplebase.cpp \
    wpan/rxresponseiosample16.cpp \
    wpan/rxresponseiosample64.cpp \
    zigbee/transmitrequest.cpp \
    zigbee/transmitstatus.cpp \
    zigbee/nodeidentificationindicator.cpp \
    zigbee/receivepacket.cpp \
    zigbee/explicitadressingcommand.cpp \
    zigbee/explicitrxindicator.cpp

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
    modemstatus.h \
    remoteatcommandrequest.h \
    remoteatcommandresponse.h \
    byteutils.h \
    wpan/txrequest16.h \
    wpan/txrequest64.h \
    wpan/txstatusresponse.h \
    wpan/rxbaseresponse.h \
    wpan/rxresponse16.h \
    wpan/rxresponse64.h \
    wpan/rxresponseiosamplebase.h \
    wpan/rxresponseiosample16.h \
    wpan/rxresponseiosample64.h \
    zigbee/transmitrequest.h \
    zigbee/transmitstatus.h \
    zigbee/nodeidentificationindicator.h \
    zigbee/receivepacket.h \
    zigbee/explicitadressingcommand.h \
    zigbee/explicitrxindicator.h

OTHER_FILES += \
    qtxb.pri \

unix {
    target.path = /usr/lib/QtXBee
    headers.path = /usr/include/QtXbee
    headers.files = $$HEADERS
    INSTALLS += target headers
}
