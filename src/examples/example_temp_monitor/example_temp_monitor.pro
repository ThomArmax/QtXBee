TEMPLATE = app

QT += qml quick

include(../examples.pri)

SOURCES += main.cpp \
    tempmonitor.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    tempmonitor.h \
    xbee_temp_sensor/xbee_temp_sensor.ino

DISTFILES += \
    main.qml \
    qchartjs/QChart.js \
    qchartjs/QChart.qml \
    monitor.js
