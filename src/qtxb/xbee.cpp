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
#include <QSerialPort>
#include <QSerialPortInfo>

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
    m_mode(NormalMode),
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
 */
XBee::XBee(const QString &serialPort, QObject *parent) :
    QObject(parent),
    m_serial(NULL),
    xbeeFound(false),
    m_mode(NormalMode),
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
    initSerialConnection();
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
    bool bRet = false;
    if(m_serial) {
        bRet = m_serial->open(QIODevice::ReadWrite);
    }
    return bRet;
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
    return true;
}

/**
 * @brief Sets the XBee's serial port, which we be used to communicate with it.
 * @note Default serial port will be used :
 * <ul>
 * <li><b>Baud Rate</b> : 9600</li>
 * <li><b>Data Bits</b> : 8 bits</li>
 * <li><b>Parity</b> : No</li>
 * <li><b>Stop Bits</b> : One stop bit</li>
 * <li><b>Flow Control</b> : No flow control</li>
 * </ul>
 * @param serialPort path to the serial port
 * @return true if succeeded; false otherwise
 * @sa XBee::setSerialPort(const QString &serialPort, const QSerialPort::BaudRate baudRate, const QSerialPort::DataBits dataBits, const QSerialPort::Parity parity, const QSerialPort::StopBits stopBits, const QSerialPort::FlowControl flowControl)
 * @sa XBee::applyDefaultSerialPortConfig()
 */
bool XBee::setSerialPort(const QString &serialPort)
{
    if(m_serial) {
        m_serial->close();
        m_serial->setPortName(serialPort);
        m_serial->disconnect(this);
    }
    else {
        m_serial = new QSerialPort(serialPort, this);
        connect(m_serial, SIGNAL(readyRead()), SLOT(readData()));
    }
    applyDefaultSerialPortConfig();
    return initSerialConnection();
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
    if(m_serial == NULL)
        return false;

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
    if(m_serial == NULL)
        return false;

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
    if(xbeeFound && m_serial->isOpen())
    {
        qDebug() << Q_FUNC_INFO << "Transmit: " << QString("0x").append(request->packet().toHex());
        m_serial->write(request->packet());
        m_serial->flush();
    }
    else
    {
        qDebug() << "XBEE: Cannot write to Serial Port" << m_serial->portName();
    }
}

void XBee::broadcast(QString data)
{
    TXRequest request;
    request.setData(data.toLatin1());
    send(&request);
}

void XBee::unicast(QByteArray address, QString data)
{
    TXRequest request;
    request.setDestAddr64(address);
    request.setData(data.toLatin1());
    send(&request);
}

/**
 * @brief Loads the XBee's addressing properties
 * <ul>
 * <li>DH</li>
 * <li>DL</li>
 * <li>MY</li>
 * <li>MP</li>
 * <li>NC</li>
 * <li>SH</li>
 * <li>SL</li>
 * <li>NI</li>
 * <li>SE</li>
 * <li>DE</li>
 * <li>CI</li>
 * <li>TO</li>
 * <li>NP</li>
 * <li>DD</li>
 * <li>CR</li>
 * </ul>
 */
void XBee::loadAddressingProperties() {
    ATCommand at;
    at.setCommand(ATCommand::Command_DH); send(&at);
    at.setCommand(ATCommand::Command_DL); send(&at);
    at.setCommand(ATCommand::Command_MY); send(&at);
    at.setCommand(ATCommand::Command_MP); send(&at);
    at.setCommand(ATCommand::Command_NC); send(&at);
    at.setCommand(ATCommand::Command_SH); send(&at);
    at.setCommand(ATCommand::Command_SL); send(&at);
    at.setCommand(ATCommand::Command_NI); send(&at);
    at.setCommand(ATCommand::Command_SE); send(&at);
    at.setCommand(ATCommand::Command_DE); send(&at);
    at.setCommand(ATCommand::Command_CI); send(&at);
    at.setCommand(ATCommand::Command_TO); send(&at);
    at.setCommand(ATCommand::Command_NP); send(&at);
    at.setCommand(ATCommand::Command_DD); send(&at);
    at.setCommand(ATCommand::Command_CR); send(&at);
}

// Adressing
bool XBee::setDH(const quint32 dh) {
    ATCommand at;
    at.setCommand(ATCommand::Command_DH);
    at.setParameter(QByteArray::number(dh));
    send(&at);
    return true;
}

bool XBee::setDL(const quint32 dl) {
    ATCommand at;
    at.setCommand(ATCommand::Command_DL);
    at.setParameter(QByteArray::number(dl));
    send(&at);
    return true;
}

bool XBee::setMY(const quint16 my) {
    ATCommand at;
    at.setCommand(ATCommand::Command_MY);
    at.setParameter(QByteArray::number(my));
    send(&at);
    return true;
}

bool XBee::setMP(const quint16 mp) {
    ATCommand at;
    at.setCommand(ATCommand::Command_MP);
    at.setParameter(QByteArray::number(mp));
    send(&at);
    return true;
}

bool XBee::setNC(const quint32 nc) {
    ATCommand at;
    at.setCommand(ATCommand::Command_NC);
    at.setParameter(QByteArray::number(nc));
    send(&at);
    return true;
}

bool XBee::setSH(const quint32 sh) {
    ATCommand at;
    at.setCommand(ATCommand::Command_SH);
    at.setParameter(QByteArray::number(sh));
    send(&at);
    return true;
}

