/*
 * Copyright (C) 2015 ThomArmax (Thomas COIN)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * Thomas COIN <esvcorp@gmail.com> 18/04/2015
*/

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
    QObject::connect(&xb, SIGNAL(receivedTransmitStatus(ZBTxStatusResponse*)), &xb, SLOT(displayTransmitStatus(ZBTxStatusResponse*)));
    QObject::connect(&xb, SIGNAL(receivedRXIndicator(ZBRxResponse*)), &xb, SLOT(displayRXIndicator(ZBRxResponse*)));
    QObject::connect(&xb, SIGNAL(receivedRXIndicatorExplicit(ZBExplicitRxResponse*)), &xb, SLOT(displayRXIndicatorExplicit(ZBExplicitRxResponse*)));
    QObject::connect(&xb, SIGNAL(receivedNodeIdentificationIndicator(ZBIONodeIdentificationResponse*)), &xb, SLOT(displayNodeIdentificationIndicator(ZBIONodeIdentificationResponse*)));
    QObject::connect(&xb, SIGNAL(receivedRemoteCommandResponse(RemoteATCommandResponse*)), &xb, SLOT(displayRemoteCommandResponse(RemoteATCommandResponse*)));

//    ATCommand nd;
//    nd.setCommand(ATCommand::Command_ND);
//    xb.sendATCommandAsync(&nd);

//    ATCommand panId;
//    panId.setCommand(ATCommand::Command_ID);
//    xb.sendATCommandAsync(&panId);

    RemoteATCommandRequest ni;
    ni.setCommand(ATCommand::Command_NI);
//    ni.setDestinationAddress16(0xFFFE);
//    ni.setDestinationAddress64(0x13A20040CABB38);
    ni.setDestinationAddress16(0x2);
    ni.setDestinationAddress64(0x13A20040CABB38);
    xb.send(&ni);

    ni.setCommand(ATCommand::Command_SH);
    xb.send(&ni);
    ni.setCommand(ATCommand::Command_SL);
    xb.send(&ni);
    ni.setCommand(ATCommand::Command_ID);
    xb.send(&ni);
    ni.setCommand(ATCommand::Command_MY);
    xb.send(&ni);

//    WPAN::TXRequest16 tx16;
//    tx16.setDestinationAddress(0x0002);
//    tx16.setData("hello boy");
//    xb.send(&tx16);

//    WPAN::TXRequest64 tx64;
//    tx64.setDestinationAddress(0x13A20040CABB38);
//    tx64.setData("hello 64");
//    xb.send(&tx64);

//    tx64.setDestinationAddress(0xFFFFFFFF);
//    xb.send(&tx64);

    return a.exec();
}

