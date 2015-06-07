#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "tempmonitor.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    TempMonitor monitor("/dev/ttyUSB0");

    monitor.setTempSensorAddress(2);
    monitor.start(1000);

    engine.rootContext()->setContextProperty("monitor", &monitor);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
