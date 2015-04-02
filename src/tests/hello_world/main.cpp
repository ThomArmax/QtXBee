#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QTime>
#include <QDebug>

#include "xbee.h"
#include "atcommandframe.h"
#include "remoteatcommandrequestframe.h"

using namespace QtXBee;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    XBee xb("/dev/ttyUSB0");
    xb.setMode(XBee::API1Mode);

    QObject::connect(&xb, SIGNAL(receivedATCommandResponse(ATCommandResponseFrame*)), &xb, SLOT(displayATCommandResponse(ATCommandResponseFrame*)));
    QObject::connect(&xb, SIGNAL(receivedModemStatus(ModemStatusFrame*)), &xb, SLOT(displayModemStatus(ModemStatusFrame*)));
    QObject::connect(&xb, SIGNAL(receivedTransmitStatus(TransmitStatusFrame*)), &xb, SLOT(displayTransmitStatus(TransmitStatusFrame*)));
    QObject::connect(&xb, SIGNAL(receivedRXIndicator(ReceivePacketFrame*)), &xb, SLOT(displayRXIndicator(ReceivePacketFrame*)));
    QObject::connect(&xb, SIGNAL(receivedRXIndicatorExplicit(ExplicitRxIndicatorFrame*)), &xb, SLOT(displayRXIndicatorExplicit(ExplicitRxIndicatorFrame*)));
    QObject::connect(&xb, SIGNAL(receivedNodeIdentificationIndicator(NodeIdentificationIndicatorFrame*)), &xb, SLOT(displayNodeIdentificationIndicator(NodeIdentificationIndicatorFrame*)));
    QObject::connect(&xb, SIGNAL(receivedRemoteCommandResponse(RemoteATCommandResponseFrame*)), &xb, SLOT(displayRemoteCommandResponse(RemoteATCommandResponseFrame*)));

    ATCommandFrame nd;
    nd.setCommand(ATCommandFrame::Command_ND);
    xb.sendATCommandAsync(&nd);
    RemoteATCommandRequestFrame ni;
    ni.setATCommand(ATCommandFrame::Command_MY);
    //ni.setNetworkAddress(3332);
    ni.setNetworkAddress(0xFFFE);
    //ni.setDestinationAddress(0x13A20040CABB38);
    ni.setDestinationAddress(0xFFFF);

    qDebug() << "Remote NI command :" << ni.packet().toHex();
    xb.sendATCommandAsync(&ni);
    return a.exec();
}

