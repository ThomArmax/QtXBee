#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QTime>

#include "xbee.h"
#include "txrequest.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    XBee xb("/dev/ttyUSB0");

    QObject::connect(&xb, SIGNAL(receivedATCommandResponse(ATCommandResponse*)), &xb, SLOT(displayATCommandResponse(ATCommandResponse*)));
    QObject::connect(&xb, SIGNAL(receivedModemStatus(ModemStatus*)), &xb, SLOT(displayModemStatus(ModemStatus*)));
    QObject::connect(&xb, SIGNAL(receivedTransmitStatus(TransmitStatus*)), &xb, SLOT(displayTransmitStatus(TransmitStatus*)));
    QObject::connect(&xb, SIGNAL(receivedRXIndicator(RXIndicator*)), &xb, SLOT(displayRXIndicator(RXIndicator*)));
    QObject::connect(&xb, SIGNAL(receivedRXIndicatorExplicit(RXIndicatorExplicit*)), &xb, SLOT(displayRXIndicatorExplicit(RXIndicatorExplicit*)));
    QObject::connect(&xb, SIGNAL(receivedNodeIdentificationIndicator(NodeIdentificationIndicator*)), &xb, SLOT(displayNodeIdentificationIndicator(NodeIdentificationIndicator*)));
    QObject::connect(&xb, SIGNAL(receivedRemoteCommandResponse(RemoteCommandResponse*)), &xb, SLOT(displayRemoteCommandResponse(RemoteCommandResponse*)));

    ATCommand atapi, atmy, atid;
    atapi.setCommand(ATCommand::Command_AP);
    atapi.setParameter("1");
    atmy.setCommand(ATCommand::Command_MY);
    atid.setCommand(ATCommand::Command_ID);

    xb.send(&atapi);
    xb.send(&atid);

    return a.exec();
}

