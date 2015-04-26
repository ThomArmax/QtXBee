#include <QCoreApplication>
#include <QDebug>

#include <XBee>
#include <wpan/txrequest16.h>
#include <wpan/txstatusresponse.h>

using namespace QtXBee;
using namespace QtXBee::Wpan;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    XBee xb;
    TxRequest16 req;
    TxStatusResponse *rep = NULL;

    // Configure serial
    // port here

    if(!xb.open()) {
        qFatal("Failed to open serial port");
    }

    req.setDestinationAddress(0x2); // Remote node 16-bit address (remote node's MY parameter)
    req.setData("Hello World !");   // Data to send

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
