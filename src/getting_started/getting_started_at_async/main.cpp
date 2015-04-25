//main.cpp

#include <QCoreApplication>

#include <XBee>
#include <ATCommand>
#include <ATCommandResponse>

#include "xbeeresponseprinter.h"

using namespace QtXBee;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    XBeeResponsePrinter printer;
    XBee xb;
    ATCommand panId;

    // Configure serial
    // port here

    if(!xb.open()) {
        qFatal("Failed to open serial port");
    }

    panId.setCommand(ATCommand::Command_ID);

    QObject::connect(&xb,
                     SIGNAL(receivedATCommandResponse(ATCommandResponse*)),
                     &printer,
                     SLOT(onPacketReceived(ATCommandResponse*))
                     );

    xb.sendATCommandAsync(&panId);

    return a.exec();
}
