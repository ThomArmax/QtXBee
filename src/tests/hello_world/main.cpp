#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QTime>
#include <QDebug>

#include "XBee"
#include "atcommand.h"
#include "remoteatcommandrequest.h"
#include "wpan/txrequest16.h"
#include "wpan/txrequest64.h"

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

    ATCommand panId;
    panId.setCommand(ATCommand::Command_ID);
    xb.sendATCommandAsync(&panId);

//    RemoteATCommandRequest ni;
//    ni.setATCommand(ATCommand::Command_MY);
//    //ni.setNetworkAddress(3332);
//    ni.setNetworkAddress(0xFFFE);
//    //ni.setDestinationAddress(0x13A20040CABB38);
//    ni.setDestinationAddress(0xFFFF);
//    xb.sendATCommandAsync(&ni);

    WPAN::TXRequest16 tx16;
    tx16.setDestinationAddress(0x0002);
    tx16.setData("hello boy");
    xb.send(&tx16);

    WPAN::TXRequest64 tx64;
    tx64.setDestinationAddress(0x13A20040CABB38);
    tx64.setData("hello 64");
    xb.send(&tx64);

    tx64.setDestinationAddress(0xFFFFFFFF);
    xb.send(&tx64);

    return a.exec();
}

