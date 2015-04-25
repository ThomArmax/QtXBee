//xbeeresponseprinter.h

#ifndef XBEERESPONSEPRINTER
#define XBEERESPONSEPRINTER

#include <QObject>
#include <QDebug>
#include <ATCommandResponse>

using namespace QtXBee;

class XBeeResponsePrinter : public QObject {
    Q_OBJECT
public:
    explicit XBeeResponsePrinter(QObject *parent = 0) : QObject(parent) {}
   ~XBeeResponsePrinter() {}
public slots:
    void onPacketReceived(ATCommandResponse *packet) {
        qDebug() << "Received packet";
        qDebug() << qPrintable(packet->toString());
    }
};

#endif // XBEERESPONSEPRINTER

