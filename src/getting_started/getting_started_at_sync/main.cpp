#include <QCoreApplication>
#include <QDebug>
#include <XBee>
#include <ATCommand>
#include <ATCommandResponse>

using namespace QtXBee;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    XBee xb;
    ATCommand panId;
    ATCommandResponse *rep = NULL;

    // Configure serial
    // port here

    if(!xb.open()) {
        qFatal("Failed to open serial port");
    }

    panId.setCommand(ATCommand::ATID);
    rep = xb.sendATCommandSync(&panId);

    if(!rep) {
        qFatal("No response");
    }

    if(rep->status() != ATCommandResponse::Ok) {
        qWarning() << "AT Command Failed with status" << rep->status();
    }
    else {
        qDebug() << "PAN ID =" << rep->data().toHex();
    }

    delete rep;
    return 0;
}
