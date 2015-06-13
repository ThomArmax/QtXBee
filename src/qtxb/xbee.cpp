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

#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

#include "XBee"
#include "Global"
#include "XBeePacket"
#include "ATCommand"
#include "ATCommandQueueParam"
#include "RemoteATCommandRequest"
#include "ATCommandResponse"
#include "ModemStatus"
#include "RemoteATCommandResponse"
#include "RemoteNode"
#include "NodeDiscoveryResponseParser"

#include "wpan/TxStatusResponse"
#include "wpan/RxResponse16"
#include "wpan/RxResponse64"

#include "zigbee/zbtxstatusresponse.h"
#include "zigbee/zbrxresponse.h"
#include "zigbee/zbexplicitrxresponse.h"
#include "zigbee/zbionodeidentificationresponse.h"
#include "zigbee/zbtxrequest.h"
#include "zigbee/zbexplicittxrequest.h"

namespace QtXBee {

/**
 * @brief XBee's default constructor.
 *
 * Allocates and initializes all parameters to there default values.
 * @note At this stage, no serial communication is initialized, so you can't communicate with your physical XBee until the serial port is initialized.
 * @param parent parent object
 * @sa XBee::XBee(const QString &serialPort, QObject *parent)
 * @sa XBee::setSerialPort()
 */
XBee::XBee(QObject *parent) :
    QObject(parent),
    m_serial(NULL),
    xbeeFound(false),
    m_mode(API1Mode),
    m_frameIdCounter(1),
    m_dh(0),
    m_dl(0),
    m_my(0),
    m_mp(0),
    m_nc(0),
    m_sh(0),
    m_sl(0),
    m_ni(QString()),
    m_se(0),
    m_de(0),
    m_ci(0),
    m_to(0),
    m_np(0),
    m_dd(0),
    m_cr(0)
{
}

/**
 * @brief XBee's constructor
 *
 * Allocates and initializes all parameters to there default values and try to open the serial port specified in argument.
 * @param serialPort serial port path (eg. /dev/ttyUSB0) on with the XBee is plugged.
 * @param parent parent object
 * @note In this case, the serial port configuration will ba set to :
 * - <b>Baud Rate</b> : 9600
 * - <b>Data Bits</b> : 8 bits
 * - <b>Parity</b> : No
 * - <b>Stop Bits</b> : One stop bit
 * - <b>Flow Control</b> : No flow control
 */
XBee::XBee(const QString &serialPort, QObject *parent) :
    QObject(parent),
    m_serial(NULL),
    xbeeFound(false),
    m_mode(API1Mode),
    m_frameIdCounter(1),
    m_dh(0),
    m_dl(0),
    m_my(0),
    m_mp(0),
    m_nc(0),
    m_sh(0),
    m_sl(0),
    m_ni(QString()),
    m_se(0),
    m_de(0),
    m_ci(0),
    m_to(0),
    m_np(0),
    m_dd(0),
    m_cr(0)
{
    m_serial = new QSerialPort(serialPort, this);
    connect(m_serial, SIGNAL(readyRead()), SLOT(readData()));
    applyDefaultSerialPortConfig();
}

/**
 * @brief Destroyes the XBee instance, frees allocated resources and close the serial port.
 */
XBee::~XBee()
{
    if(m_serial && m_serial->isOpen())
    {
        m_serial->close();
        qDebug() << "XBEE: Serial Port closed successfully";
    }
}

/**
 * @brief Opens the XBee' serial port
 * @return true if succeeded; false otherwise.
 * @sa XBee::close()
 * @sa XBee::setSerialPort()
 */
bool XBee::open()
{
    if(!m_serial)
    {
        qWarning() << "XBEE: No serial port defined";
        xbeeFound = false;
        return false;
    }

    if(m_serial->open(QIODevice::ReadWrite))
    {
        if(m_serial->isOpen())
        {
            qDebug() << "XBEE: Connected successfully";
            qDebug() << "XBEE: Serial Port Name: " << m_serial->portName();
            xbeeFound = true;
            startupCheck();
            return true;
        }
    }
    else
    {
        qDebug() << "XBEE: Serial Port" << m_serial->portName() << "could not be opened";
    }

    xbeeFound = false;
    return false;
}

/**
 * @brief Closes the XBee' serial port
 * @return true if succeeded; false otherwise
 */
bool XBee::close()
{
    if(m_serial) {
        m_serial->close();
    }
    xbeeFound = false;
    return true;
}

/**
 * @brief Sets the XBee's serial port, which we be used to communicate with it.
 * @note Default serial port will be used :
 * - <b>Baud Rate</b> : 9600
 * - <b>Data Bits</b> : 8 bits
 * - <b>Parity</b> : No
 * - <b>Stop Bits</b> : One stop bit
 * - <b>Flow Control</b> : No flow control
 * @param serialPort path to the serial port
 * @return true if succeeded; false otherwise
 * @sa XBee::setSerialPort(const QString &serialPort, const QSerialPort::BaudRate baudRate, const QSerialPort::DataBits dataBits, const QSerialPort::Parity parity, const QSerialPort::StopBits stopBits, const QSerialPort::FlowControl flowControl)
 * @sa XBee::applyDefaultSerialPortConfig()
 */
bool XBee::setSerialPort(const QString &serialPort)
{
    bool bRet = false;
    if(m_serial) {
        m_serial->close();
        m_serial->setPortName(serialPort);
        m_serial->disconnect(this);
        delete m_serial;
        m_serial = NULL;
    }
    m_serial = new QSerialPort(serialPort, this);
    connect(m_serial, SIGNAL(readyRead()), SLOT(readData()));

    bRet = applyDefaultSerialPortConfig();

    return bRet;
}

/**
 * @brief Configures the serial port used to communicate with the XBee.
 * @param serialPort path to the serial port
 * @param baudRate the baud rate
 * @param dataBits the data bits
 * @param parity the parity
 * @param stopBits the stop bits
 * @param flowControl the flow control
 * @return true if succeeded; false otherwise
 */
bool XBee::setSerialPort(const QString &serialPort, const QSerialPort::BaudRate baudRate, const QSerialPort::DataBits dataBits, const QSerialPort::Parity parity, const QSerialPort::StopBits stopBits, const QSerialPort::FlowControl flowControl)
{
    bool bRet = false;
    if(setSerialPort(serialPort)) {
        bRet = setSerialPortConfiguration(baudRate, dataBits, parity, stopBits, flowControl);
    }
    return bRet;
}

/**
 * @brief Configures the serial port used to communicate with the XBee.
 * @note This method must be called after have defining the serial port
 * @param baudRate the baud rate
 * @param dataBits the data bits
 * @param parity the parity
 * @param stopBits the stop bits
 * @param flowControl the flow control
 * @return true if succeeded; false otherwise.
 * @sa XBee::setSerialPort()
 */
bool XBee::setSerialPortConfiguration(const QSerialPort::BaudRate baudRate, const QSerialPort::DataBits dataBits, const QSerialPort::Parity parity, const QSerialPort::StopBits stopBits, const QSerialPort::FlowControl flowControl)
{
    if(m_serial == NULL) {
        qWarning() << Q_FUNC_INFO << "No serial port has been defined";
        return false;
    }

    return  m_serial->setBaudRate(baudRate) &&
            m_serial->setDataBits(dataBits) &&
            m_serial->setParity(parity) &&
            m_serial->setStopBits(stopBits) &&
            m_serial->setFlowControl(flowControl);
}

/**
 * @brief Applies the default configuration to the serial port.
 * <ul>
 * <li><b>Baud Rate</b> : 9600</li>
 * <li><b>Data Bits</b> : 8 bits</li>
 * <li><b>Parity</b> : No</li>
 * <li><b>Stop Bits</b> : One stop bit</li>
 * <li><b>Flow Control</b> : No flow control</li>
 * </ul>
 * @note You serial port must be set before calling this method
 * @return true if succeeded; false otherwise.
 * @sa XBee::setSerialPort()
 */
bool XBee::applyDefaultSerialPortConfig()
{
    if(m_serial == NULL) {
        qWarning() << "Applying serial port configuration to NULL QSerialPort !";
        return false;
    }

    return  m_serial->setBaudRate(QSerialPort::Baud9600) &&
            m_serial->setDataBits(QSerialPort::Data8) &&
            m_serial->setParity(QSerialPort::NoParity) &&
            m_serial->setStopBits(QSerialPort::OneStop) &&
            m_serial->setFlowControl(QSerialPort::NoFlowControl);
}

void XBee::displayATCommandResponse(ATCommandResponse *digiMeshPacket){
    qDebug() << "*********************************************";
    qDebug() << "Received ATCommandResponse: ";
    qDebug() << qPrintable(digiMeshPacket->toString());
    qDebug() << "*********************************************";
}
void XBee::displayModemStatus(ModemStatus *digiMeshPacket){
    qDebug() << "Received ModemStatus: ";
    qDebug() << qPrintable(digiMeshPacket->toString());
}
void XBee::displayTransmitStatus(ZBTxStatusResponse *digiMeshPacket){
    qDebug() << "Received TransmitStatus: " << digiMeshPacket->packet().toHex();
}
void XBee::displayRxIndicator(ZBRxResponse *digiMeshPacket){
    qDebug() << "Received RxIndicator: " << digiMeshPacket->data().toHex();
}
void XBee::displayRxIndicatorExplicit(ZBExplicitRxResponse *digiMeshPacket){
    qDebug() << "Received RxIndicatorExplicit: " << digiMeshPacket->packet().toHex();
}
void XBee::displayNodeIdentificationIndicator(ZBIONodeIdentificationResponse *digiMeshPacket){
    qDebug() << "Received NodeIdentificationIndicator: " << digiMeshPacket->packet().toHex();
}
void XBee::displayRemoteCommandResponse(RemoteATCommandResponse *digiMeshPacket){
    qDebug() << "*********************************************";
    qDebug() << "Received RemoteCommandResponse: ";
    qDebug() << qPrintable(digiMeshPacket->toString());
    qDebug() << "*********************************************";
}

/**
 * @brief Sends asynchronously the given packet
 * @param packet the packet to send.
 * @note A signal (corresponding the given packet) will be emitted when a response is received.
 *
 * For example, if the given packet is an ATCommand, the XBee::receivedATCommandResponse() will be emitted.
 */
void XBee::sendAsync(XBeePacket *packet)
{
    packet->assemblePacket();
    if(xbeeFound && m_serial->isOpen())
    {
        packet->setFrameId(m_frameIdCounter);
        if(m_frameIdCounter >= 255)
            m_frameIdCounter = 1;
        else m_frameIdCounter++;

        qDebug() << Q_FUNC_INFO << "Transmit: " << QString("0x").append(packet->packet().toHex());
        m_serial->write(packet->packet());
        m_serial->flush();
    }
    else
    {
        qDebug() << "XBEE: Cannot write to Serial Port" << m_serial->portName();
    }
}

/**
 * @brief Sends asynchronously the given command in command mode
 *
 * To put the module in command mode, you need first to send '+++'
 * When a response is received, the signal rawDataReceived() will be emitted.
 * @see http://knowledge.digi.com/articles/Knowledge_Base_Article/The-AT-Command-Set
 * @param command the command to send
 * @return true if succeeded; false otherwise.
 * @note The XBee must be in XBee::CommandMode, @see XBee::setMode()
 */
bool XBee::sendCommandAsync(const QByteArray &command)
{
    if(m_mode != CommandMode)
        return false;
    if(!xbeeFound)
        return false;
    if(!m_serial)
        return false;
    m_serial->write(command);
    return true;
}

/**
 * @brief Sends synchronously the given command using in command mode
 *
 * To put the module in command mode, you need first to send '+++'
 * @see http://knowledge.digi.com/articles/Knowledge_Base_Article/The-AT-Command-Set
 * @param command the command to send
 * @return the response (the read data from the serial port are appended until the last received character is <CR> (0x0D))
 * @note The XBee must be in XBee::CommandMode
 * @see XBee::setMode()
 */
QByteArray XBee::sendCommandSync(const QByteArray &command)
{
    QByteArray rep;
    if(m_mode == CommandMode && xbeeFound && m_serial)
    {
        m_serial->blockSignals(true);
        m_serial->write(command);
        m_serial->flush();
        while(m_serial->waitForReadyRead(10))
            rep.append(m_serial->readAll());

        m_serial->blockSignals(false);

        if(!rep.isEmpty()) {
        if(rep.at(rep.size()-1) == 0x0D)
            rep.remove(rep.size()-1, 1);
        }
    }
    return rep;
}

/**
 * @brief Sends synchronously the given packet
 * @param packet the packet to send.
 * @retval the associated XBeeResponse in case of success
 * @retval NULL if failed
 * @note XBee don't take the XBeeResponse's ownership, you have to.
 */
XBeeResponse * XBee::sendSync(XBeePacket *packet)
{
    XBeeResponse * rep = NULL;
    QByteArray repPacket;
    QByteArray tmp;

    if(!xbeeFound) {
        qWarning() << Q_FUNC_INFO << "No serial configured, can't send packet";
        return NULL;
    }

    if(packet == NULL) {
        qWarning() << Q_FUNC_INFO << "Invalid argument: null packet";
        return NULL;
    }

    packet->setFrameId(m_frameIdCounter);
    if(m_frameIdCounter >= 255)
        m_frameIdCounter = 1;
    else m_frameIdCounter++;

    packet->assemblePacket();

    m_serial->blockSignals(true);

    m_serial->write(packet->packet());
    m_serial->flush();
    while(m_serial->waitForReadyRead(100)) {
        tmp.append(m_serial->readAll());
    }

    while(!tmp.isEmpty() && (unsigned char)tmp.at(0) != (unsigned char)XBeePacket::StartDelimiter) {
        tmp.remove(0, 1);
    }

    repPacket = tmp;

    m_serial->blockSignals(false);

    if(repPacket.size() > 0) {
        rep = processPacket(repPacket, false);
        if(!rep) {
            qDebug() << Q_FUNC_INFO << "Failed to process received response !";
        }
    }
    else {
        qDebug() << Q_FUNC_INFO << "no response to";
        qDebug() << qPrintable(packet->toString());
    }
    return rep;
}

/**
 * @brief Sends an ATCommand asynchronously
 *
 * The XBee::receivedATCommandResponse() signal will be emmited when a response to the sent ATCommand is received.
 * @param command
 */
void XBee::sendATCommandAsync(ATCommand *command)
{
    sendAsync(command);
}

/**
 * @brief Sends an ATCommand asynchronously
 *
 * The XBee::receivedATCommandResponse() signal will be emmited when a response to the sent ATCommand is received.
 * @param command
 * @note This method is not implemented yet
 * @todo Implement this method
 */
void XBee::sendATCommandAsync(const QByteArray &data)
{
    Q_UNUSED(data);
}


/**
 * @brief Sends an ATCommand synchronously
 * @param command
 * @return the corresponding ATCommandResponse; or null.
 * @note XBee don't take the ATCommandResponse's ownership, you have to.
 */
ATCommandResponse * XBee::sendATCommandSync(ATCommand *command)
{
    Q_ASSERT(command);
    ATCommandResponse * rep = NULL;
    QByteArray repPacket;
    QByteArray tmp;

    if(!xbeeFound) {
        qWarning() << Q_FUNC_INFO << "No serial configured, can't send packet";
        return NULL;
    }

    if(command == NULL) {
        qWarning() << Q_FUNC_INFO << "Invalid argument: null packet";
        return NULL;
    }

    command->setFrameId(m_frameIdCounter);
    if(m_frameIdCounter >= 255)
        m_frameIdCounter = 1;
    else m_frameIdCounter++;

    command->assemblePacket();

    m_serial->blockSignals(true);

    m_serial->write(command->packet());
    m_serial->flush();
    while(m_serial->waitForReadyRead(100)) {
        tmp.append(m_serial->readAll());
    }

    while(!tmp.isEmpty() && (unsigned char)tmp.at(0) != (unsigned char)XBeePacket::StartDelimiter) {
        tmp.remove(0, 1);
    }

    repPacket = tmp;

    m_serial->blockSignals(false);

    if(repPacket.size() > 0) {
        rep = new ATCommandResponse();
        rep->setPacket(repPacket);
    }
    else {
        qDebug() << Q_FUNC_INFO << "no response to";
        qDebug() << qPrintable(command->toString());
    }
    return rep;
}

/**
 * @brief Sends an ATCommand synchronously
 * @param atcommand
 * @return the corresponding ATCommandResponse; or null.
 * @note XBee don't take the ATCommandResponse's ownership, you have to.
 */
ATCommandResponse * XBee::sendATCommandSync(const QByteArray &atcommand)
{
    ATCommandResponse * rep = NULL;
    if(atcommand.size() >= 2)
    {
        ATCommand at;
        at.setCommand(atcommand.mid(0, 2));
        if(atcommand.size() > 2) {
            at.setParameter(atcommand.mid(2, atcommand.size()-2));
        }
        rep = sendATCommandSync(&at);
    }
    else {
        qWarning() << Q_FUNC_INFO << "bad command" << atcommand;
    }
    return rep;
}

/**
 * @brief Loads the XBee's addressing properties
 * - DH
 * - DL
 * - MY
 * - MP
 * - NC
 * - SH
 * - SL
 * - NI
 * - SE
 * - DE
 * - CI
 * - TO
 * - NP
 * - DD
 * - CR
 */
void XBee::loadAddressingProperties() {
    ATCommand at;
    at.setCommand(ATCommand::ATDH); sendATCommandAsync(&at);
    at.setCommand(ATCommand::ATDL); sendATCommandAsync(&at);
    at.setCommand(ATCommand::ATMY); sendATCommandAsync(&at);
    at.setCommand(ATCommand::ATMP); sendATCommandAsync(&at);
    at.setCommand(ATCommand::ATNC); sendATCommandAsync(&at);
    at.setCommand(ATCommand::ATSH); sendATCommandAsync(&at);
    at.setCommand(ATCommand::ATSL); sendATCommandAsync(&at);
    at.setCommand(ATCommand::ATNI); sendATCommandAsync(&at);
    at.setCommand(ATCommand::ATSE); sendATCommandAsync(&at);
    at.setCommand(ATCommand::ATDE); sendATCommandAsync(&at);
    at.setCommand(ATCommand::ATCI); sendATCommandAsync(&at);
    at.setCommand(ATCommand::ATTO); sendATCommandAsync(&at);
    at.setCommand(ATCommand::ATNP); sendATCommandAsync(&at);
    at.setCommand(ATCommand::ATDD); sendATCommandAsync(&at);
    at.setCommand(ATCommand::ATCR); sendATCommandAsync(&at);
}

// Adressing
bool XBee::setDH(const quint32 dh) {
    ATCommand at;
    at.setCommand(ATCommand::ATDH);
    at.setParameter(QByteArray::number(dh));
    sendATCommandAsync(&at);
    return true;
}

bool XBee::setDL(const quint32 dl) {
    ATCommand at;
    at.setCommand(ATCommand::ATDL);
    at.setParameter(QByteArray::number(dl));
    sendATCommandAsync(&at);
    return true;
}

bool XBee::setMY(const quint16 my) {
    ATCommand at;
    at.setCommand(ATCommand::ATMY);
    at.setParameter(QByteArray::number(my));
    sendATCommandAsync(&at);
    return true;
}

bool XBee::setMP(const quint16 mp) {
    ATCommand at;
    at.setCommand(ATCommand::ATMP);
    at.setParameter(QByteArray::number(mp));
    sendATCommandAsync(&at);
    return true;
}

bool XBee::setNC(const quint32 nc) {
    ATCommand at;
    at.setCommand(ATCommand::ATNC);
    at.setParameter(QByteArray::number(nc));
    sendATCommandAsync(&at);
    return true;
}

bool XBee::setSH(const quint32 sh) {
    ATCommand at;
    at.setCommand(ATCommand::ATSH);
    at.setParameter(QByteArray::number(sh));
    sendATCommandAsync(&at);
    return true;
}

bool XBee::setSL(const quint32 sl) {
    ATCommand at;
    at.setCommand(ATCommand::ATSL);
    at.setParameter(QByteArray::number(sl));
    sendATCommandAsync(&at);
    return true;
}

bool XBee::setNI(const QString & ni) {
    ATCommand at;
    at.setCommand(ATCommand::ATNI);
    at.setParameter(ni.toUtf8());
    sendATCommandAsync(&at);
    return true;
}

bool XBee::setSE(const quint8 se) {
    ATCommand at;
    at.setCommand(ATCommand::ATSE);
    at.setParameter(QByteArray::number(se));
    sendATCommandAsync(&at);
    return true;
}

bool XBee::setDE(const quint8 de) {
    ATCommand at;
    at.setCommand(ATCommand::ATDE);
    at.setParameter(QByteArray::number(de));
    sendATCommandAsync(&at);
    return true;
}

bool XBee::setCI(const quint8 ci) {
    ATCommand at;
    at.setCommand(ATCommand::ATCI);
    at.setParameter(QByteArray::number(ci));
    sendATCommandAsync(&at);
    return true;
}

bool XBee::setTO(const quint8 to) {
    ATCommand at;
    at.setCommand(ATCommand::ATTO);
    at.setParameter(QByteArray::number(to));
    sendATCommandAsync(&at);
    return true;
}

bool XBee::setNP(const quint8 np) {
    ATCommand at;
    at.setCommand(ATCommand::ATNP);
    at.setParameter(QByteArray::number(np));
    sendATCommandAsync(&at);
    return true;
}

bool XBee::setDD(const quint16 dd) {
    ATCommand at;
    at.setCommand(ATCommand::ATDD);
    at.setParameter(QByteArray::number(dd));
    sendATCommandAsync(&at);
    return true;
}

bool XBee::setCR(const quint8 cr) {
    ATCommand at;
    at.setCommand(ATCommand::ATCR);
    at.setParameter(QByteArray::number(cr));
    sendATCommandAsync(&at);
    return true;
}

/**
 * @brief Sets the XBee's mode
 * @param mode
 * @return true if succeeded; false otherwise.
 * @todo Set the mode into the XBee, not only the class attribute
 * @sa XBee::Mode
 * @sa XBee::mode()
 */
bool XBee::setMode(const Mode mode)
{
    m_mode = mode;
    buffer.clear();
    return true;
}

/**
 * @brief Returns the XBee's mode
 * @return the XBee's mode
 * @sa XBee::setMode()
 * @sa XBee::Mode
 */
XBee::Mode XBee::mode() const
{
    return m_mode;
}

//_________________________________________________________________________________________________
//___________________________________________PRIVATE API___________________________________________
//_________________________________________________________________________________________________
void XBee::readData()
{
    unsigned startDelimiter = 0x7E;

    QByteArray data = m_serial->readAll();
    QByteArray packet;
    buffer.append(data);

    if(m_mode == CommandMode) {
        if(buffer.endsWith(13)) {
            emit rawDataReceived(buffer);
            buffer.clear();
        }
    }
    else {

        while(!buffer.isEmpty() && (unsigned char)buffer.at(0) != (unsigned char)startDelimiter) {
            buffer.remove(0, 1);
        }
        if(buffer.size() > 2) {
            unsigned length = buffer.at(2)+4;
            if((unsigned char)buffer.size() >= (unsigned char)length) {
                packet.append(buffer.left(length));
                qDebug() << Q_FUNC_INFO << QString("0x").append(packet.toHex());
                processPacket(packet, true);
                buffer.remove(0, length);
            }
        }
    }
}

XBeeResponse * XBee::processPacket(QByteArray packet, const bool async)
{
    unsigned packetType = (unsigned char)packet.at(3);

    switch (packetType) {
    /********************** WPAN **********************/
    case XBeePacket::Rx16ResponseId : {
        Wpan::RxResponse16 * response = new Wpan::RxResponse16();
        response->setPacket(packet);
        if(async) {
            emit receivedRxResponse16(response);
            response->deleteLater();
        }
        else {
            return response;
        }
        break;
    }
    case XBeePacket::Rx64ResponseId : {
        Wpan::RxResponse64 * response = new Wpan::RxResponse64();
        response->setPacket(packet);
        if(async) {
            emit receivedRxResponse64(response);
            response->deleteLater();
        }
        else {
            return response;
        }
        break;
    }
    case XBeePacket::TxStatusResponseId : {
        Wpan::TxStatusResponse * response = new Wpan::TxStatusResponse();
        response->setPacket(packet);
        if(async) {
            emit receivedTransmitStatus(response);
            response->deleteLater();
        }
        else {
            return response;
        }
        break;
    }
    /********************** QtXBee **********************/
    case XBeePacket::ATCommandResponseId : {
        ATCommandResponse *response = new ATCommandResponse(packet);
        if(async) {
            processATCommandRespone(response);
            response->deleteLater();
        }
        else {
            return response;
        }
        break;
    }
    case XBeePacket::ModemStatusResponseId : {
        ModemStatus *response = new ModemStatus(packet);
        if(async) {
            emit receivedModemStatus(response);
            response->deleteLater();
        }
        else {
            return response;
        }
        break;
    }
    case XBeePacket::RemoteATCommandResponseId : {
        RemoteATCommandResponse *response = new RemoteATCommandResponse(packet);
        if(async) {
            emit receivedRemoteCommandResponse(response);
            response->deleteLater();
        }
        else {
            return response;
        }
        break;
    }
    /********************** ZigBee **********************/
    case XBeePacket::ZBTxStatusResponseId : {
        ZBTxStatusResponse *response = new ZBTxStatusResponse(this);
        response->readPacket(packet);
        if(async) {
            emit receivedTransmitStatus(response);
        }
        else {
            return response;
        }
        break;
    }
    case XBeePacket::ZBRxResponseId : {
        ZBRxResponse *response = new ZBRxResponse(this);
        response->readPacket(packet);
        if(async) {
            emit receivedRxIndicator(response);
        }
        else {
            return response;
        }
        break;
    }
    case XBeePacket::ZBExplicitRxResponseId : {
        ZBExplicitRxResponse *response = new ZBExplicitRxResponse(this);
        response->readPacket(packet);
        if(async) {
            emit receivedRxIndicatorExplicit(response);
        }
        else {
            return response;
        }
        break;
    }
    case XBeePacket::ZBIONodeIdentificationId : {
        ZBIONodeIdentificationResponse *response = new ZBIONodeIdentificationResponse(this);
        response->setPacket(packet);
        if(async) {
            emit receivedNodeIdentificationIndicator(response);
        }
        else {
            return response;
        }
        break;
    }
    default:
        qDebug() << Q_FUNC_INFO << qPrintable(QString("Error: Unknown or Unhandled Packet (type=%1): 0x%2").
                                              arg(packetType,0,16).
                                              arg(QString(packet.toHex())));
    }
    return NULL;
}

void XBee::processATCommandRespone(ATCommandResponse *rep) {
    Q_ASSERT(rep);
    ATCommand::ATCommandType at = rep->atCommand();
    QByteArray data = rep->data().toHex();
    quint32 dataInt = QString(data).toInt(0, 16);

    qDebug() << Q_FUNC_INFO << "AT command" << ATCommand::atCommandToString(at) << QString("0x%1").arg(at , 0, 16) << " : " << data << dataInt;

    switch(at) {
    // Addressing
    case ATCommand::ATDH : m_dh = dataInt; emit DHChanged(m_dh); break;
    case ATCommand::ATDL : m_dl = dataInt; emit DLChanged(m_dl); break;
    case ATCommand::ATMY : m_my = dataInt; emit MYChanged(m_my); break;
    case ATCommand::ATMP : m_mp = dataInt; emit MPChanged(m_mp); break;
    case ATCommand::ATNC : m_nc = dataInt; emit NCChanged(m_nc); break;
    case ATCommand::ATSH : m_sh = dataInt; emit SHChanged(m_sh); break;
    case ATCommand::ATSL : m_sl = dataInt; emit SLChanged(m_sl); break;
    case ATCommand::ATNI : m_ni = data; emit NIChanged(m_ni); break;
    case ATCommand::ATSE : m_se = dataInt; emit SEChanged(m_se); break;
    case ATCommand::ATDE : m_de = dataInt; emit DEChanged(m_de); break;
    case ATCommand::ATCI : m_ci = dataInt; emit CIChanged(m_ci); break;
    case ATCommand::ATTO : m_to = dataInt; emit TOChanged(m_to); break;
    case ATCommand::ATNP : m_np = dataInt; emit NPChanged(m_np); break;
    case ATCommand::ATDD : m_dd = dataInt; emit DDChanged(m_dd); break;
    case ATCommand::ATCR : m_cr = dataInt; emit CRChanged(m_cr); break;

    case ATCommand::ATND : {
        RemoteNode * node = NULL;
        NodeDiscoveryResponseParser nd;
        if((node = nd.parseData(rep->data())) != NULL) {
            node->setParent(this);
            qDebug() << "Discovered node :" << qPrintable(node->toString());
        }

        break;
    }
    default:
        qWarning() << Q_FUNC_INFO << "Unhandled AT command" <<  QString("0x%1 (%2)").arg(at , 0, 16).arg(ATCommand::atCommandToString(at));
    }
    emit receivedATCommandResponse(rep);
}

bool XBee::startupCheck()
{
    return true;
    bool bRet = false;
    ATCommand at;
    ATCommandResponse * rep = NULL;
    QString errorStr;
    Mode currentMode;

    qDebug() << "****************** XBEE CONFIGURATION CHECKUP ******************";
    if(xbeeFound)
    {
        // Go in command mode
        if(enterInCommandMode()) {
            QByteArray r;
            r = synchronousCmd(QByteArray("ATAP").append(0x0d));
            if(!r.isEmpty()) {
                currentMode = (Mode) r.toInt();
                if(currentMode != API1Mode) {
                    qDebug() << "XBee radio is not in API mode without escape characters (AP=1). Try to set AP=1";
                    r = synchronousCmd(QByteArray("ATAP1").append(0x0d));
                    if(r == "OK") {
                        errorStr = "OK";
                    }
                    errorStr = "KO (Failed to set AP=1)";
                }
                else {
                    errorStr = "OK";
                }
            }
            else {
                errorStr = "KO (No response to AP command";
            }
        }
        else {
            errorStr = "KO (Failed to enter in command mode)";
        }
        exitCommandMode();
        // Check AP mode
//        at.setCommand("AP");
//        rep = sendATCommandSync(&at);
//        if(rep)
//        {
//            if(rep->commandStatus() == ATCommandResponse::Ok) {
//                bool ok = false;
//                currentMode = (Mode)rep->data().toHex().toInt(&ok,16);
//                if(ok) {
//                    if(currentMode != API1Mode) {
//                        qDebug() << Q_FUNC_INFO << "XBee radio is not in API mode without escape characters (AP=1). Try to set AP=1";
//                        at.clear();
//                        at.setCommand("AP");
//                        at.setParameter("1");
//                        at.assemblePacket();
//                        if(currentMode == 2) at.escapePacket();
//                        delete rep;
//                        rep = sendATCommandSync(&at);
//                        if(currentMode == 2) at.unescapePacket();
//                        if(rep) {
//                            if(rep->commandStatus() == ATCommandResponse::Ok) {
//                                errorStr = "OK";
//                                bRet = true;
//                                delete rep;
//                                rep = NULL;
//                            }
//                            else {
//                                errorStr = QString("KO (Failed to set AP=1, %1)").arg(rep->statusToString(rep->commandStatus()));
//                                qDebug() << Q_FUNC_INFO << "rep" << rep->packet().toHex();
//                            }
//                        }
//                        else {
//                            errorStr = "KO (No response to AP command)";
//                        }
//                    }
//                    else {
//                        errorStr = "OK";
//                        bRet = true;
//                    }
//                }
//                else {
//                    errorStr = "KO (Failed to get AP parameter)";
//                }
//            }
//            else {
//                errorStr = "KO (AP command failed)";
//            }
//        }
//        else
//        {
//            errorStr = "KO (No response to AP command)";
//        }
        qDebug() << "XBEE: Startup check :" << "XBee in API mode (AP=1) :" << qPrintable(errorStr);

        // Check HardWare Rev
        at.clear();
        at.setCommand("HV");
        rep = sendATCommandSync(&at);
        if(rep)
        {
            if(rep->status() == ATCommandResponse::Ok) {
                bool ok = false;
                int hv = rep->data().left(1).toHex().toInt(&ok,16);
                if(ok) {
                    if(hv == QtXBee::XBeeSerie1 || hv == QtXBee::XBeeSerie1Pro) {
                        errorStr = QString("OK (0x%1)").arg(QString(rep->data().toHex()));
                        bRet &= true;
                    }
                    else {
                        errorStr = QString("KO (Unsuported hardware version 0x%1)").arg(QString(rep->data().toHex()));
                        bRet = false;
                    }
                }
                else {
                    errorStr = "KO (Failed to retreive HV parameter from received response)";
                    bRet = false;
                }
            }
            else {
                errorStr = "KO (HV command failed)";
                bRet = false;
            }
        }
        else
        {
            errorStr = "KO (No response to HV command)";
            bRet = false;
        }

    }
    if(rep) {
        delete rep;
    }
    qDebug() << "XBEE: Startup check :" << "XBee Serie 1/1Pro       :" << qPrintable(errorStr);
    qDebug() << "*****************************************************************";
    return bRet;
}

QByteArray XBee::synchronousCmd(QByteArray cmd)
{
    QByteArray rep;
    m_serial->blockSignals(true);
    m_serial->write(cmd);
    m_serial->flush();
    while(m_serial->waitForReadyRead(10))
        rep.append(m_serial->readAll());

    m_serial->blockSignals(false);

    if(!rep.isEmpty()) {
    if(rep.at(rep.size()-1) == 0x0D)
        rep.remove(rep.size()-1, 1);
    }
    return rep;
}

bool XBee::enterInCommandMode()
{
    bool bRet = false;
    QByteArray rep;

    m_serial->blockSignals(true);
    m_serial->write("+++");
    m_serial->flush();
    while(m_serial->waitForReadyRead(2000))
        rep.append(m_serial->readAll());
    m_serial->blockSignals(false);
    if(rep == QByteArray("OK").append(0x0D)) {
        bRet = true;
        qDebug() << "XBee entering in command mode ...";
        QThread::sleep(2);
    }
    else {
        qWarning() << "XBee failed to enter in Command Mode (" << rep << ")";
    }
    return bRet;
}

bool XBee::exitCommandMode()
{
    QByteArray rep;
    rep = synchronousCmd(QByteArray("ATCN").append(0x0D));
    if(rep == "OK")
        qDebug() << "XBee exiting from command mode ...";
    else
        qDebug() << "XBee failed to exit from command mode";
    return rep == "OK";
}

} // END namepsace
