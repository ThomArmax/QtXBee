#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QTime>

#include "xbee.h"
#include "atcommandframe.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    XBee xb("/dev/ttyUSB1");
    xb.setMode(XBee::API1Mode);

    QObject::connect(&xb, SIGNAL(receivedATCommandResponse(ATCommandResponseFrame*)), &xb, SLOT(displayATCommandResponse(ATCommandResponseFrame*)));
    QObject::connect(&xb, SIGNAL(receivedModemStatus(ModemStatusFrame*)), &xb, SLOT(displayModemStatus(ModemStatusFrame*)));
    QObject::connect(&xb, SIGNAL(receivedTransmitStatus(TransmitStatusFrame*)), &xb, SLOT(displayTransmitStatus(TransmitStatusFrame*)));
    QObject::connect(&xb, SIGNAL(receivedRXIndicator(ReceivePacketFrame*)), &xb, SLOT(displayRXIndicator(ReceivePacketFrame*)));
    QObject::connect(&xb, SIGNAL(receivedRXIndicatorExplicit(ExplicitRxIndicatorFrame*)), &xb, SLOT(displayRXIndicatorExplicit(ExplicitRxIndicatorFrame*)));
    QObject::connect(&xb, SIGNAL(receivedNodeIdentificationIndicator(NodeIdentificationIndicatorFrame*)), &xb, SLOT(displayNodeIdentificationIndicator(NodeIdentificationIndicatorFrame*)));
    QObject::connect(&xb, SIGNAL(receivedRemoteCommandResponse(RemoteATCommandResponseFrame*)), &xb, SLOT(displayRemoteCommandResponse(RemoteATCommandResponseFrame*)));

    ATCommandFrame atapi, atmy, atid, atdh, atdl;
    atapi.setCommand(ATCommandFrame::Command_AP);
    atapi.setParameter("1");
//    atmy.setCommand(ATCommand::Command_MY);
//    atid.setCommand(ATCommand::Command_ID);
//    atid.setParameter("3321");
//    atdh.setCommand(ATCommand::Command_DH);
//    atdl.setCommand(ATCommand::Command_DL);

//    xb.send(&atapi);
    xb.send(&atid);
//    xb.send(&atdh);
//    xb.send(&atdh);
    ATCommandFrame nd;
    nd.setCommand(ATCommandFrame::Command_ND);
    xb.send(&nd);

    return a.exec();
}

