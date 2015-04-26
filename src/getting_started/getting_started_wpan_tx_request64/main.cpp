#include <QCoreApplication>
#include <QDebug>

#include <XBee>
#include <wpan/txrequest64.h>
#include <wpan/txstatusresponse.h>

using namespace QtXBee;
using namespace QtXBee::Wpan;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    XBee xb;
    TxRequest64 req;
    TxStatusResponse *rep = NULL;

    // Configure serial
    // port here

    if(!xb.open()) {
        qFatal("Failed to open serial port");
    }

    req.setDestinationAddress(0x13a20040cabb38);    // Remote node 64-bit address (remote node's SH+SL parameters)
    req.setData("Hello World !");                   // Data to send

    rep = qobject_cast<TxStatusResponse*>(xb.sendSync(&req));

    if(!rep) { // Check the response
        qFatal("No response");
    }

    qDebug() << "Transmit"
             << (rep->status() == TxStatusResponse::Success ?
                     qPrintable("succeeded") :
                     (qPrintable("failed with error " + TxStatusResponse::statusToString(rep->status()))));

    delete rep;

    return 0;
}
