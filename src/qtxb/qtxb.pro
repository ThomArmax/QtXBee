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
    digimeshframe.cpp \
    digimeshframeresponse.cpp \
    atcommandframe.cpp \
    atcommandqueueparamframe.cpp \
    modemstatusframe.cpp \
    transmitrequestframe.cpp \
    nodeidentificationindicatorframe.cpp \
    remoteatcommandrequestframe.cpp \
    remoteatcommandresponseframe.cpp \
    atcommandresponseframe.cpp \
    receivepacketframe.cpp \
    explicitrxindicatorframe.cpp \
    transmitstatusframe.cpp \
    explicitadressingcommandframe.cpp \
    nodediscoveryresponseparser.cpp

HEADERS += \
    global.h \
    xbee.h \
    digimeshframe.h \
    digimeshframeresponse.h \
    atcommandframe.h \
    atcommandqueueparamframe.h \
    modemstatusframe.h \
    transmitrequestframe.h \
    nodeidentificationindicatorframe.h \
    remoteatcommandresponseframe.h \
    remoteatcommandrequestframe.h \
    atcommandresponseframe.h \
    receivepacketframe.h \
    explicitrxindicatorframe.h \
    transmitstatusframe.h \
    explicitadressingcommandframe.h \
    nodediscoveryresponseparser.h

OTHER_FILES += \
    qtxb.pri \

unix {
    target.path = /usr/lib/QtXBee
    headers.path = /usr/include/QtXbee
    headers.files = $$HEADERS
    INSTALLS += target headers
}
