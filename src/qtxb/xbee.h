#ifndef XBEE_H
#define XBEE_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "digimeshpacket.h"

#include "atcommand.h"
#include "atcommandqueueparam.h"
#include "txrequest.h"
#include "txrequestexplicit.h"
#include "remotecommandrequest.h"

#include "atcommandresponse.h"
#include "modemstatus.h"
#include "transmitstatus.h"
#include "rxindicator.h"
#include "rxindicatorexplicit.h"
#include "nodeidentificationindicator.h"
#include "remotecommandresponse.h"

class XBee : public QObject
{
    Q_OBJECT
public:
    explicit XBee(QObject *parent = 0);
    XBee(const QString & serialPort, QObject * parent = 0);

    bool setSerialPort(const QString & serialPort);
    bool applyDefaultSerialPortConfig();
    void send(DigiMeshPacket *request);
    void broadcast(QString data);
    void unicast(QByteArray address, QString data);
    ~XBee();

signals:
    void receivedATCommandResponse(ATCommandResponse *response);
    void receivedModemStatus(ModemStatus *response);
    void receivedTransmitStatus(TransmitStatus *response);
    void receivedRXIndicator(RXIndicator *response);
    void receivedRXIndicatorExplicit(RXIndicatorExplicit *response);
    void receivedNodeIdentificationIndicator(NodeIdentificationIndicator *response);
    void receivedRemoteCommandResponse(RemoteCommandResponse *response);

public slots:
    void displayATCommandResponse(ATCommandResponse *digiMeshPacket);
    void displayModemStatus(ModemStatus *digiMeshPacket);
    void displayTransmitStatus(TransmitStatus *digiMeshPacket);
    void displayRXIndicator(RXIndicator *digiMeshPacket);
    void displayRXIndicatorExplicit(RXIndicatorExplicit *digiMeshPacket);
    void displayNodeIdentificationIndicator(NodeIdentificationIndicator *digiMeshPacket);
    void displayRemoteCommandResponse(RemoteCommandResponse *digiMeshPacket);

private slots:
    void readData();

private:
    bool initSerialConnection();
    void processPacket(QByteArray packet);

private:
    QSerialPort *serial;
    bool xbeeFound;
    QByteArray buffer;
};

#endif
