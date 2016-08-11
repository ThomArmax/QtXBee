#-------------------------------------------------
#
# Project created by QtCreator 2015-03-15T16:38:16
#
#-------------------------------------------------

QT       -= gui

TARGET = QtXBee
TEMPLATE = lib

VERSION = 0.1.0

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
    zigbee/zbexplicittxrequest.cpp \
    zigbee/zbtxstatusresponse.cpp \
    zigbee/zbtxrequest.cpp \
    zigbee/zbrxresponse.cpp \
    zigbee/zbionodeidentificationresponse.cpp \
    zigbee/zbexplicitrxresponse.cpp

CORE_HEADERS += \
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
    ByteUtils \
    Global \
    XBee \
    ATCommand \
    ATCommandQueueParam \
    ATCommandResponse \
    ModemStatus \
    NodeDiscoveryResponseParser \
    RemoteATCommandRequest \
    RemoteATCommandResponse \
    RemoteNode \
    XBeePacket \
    XBeeResponse

WPAN_HEADERS += \
    wpan/txrequest16.h \
    wpan/txrequest64.h \
    wpan/txstatusresponse.h \
    wpan/rxbaseresponse.h \
    wpan/rxresponse16.h \
    wpan/rxresponse64.h \
    wpan/rxresponseiosamplebase.h \
    wpan/rxresponseiosample16.h \
    wpan/rxresponseiosample64.h \
    wpan/RxBaseResponse \
    wpan/RxResponse16 \
    wpan/RxResponse64 \
    wpan/RxResponseIoSample16 \
    wpan/RxResponseIoSample64 \
    wpan/RxResponseIoSampleBase \
    wpan/TxRequest16 \
    wpan/TxRequest64 \
    wpan/TxStatusResponse

ZB_HEADERS += \
    zigbee/zbexplicittxrequest.h \
    zigbee/zbexplicitrxresponse.h \
    zigbee/zbionodeidentificationresponse.h \
    zigbee/zbrxresponse.h \
    zigbee/zbtxrequest.h \
    zigbee/zbtxstatusresponse.h

HEADERS += \
    $$CORE_HEADERS \
    $$WPAN_HEADERS \
    $$ZB_HEADERS

OTHER_FILES += \
    qtxb.pri \

unix {
    target.path = /usr/lib/QtXBee

    core_headers.path = /usr/include/QtXbee
    core_headers.files = $$CORE_HEADERS

    wpan_headers.path = /usr/include/QtXbee/wpan
    wpan_headers.files = $$WPAN_HEADERS

    zb_headers.path = /usr/include/QtXbee/zigbee
    zb_headers.files = $$ZB_HEADERS
    INSTALLS += target core_headers wpan_headers zb_headers
}
