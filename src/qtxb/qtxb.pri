win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD//../../../usr/lib/QtXBee -lQtXBee0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD//../../../usr/lib/QtXBee -lQtXBee0
else:unix: LIBS += -L$$OUT_PWD/../../../usr/lib/QtXBee -lQtXBee

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

QT += serialport
