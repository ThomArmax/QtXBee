#include <QCoreApplication>
#include <QDebug>

#include <XBee>
#include <RemoteATCommandRequest>
#include <XBeeResponse>

using namespace QtXBee;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    XBee xb;
    XBeeResponse * rep = NULL;
    RemoteATCommandRequest remoteNI;

    // Configure serial
    // port here

    if(!xb.open()) {
        qFatal("Failed to open serial port");
    }

    remoteNI.setCommand(ATCommand::ATNI); // Node Indentifier
    remoteNI.setDestinationAddress16(0x2);
    rep = xb.sendSync(&remoteNI);

    if(!rep) {
        qFatal("No response");
    }

    qDebug() << qPrintable(rep->toString());
    qDebug() << "Node Identifier =" << rep->data();

    delete rep;

    return 0;
}
