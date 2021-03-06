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

#ifndef XBEE_H
#define XBEE_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace QtXBee {
class XBeePacket;
class XBeeResponse;
class ATCommandResponse;
class ATCommand;
class ModemStatus;
class RemoteATCommandResponse;

namespace Wpan {
class RxResponse64;
class RxResponse16;
class TxStatusResponse;
}

namespace ZigBee {
class ZBTxStatusResponse;
class ZBRxResponse;
class ZBExplicitRxResponse;
class ZBIONodeIdentificationResponse;
}

using namespace QtXBee::Wpan;
using namespace QtXBee::ZigBee;

class XBee : public QObject
{
    Q_OBJECT
public:
    enum Mode {
        CommandMode,
        API1Mode,
        API2Mode
    };

    explicit            XBee                                (QObject *parent = 0);
                        XBee                                (const QString & serialPort, QObject * parent = 0);
                        ~XBee                               ();

    bool                applyDefaultSerialPortConfig        ();

    bool                sendCommandAsync                    (const QByteArray & command);
    XBeeResponse *      sendSync                            (XBeePacket * packet);
    ATCommandResponse * sendATCommandSync                   (ATCommand * command);
    ATCommandResponse * sendATCommandSync                   (const QByteArray & atcommand);

    QByteArray          sendCommandSync                     (const QByteArray & command);
    void                sendAsync                           (XBeePacket * packet);
    void                sendATCommandAsync                  (ATCommand *command);
    void                sendATCommandAsync                  (const QByteArray & data);

    bool                setMode                             (const Mode mode);
    Mode                mode                                () const;

    bool                setSerialPort                       (const QString & serialPort);
    bool                setSerialPort                       (const QString &serialPort,
                                                             const QSerialPort::BaudRate baudRate,
                                                             const QSerialPort::DataBits dataBits,
                                                             const QSerialPort::Parity parity,
                                                             const QSerialPort::StopBits stopBits,
                                                             const QSerialPort::FlowControl flowControl);
    bool                setSerialPortConfiguration          (const QSerialPort::BaudRate baudRate,
                                                             const QSerialPort::DataBits dataBits,
                                                             const QSerialPort::Parity parity,
                                                             const QSerialPort::StopBits stopBits,
                                                             const QSerialPort::FlowControl flowControl);

    // Adressing
    bool                setDH                               (const quint32 dh);
    bool                setDL                               (const quint32 dl);
    bool                setMY                               (const quint16 my);
    bool                setMP                               (const quint16 mp);
    bool                setNC                               (const quint32 nc);
    bool                setSH                               (const quint32 sh);
    bool                setSL                               (const quint32 sl);
    bool                setNI                               (const QString & ni);
    bool                setSE                               (const quint8 se);
    bool                setDE                               (const quint8 de);
    bool                setCI                               (const quint8 ci);
    bool                setTO                               (const quint8 to);
    bool                setNP                               (const quint8 np);
    bool                setDD                               (const quint16 dd);
    bool                setCR                               (const quint8 cr);