bool XBee::setSL(const quint32 sl) {
    ATCommand at;
    at.setCommand(ATCommand::Command_SL);
    at.setParameter(QByteArray::number(sl));
    send(&at);
    return true;
}

bool XBee::setNI(const QString & ni) {
    ATCommand at;
    at.setCommand(ATCommand::Command_NI);
    at.setParameter(ni.toUtf8());
    send(&at);
    return true;
}

bool XBee::setSE(const quint8 se) {
    ATCommand at;
    at.setCommand(ATCommand::Command_SE);
    at.setParameter(QByteArray::number(se));
    send(&at);
    return true;
}

bool XBee::setDE(const quint8 de) {
    ATCommand at;
    at.setCommand(ATCommand::Command_DE);
    at.setParameter(QByteArray::number(de));
    send(&at);
    return true;
}

bool XBee::setCI(const quint8 ci) {
    ATCommand at;
    at.setCommand(ATCommand::Command_CI);
    at.setParameter(QByteArray::number(ci));
    send(&at);
    return true;
}

bool XBee::setTO(const quint8 to) {
    ATCommand at;
    at.setCommand(ATCommand::Command_TO);
    at.setParameter(QByteArray::number(to));
    send(&at);
    return true;
}

bool XBee::setNP(const quint8 np) {
    ATCommand at;
    at.setCommand(ATCommand::Command_NP);
    at.setParameter(QByteArray::number(np));
    send(&at);
    return true;
}

bool XBee::setDD(const quint16 dd) {
    ATCommand at;
    at.setCommand(ATCommand::Command_DD);
    at.setParameter(QByteArray::number(dd));
    send(&at);
    return true;
}

bool XBee::setCR(const quint8 cr) {
    ATCommand at;
    at.setCommand(ATCommand::Command_CR);
    at.setParameter(QByteArray::number(cr));
    send(&at);
    return true;
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

    qDebug() << Q_FUNC_INFO << buffer;

    if(m_mode == NormalMode) {
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
            if((unsigned char)buffer.size() >= (unsigned char)length){
                packet.append(buffer.left(length));
                qDebug() << Q_FUNC_INFO << QString("0x").append(packet.toHex());
                processPacket(packet);
                buffer.remove(0, length);
            }
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
        processATCommandRespone(response);
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
        qDebug() << Q_FUNC_INFO << qPrintable(QString("Error: Unknown or Unhandled Packet (type=%1): 0x%2").
                                              arg(packetType,0,16).
                                              arg(QString(packet.toHex())));
    }
}

void XBee::processATCommandRespone(ATCommandResponse *rep) {
    Q_ASSERT(rep);
    ATCommand::ATCommandType at = rep->atCommand();
    QByteArray data = rep->data().toHex();
    quint32 dataInt = QString(data).toInt(0, 16);

    qDebug() << Q_FUNC_INFO << "AT command" << ATCommand::atCommandToString(at) << QString("0x%1").arg(at , 0, 16) << " : " << data << dataInt;

    switch(at) {
    // Addressing
    case ATCommand::Command_DH : m_dh = dataInt; emit DHChanged(m_dh); break;
    case ATCommand::Command_DL : m_dl = dataInt; emit DLChanged(m_dl); break;
    case ATCommand::Command_MY : m_my = dataInt; emit MYChanged(m_my); break;
    case ATCommand::Command_MP : m_mp = dataInt; emit MPChanged(m_mp); break;
    case ATCommand::Command_NC : m_nc = dataInt; emit NCChanged(m_nc); break;
    case ATCommand::Command_SH : m_sh = dataInt; emit SHChanged(m_sh); break;
    case ATCommand::Command_SL : m_sl = dataInt; emit SLChanged(m_sl); break;
    case ATCommand::Command_NI : m_ni = data; emit NIChanged(m_ni); break;
    case ATCommand::Command_SE : m_se = dataInt; emit SEChanged(m_se); break;
    case ATCommand::Command_DE : m_de = dataInt; emit DEChanged(m_de); break;
    case ATCommand::Command_CI : m_ci = dataInt; emit CIChanged(m_ci); break;
    case ATCommand::Command_TO : m_to = dataInt; emit TOChanged(m_to); break;
    case ATCommand::Command_NP : m_np = dataInt; emit NPChanged(m_np); break;
    case ATCommand::Command_DD : m_dd = dataInt; emit DDChanged(m_dd); break;
    case ATCommand::Command_CR : m_cr = dataInt; emit CRChanged(m_cr); break;
    default:
        qWarning() << Q_FUNC_INFO << "Unhandled AT command" <<  QString("0x%1 (%2)").arg(at , 0, 16).arg(ATCommand::atCommandToString(at));
    }
    emit receivedATCommandResponse(rep);
}

bool XBee::initSerialConnection()
{
    if(!m_serial)
        return false;

    if (m_serial->open(QIODevice::ReadWrite))
    {
        if(applyDefaultSerialPortConfig())
        {
            if(m_serial->isOpen())
            {
                qDebug() << "XBEE: Connected successfully";
                qDebug() << "XBEE: Serial Port Name: " << m_serial->portName();
                xbeeFound = true;
                return true;
            }
        }
    }
    else
    {
        qDebug() << "XBEE: Serial Port" << m_serial->portName() << "could not be opened";
    }

    return false;
}
