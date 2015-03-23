#ifndef XBEE_H
#define XBEE_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class DigiMeshPacket;
class ATCommandResponse;
class ModemStatus;
class TransmitStatus;
class RXIndicator;
class RXIndicatorExplicit;
class NodeIdentificationIndicator;
class RemoteCommandResponse;

class XBee : public QObject
{
    Q_OBJECT
public:
    explicit XBee(QObject *parent = 0);
    XBee(const QString & serialPort, QObject * parent = 0);
    ~XBee();

    bool applyDefaultSerialPortConfig();
    void broadcast(QString data);
    void unicast(QByteArray address, QString data);
    void send(DigiMeshPacket *request);

    bool setSerialPort(const QString & serialPort);
    bool setSerialPort(
            const QString &serialPort,
            const QSerialPort::BaudRate baudRate,
            const QSerialPort::DataBits dataBits,
            const QSerialPort::Parity parity,
            const QSerialPort::StopBits stopBits,
            const QSerialPort::FlowControl flowControl);
    bool setSerialPortConfiguration(
            const QSerialPort::BaudRate baudRate,
            const QSerialPort::DataBits dataBits,
            const QSerialPort::Parity parity,
            const QSerialPort::StopBits stopBits,
            const QSerialPort::FlowControl flowControl);

    // Adressing
    bool setDH(const quint32 dh);
    bool setDL(const quint32 dl);
    bool setMY(const quint16 my);
    bool setMP(const quint16 mp);
    bool setNC(const quint32 nc);
    bool setSH(const quint32 sh);
    bool setSL(const quint32 sl);
    bool setNI(const QString & ni);
    bool setSE(const quint8 se);
    bool setDE(const quint8 de);
    bool setCI(const quint8 ci);
    bool setTO(const quint8 to);
    bool setNP(const quint8 np);
    bool setDD(const quint16 dd);
    bool setCR(const quint8 cr);
    quint32 DH() const { return m_dh;}
    quint32 DL() const { return m_dl;}
    quint16 MY() const { return m_my;}
    quint16 MP() const { return m_mp;}
    quint32 NC() const { return m_nc;}
    quint32 SH() const { return m_sh;}
    quint32 SL() const { return m_sl;}
    QString NI() const { return m_ni;}
    quint8 SE() const { return m_se;}
    quint8 DE() const { return m_de;}
    quint8 CI() const { return m_ci;}
    quint8 TO() const { return m_to;}
    quint8 NO() const { return m_np;}
    quint16 DD() const { return m_dd;}
    quint8 CR() const { return m_cr;}
signals:
    void DHChanged(const quint32 dh);
    void DLChanged(const quint32 dh);
    void MYChanged(const quint16 my);
    void MPChanged(const quint16 mp);
    void NCChanged(const quint32 nc);
    void SHChanged(const quint32 sh);
    void SLChanged(const quint32 sl);
    void NIChanged(const QString & ni);
    void SEChanged(const quint8 se);
    void DEChanged(const quint8 de);
    void CIChanged(const quint8 ci);
    void TOChanged(const quint8 to);
    void NPChanged(const quint8 np);
    void DDChanged(const quint16 dd);
    void CRChanged(const quint8 cr);

signals:
    void receivedATCommandResponse(ATCommandResponse *response);
    void receivedModemStatus(ModemStatus *response);
    void receivedTransmitStatus(TransmitStatus *response);
    void receivedRXIndicator(RXIndicator *response);
    void receivedRXIndicatorExplicit(RXIndicatorExplicit *response);
    void receivedNodeIdentificationIndicator(NodeIdentificationIndicator *response);
    void receivedRemoteCommandResponse(RemoteCommandResponse *response);

public slots:
    void loadAddressingProperties();
    bool open();
    bool close();

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
    void processATCommandRespone(ATCommandResponse *rep);

private:
    QSerialPort *serial;
    bool xbeeFound;
    QByteArray buffer;

    // Adressing
    quint32 m_dh;
    quint32 m_dl;
    quint16 m_my;
    quint16 m_mp;
    quint32 m_nc;
    quint32 m_sh;
    quint32 m_sl;
    QString m_ni;
    quint8 m_se;
    quint8 m_de;
    quint8 m_ci;
    quint8 m_to;
    quint8 m_np;
    quint16 m_dd;
    quint8 m_cr;
};

#endif
