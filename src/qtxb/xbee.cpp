#include "xbee.h"

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

#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QCoreApplication>

XBee::XBee(QObject *parent) :
    QObject(parent),
    serial(NULL),
    xbeeFound(false)
{
}

XBee::XBee(const QString &serialPort, QObject *parent) :
    QObject(parent),
    serial(NULL),
    xbeeFound(false)
{
    serial = new QSerialPort(serialPort, this);
    connect(serial, SIGNAL(readyRead()), SLOT(readData()));
    initSerialConnection();
}

XBee::~XBee()
{
    if(serial->isOpen())
    {
        serial->close();
        qDebug() << "XBEE: Serial Port closed successfully";
    }
}

bool XBee::setSerialPort(const QString &serialPort)
{
    if(serial) {
        serial->close();
        serial->setPortName(serialPort);
    }
    else {
        serial = new QSerialPort(serialPort, this);
        connect(serial, SIGNAL(readyRead()), SLOT(readData()));
    }
    applyDefaultSerialPortConfig();
    return initSerialConnection();
}

bool XBee::applyDefaultSerialPortConfig()
{
    if(serial == NULL)
        return false;

    return  serial->setBaudRate(QSerialPort::Baud9600) &&
            serial->setDataBits(QSerialPort::Data8) &&
            serial->setParity(QSerialPort::NoParity) &&
            serial->setStopBits(QSerialPort::OneStop) &&
            serial->setFlowControl(QSerialPort::NoFlowControl);
}

void XBee::displayATCommandResponse(ATCommandResponse *digiMeshPacket){
    qDebug() << "Received ATCommandResponse: ";
    qDebug() << qPrintable(digiMeshPacket->toString());
}
void XBee::displayModemStatus(ModemStatus *digiMeshPacket){
    qDebug() << "Received ModemStatus: " << digiMeshPacket->packet().toHex();
}
void XBee::displayTransmitStatus(TransmitStatus *digiMeshPacket){
    qDebug() << "Received TransmitStatus: " << digiMeshPacket->packet().toHex();
}
void XBee::displayRXIndicator(RXIndicator *digiMeshPacket){
    qDebug() << "Received RXIndicator: " << digiMeshPacket->data().toHex();
}
void XBee::displayRXIndicatorExplicit(RXIndicatorExplicit *digiMeshPacket){
    qDebug() << "Received RXIndicatorExplicit: " << digiMeshPacket->packet().toHex();
}
void XBee::displayNodeIdentificationIndicator(NodeIdentificationIndicator *digiMeshPacket){
    qDebug() << "Received NodeIdentificationIndicator: " << digiMeshPacket->packet().toHex();
}
void XBee::displayRemoteCommandResponse(RemoteCommandResponse *digiMeshPacket){
    qDebug() << "Received RemoteCommandResponse: " << digiMeshPacket->packet().toHex();
}

void XBee::send(DigiMeshPacket *request)
{
    request->assemblePacket();
    if(xbeeFound && serial->isOpen())
    {
        qDebug() << Q_FUNC_INFO << "Transmit: " << request->packet().toHex();
        serial->write(request->packet());
        serial->flush();
    }
    else
    {
        qDebug() << "XBEE: Cannot write to Serial Port - closed";
    }
}

void XBee::broadcast(QString data)
{
    TXRequest *request = new TXRequest(this);
    request->setData(data.toLatin1());
    send(request);
}

void XBee::unicast(QByteArray address, QString data)
{
    TXRequest *request = new TXRequest(this);
    request->setDestAddr64(address);
    request->setData(data.toLatin1());
    send(request);
}

void XBee::readData()
{
    unsigned startDelimiter = 0x7E;

    QByteArray data = serial->readAll();
    buffer.append(data);

    QByteArray packet;

    while(!buffer.isEmpty() && (unsigned char)buffer.at(0) != (unsigned char)startDelimiter) {
        buffer.remove(0, 1);
    }
    if(buffer.size() > 2) {
        unsigned length = buffer.at(2)+4;
        if((unsigned char)buffer.size() >= (unsigned char)length){
            packet.append(buffer.left(length));
            processPacket(packet);
            buffer.remove(0, length);
        }
    }
}

void XBee::processPacket(QByteArray packet)
{

    unsigned packetType = (unsigned char)packet.at(3);
    qDebug() << Q_FUNC_INFO << "packet type :" << QString::number(packetType, 16).prepend("0x");

    switch (packetType) {
    case DigiMeshPacket::ATCommandResponseFrame : {
        ATCommandResponse *response = new ATCommandResponse(packet);
        emit receivedATCommandResponse(response);
        response->deleteLater();
        break;
    }
    case DigiMeshPacket::ModemStatusFrame : {
        ModemStatus *response = new ModemStatus(packet);
        emit receivedModemStatus(response);
        response->deleteLater();
        break;
    }
    case DigiMeshPacket::TransmitStatusFrame : {
        TransmitStatus *response = new TransmitStatus(this);
        response->readPacket(packet);
        emit receivedTransmitStatus(response);
        break;
    }
    case DigiMeshPacket::RXIndicatorFrame : {
        RXIndicator *response = new RXIndicator(this);
        response->readPacket(packet);
        emit receivedRXIndicator(response);
        break;
    }
    case DigiMeshPacket::RXIndicatorExplicitFrame : {
        RXIndicatorExplicit *response = new RXIndicatorExplicit(this);
        response->readPacket(packet);
        emit receivedRXIndicatorExplicit(response);
        break;
    }
    case DigiMeshPacket::NodeIdentificationIndicatorFrame : {
        NodeIdentificationIndicator *response = new NodeIdentificationIndicator(this);
        response->readPacket(packet);
        emit receivedNodeIdentificationIndicator(response);
        break;
    }
    case DigiMeshPacket::RemoteCommandResponseFrame : {
        RemoteCommandResponse *response = new RemoteCommandResponse(packet);
        emit receivedRemoteCommandResponse(response);
        response->deleteLater();
        break;
    }
    default:
        qDebug() << "Error:  Unknown Packet: " << packet.toHex();
    }

}

//_________________________________________________________________________________________________
//___________________________________________PRIVATE API___________________________________________
//_________________________________________________________________________________________________

bool XBee::initSerialConnection()
{
    if(!serial)
        return false;

    if (serial->open(QIODevice::ReadWrite))
    {
        if(applyDefaultSerialPortConfig())
        {
            if(serial->isOpen())
            {
                qDebug() << "XBEE: Connected successfully";
                qDebug() << "XBEE: Serial Port Name: " << serial->portName();
                xbeeFound = true;
                return true;
            }
        }
    }
    else
    {
        qDebug() << "XBEE: Serial Port could not be opened";
    }

    return false;
}
