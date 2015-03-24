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

/**
 * @brief The XBee class is used to represents the local XBee.
 *
 * You can :
 * <ul>
 * <li>Open/Close and configure the serial interface</li>
 * <li>Get/Set all XBee's parameters</li>
 * <li>Send/Receive packets to/from other remote XBees</li>
 * </ul>
 * @todo What to do when the XBee is in XBee::NormalMode at the user wants to send API packets ?
 * Auto switch to the correct mode ? Stay in XBee::NormalMode and do nothing but warn the user ?
 */
class XBee : public QObject
{
    Q_OBJECT
public:
    explicit XBee(QObject *parent = 0);
    XBee(const QString & serialPort, QObject * parent = 0);
    ~XBee();

    /**
     * @brief The Mode enum defines the mode the XBee is.
     * @note The mode affects the way the data read on serial port are handled
     */
    enum Mode {
        NormalMode, /**< Standard mode */
        API1Mode,   /**< API 1 mode */
        API2Mode    /**< API 2 mode */
    };

    bool applyDefaultSerialPortConfig();
    void broadcast(QString data);
    void unicast(QByteArray address, QString data);
    void send(DigiMeshPacket *request);

    bool setMode(const Mode mode) { m_mode = mode; return true; }   /**< @brief Sets the XBee's mode @param mode the new Mode to be applied */
    Mode mode() const { return m_mode; }                            /**< @brief Returns the XBee's mode @return the XBee's mode */

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

    QSerialPort * serialPort() { return m_serial; } /**< @brief Returns the QSerialPort used to communicate with the XBee. @return the QSerialPort used to communicate with the XBee */

signals:
    void receivedATCommandResponse(ATCommandResponse *response);                        /**< @brief Emitted when at ATCommandResponse frame is received*/
    void receivedModemStatus(ModemStatus *response);                                    /**< @brief Emitted when at ModemStatus frame is received*/
    void receivedTransmitStatus(TransmitStatus *response);                              /**< @brief Emitted when at TransmitStatus frame is received*/
    void receivedRXIndicator(RXIndicator *response);                                    /**< @brief Emitted when at RXIndicator frame is received*/
    void receivedRXIndicatorExplicit(RXIndicatorExplicit *response);                    /**< @brief Emitted when at RXIndicatorExplicit frame is received*/
    void receivedNodeIdentificationIndicator(NodeIdentificationIndicator *response);    /**< @brief Emitted when at NodeIdentificationIndicator frame is received*/
    void receivedRemoteCommandResponse(RemoteCommandResponse *response);                /**< @brief Emitted when at RemoteCommandResponse frame is received*/
    void rawDataReceived(const QByteArray & data);                                      /**< @brief Emitted when raw data are received on the serial port (only in NormalMode). @sa XBee::setMode() @sa XBee::Mode */
    // Addressing signals
    void DHChanged(const quint32 dh);   /**< @brief Emitted when DH property changes. @sa XBee::setDH() @sa XBee::DH()*/
    void DLChanged(const quint32 dl);   /**< @brief Emitted when DL property changes. @sa XBee::setDL() @sa XBee::DL()*/
    void MYChanged(const quint16 my);   /**< @brief Emitted when MY property changes. @sa XBee::setMY() @sa XBee::MY()*/
    void MPChanged(const quint16 mp);   /**< @brief Emitted when MP property changes. @sa XBee::setMP() @sa XBee::MP()*/
    void NCChanged(const quint32 nc);   /**< @brief Emitted when NC property changes. @sa XBee::setNC() @sa XBee::NC()*/
    void SHChanged(const quint32 sh);   /**< @brief Emitted when SH property changes. @sa XBee::setSH() @sa XBee::SH()*/
    void SLChanged(const quint32 sl);   /**< @brief Emitted when SL property changes. @sa XBee::setSL() @sa XBee::SL()*/
    void NIChanged(const QString & ni); /**< @brief Emitted when NI property changes. @sa XBee::setNI() @sa XBee::NI()*/
    void SEChanged(const quint8 se);    /**< @brief Emitted when SE property changes. @sa XBee::setSE() @sa XBee::SE()*/
    void DEChanged(const quint8 de);    /**< @brief Emitted when DE property changes. @sa XBee::setDE() @sa XBee::DE()*/
    void CIChanged(const quint8 ci);    /**< @brief Emitted when CI property changes. @sa XBee::setCI() @sa XBee::CI()*/
    void TOChanged(const quint8 to);    /**< @brief Emitted when TO property changes. @sa XBee::setTO() @sa XBee::TO()*/
    void NPChanged(const quint8 np);    /**< @brief Emitted when NP property changes. @sa XBee::setNP() @sa XBee::NP()*/
    void DDChanged(const quint16 dd);   /**< @brief Emitted when DD property changes. @sa XBee::setDD() @sa XBee::DD()*/
    void CRChanged(const quint8 cr);    /**< @brief Emitted when CR property changes. @sa XBee::setCR() @sa XBee::CR()*/


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
    QSerialPort *m_serial;
    bool xbeeFound;
    Mode m_mode;
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