    quint32             DH                                  () const { return m_dh;}
    quint32             DL                                  () const { return m_dl;}
    quint16             MY                                  () const { return m_my;}
    quint16             MP                                  () const { return m_mp;}
    quint32             NC                                  () const { return m_nc;}
    quint32             SH                                  () const { return m_sh;}
    quint32             SL                                  () const { return m_sl;}
    QString             NI                                  () const { return m_ni;}
    quint8              SE                                  () const { return m_se;}
    quint8              DE                                  () const { return m_de;}
    quint8              CI                                  () const { return m_ci;}
    quint8              TO                                  () const { return m_to;}
    quint8              NO                                  () const { return m_np;}
    quint16             DD                                  () const { return m_dd;}
    quint8              CR                                  () const {return m_cr;}

signals:
    void                rawDataReceived                     (const QByteArray & data);
    void                receivedATCommandResponse           (QtXBee::ATCommandResponse *response);
    void                receivedModemStatus                 (QtXBee::ModemStatus *response);
    void                receivedRemoteCommandResponse       (QtXBee::RemoteATCommandResponse *response);
    void                receivedTransmitStatus              (QtXBee::ZigBee::ZBTxStatusResponse *response);
    void                receivedRxIndicator                 (QtXBee::ZigBee::ZBRxResponse *response);
    void                receivedRxIndicatorExplicit         (QtXBee::ZigBee::ZBExplicitRxResponse *response);
    void                receivedNodeIdentificationIndicator (QtXBee::ZigBee::ZBIONodeIdentificationResponse *response);
    void                receivedTransmitStatus              (QtXBee::Wpan::TxStatusResponse *response);
    void                receivedRxResponse16                (QtXBee::Wpan::RxResponse16 * response);
    void                receivedRxResponse64                (QtXBee::Wpan::RxResponse64 * response);
    // Addressing signals
    void                DHChanged                           (const quint32 dh);                                 /**< @brief Emitted when DH property changes. @sa XBee::setDH() @sa XBee::DH()*/
    void                DLChanged                           (const quint32 dl);                                 /**< @brief Emitted when DL property changes. @sa XBee::setDL() @sa XBee::DL()*/
    void                MYChanged                           (const quint16 my);                                 /**< @brief Emitted when MY property changes. @sa XBee::setMY() @sa XBee::MY()*/
    void                MPChanged                           (const quint16 mp);                                 /**< @brief Emitted when MP property changes. @sa XBee::setMP() @sa XBee::MP()*/
    void                NCChanged                           (const quint32 nc);                                 /**< @brief Emitted when NC property changes. @sa XBee::setNC() @sa XBee::NC()*/
    void                SHChanged                           (const quint32 sh);                                 /**< @brief Emitted when SH property changes. @sa XBee::setSH() @sa XBee::SH()*/
    void                SLChanged                           (const quint32 sl);                                 /**< @brief Emitted when SL property changes. @sa XBee::setSL() @sa XBee::SL()*/
    void                NIChanged                           (const QString & ni);                               /**< @brief Emitted when NI property changes. @sa XBee::setNI() @sa XBee::NI()*/
    void                SEChanged                           (const quint8 se);                                  /**< @brief Emitted when SE property changes. @sa XBee::setSE() @sa XBee::SE()*/
    void                DEChanged                           (const quint8 de);                                  /**< @brief Emitted when DE property changes. @sa XBee::setDE() @sa XBee::DE()*/
    void                CIChanged                           (const quint8 ci);                                  /**< @brief Emitted when CI property changes. @sa XBee::setCI() @sa XBee::CI()*/
    void                TOChanged                           (const quint8 to);                                  /**< @brief Emitted when TO property changes. @sa XBee::setTO() @sa XBee::TO()*/
    void                NPChanged                           (const quint8 np);                                  /**< @brief Emitted when NP property changes. @sa XBee::setNP() @sa XBee::NP()*/
    void                DDChanged                           (const quint16 dd);                                 /**< @brief Emitted when DD property changes. @sa XBee::setDD() @sa XBee::DD()*/
    void                CRChanged                           (const quint8 cr);                                  /**< @brief Emitted when CR property changes. @sa XBee::setCR() @sa XBee::CR()*/

public slots:
    void                loadAddressingProperties();
    bool                open();
    bool                close();

    void                displayATCommandResponse            (ATCommandResponse *digiMeshPacket);
    void                displayModemStatus                  (ModemStatus *digiMeshPacket);
    void                displayTransmitStatus               (ZBTxStatusResponse *digiMeshPacket);
    void                displayRxIndicator                  (ZBRxResponse *digiMeshPacket);
    void                displayRxIndicatorExplicit          (ZBExplicitRxResponse *digiMeshPacket);
    void                displayNodeIdentificationIndicator  (ZBIONodeIdentificationResponse *digiMeshPacket);
    void                displayRemoteCommandResponse        (RemoteATCommandResponse *digiMeshPacket);

private slots:
    void                readData                            ();

private:
    XBeeResponse *      processPacket                       (QByteArray packet, const bool async);
    void                processATCommandRespone             (ATCommandResponse *rep);
    bool                startupCheck                        ();
    QByteArray          synchronousCmd                      (QByteArray cmd);
    bool                enterInCommandMode                  ();
    bool                exitCommandMode                     ();

private:
    QSerialPort *       m_serial;
    bool                xbeeFound;
    Mode                m_mode;
    QByteArray          buffer;
    quint16             m_frameIdCounter;

    // Adressing
    quint32             m_dh;
    quint32             m_dl;
    quint16             m_my;
    quint16             m_mp;
    quint32             m_nc;
    quint32             m_sh;
    quint32             m_sl;
    QString             m_ni;
    quint8              m_se;
    quint8              m_de;
    quint8              m_ci;
    quint8              m_to;
    quint8              m_np;
    quint16             m_dd;
    quint8              m_cr;
};

} //END namespace

#endif
