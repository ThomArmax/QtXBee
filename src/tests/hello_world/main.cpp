#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QTime>
#include <QDebug>

#include "xbee.h"
#include "atcommand.h"
#include "remoteatcommandrequest.h"

using namespace QtXBee;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    XBee xb("/dev/ttyUSB0");
    xb.setMode(XBee::API1Mode);

    QObject::connect(&xb, SIGNAL(receivedATCommandResponse(ATCommandResponse*)), &xb, SLOT(displayATCommandResponse(ATCommandResponse*)));
    QObject::connect(&xb, SIGNAL(receivedModemStatus(ModemStatus*)), &xb, SLOT(displayModemStatus(ModemStatus*)));
    QObject::connect(&xb, SIGNAL(receivedTransmitStatus(TransmitStatus*)), &xb, SLOT(displayTransmitStatus(TransmitStatus*)));
    QObject::connect(&xb, SIGNAL(receivedRXIndicator(ReceivePacket*)), &xb, SLOT(displayRXIndicator(ReceivePacket*)));
    QObject::connect(&xb, SIGNAL(receivedRXIndicatorExplicit(ExplicitRxIndicator*)), &xb, SLOT(displayRXIndicatorExplicit(ExplicitRxIndicator*)));
    QObject::connect(&xb, SIGNAL(receivedNodeIdentificationIndicator(NodeIdentificationIndicator*)), &xb, SLOT(displayNodeIdentificationIndicator(NodeIdentificationIndicator*)));
    QObject::connect(&xb, SIGNAL(receivedRemoteCommandResponse(RemoteATCommandResponse*)), &xb, SLOT(displayRemoteCommandResponse(RemoteATCommandResponse*)));

    ATCommand nd;
    nd.setCommand(ATCommand::Command_ND);
    xb.sendATCommandAsync(&nd);
    RemoteATCommandRequest ni;
    ni.setATCommand(ATCommand::Command_MY);
    //ni.setNetworkAddress(3332);
    ni.setNetworkAddress(0xFFFE);
    //ni.setDestinationAddress(0x13A20040CABB38);
    ni.setDestinationAddress(0xFFFF);

    qDebug() << "Remote NI command :" << ni.packet().toHex();
    xb.sendATCommandAsync(&ni);
    return a.exec();
}

