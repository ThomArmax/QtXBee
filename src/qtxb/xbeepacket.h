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

#ifndef XBEEPACKET_H
#define XBEEPACKET_H

#include <QByteArray>
#include <QObject>

namespace QtXBee {

/**
 * @brief The XBeePacket class is the base class to implement XBee API frames (API Operations)
 *
 * As an alternative to Transparent Operation, API (Application Programming Interface) Operations are available.
 * API operation requires that communication with the module be done through a structured interface (data is communicated in frames in a defined order).
 * The API specifies how commands, command responses and module status messages are sent and received from the module using a UART Data Frame.
 * @todo Create the XBeeRequest class, based on XBeePacket to implement the request packet
 * specific part and remove them from XBeePacket (XBeePacket::assemblePacket(), ...)
 */
class XBeePacket : public QObject
{
    Q_OBJECT
public:

    enum ApiId {
        TxRequest64Id                   = 0x00, // 802.15.4
        TxRequest16Id                   = 0x01, // 802.15.4
        ATCommandId                     = 0x08, // 802.15.4, ZNet, ZigBee
        ATCommandQueueId                = 0x09, // 802.15.4, ZNet, ZigBee
        ZBTxRequestId                   = 0x10, // ZNet, ZigBee
        ZBExplicitTxRequestId           = 0x11, // ZNet, ZigBee
        RemoteATCommandRequestId        = 0x17, // 802.15.4, ZNet, ZigBee
        CreateSourceRouteId             = 0x21, // ZigBee
        ZBRegisterJoiningDeviceId       = 0x24, // ZigBee
        Rx64ResponseId                  = 0x80, // 802.15.4
        Rx16ResponseId                  = 0x81, // 802.15.4
        Rx64IOResponseId                = 0x82, // 802.15.4
        Rx16IOResponseId                = 0x83, // 802.15.4
        ATCommandResponseId             = 0x88, // 802.15.4, ZNet, ZigBee
        TxStatusResponseId              = 0x89, // 802.15.4
        ModemStatusResponseId           = 0x8A, // 802.15.4, ZNet, ZigBee
        ZBTxStatusResponseId            = 0x8B, // ZNet, ZigBee
        ZBRxResponseId                  = 0x90, // ZNet, ZigBee
        ZBExplicitRxResponseId          = 0x91, // ZNet, ZigBee
        ZBIOSampleResponseId            = 0x92, // ZNet, ZigBee
        XBeeSensorReadIndicatorId       = 0x94, // ZNet, ZigBee
        ZBIONodeIdentificationId        = 0x95, // ZNet, ZigBee
        RemoteATCommandResponseId       = 0x97, // 802.15.4, ZNet, ZigBee
        OverTheAirFirmwareUpdateId      = 0xA0, // ZigBee
        RouteRecordIndicatorId          = 0xA1, // ZigBee
        DeviceAuthenticatedIndicatorId  = 0xA2, // ZigBee
        ManyToOneRouteRequestId         = 0xA3, // ZigBee
        RegisterJoiningDeviceStatusId   = 0xA4, // ZigBee
        JoinNotificationStatusId        = 0xA5, // ZigBee
        UndefinedId                     = 0xFF /**< Undefined frame. Invalid value. */
    };

    /**
     * @brief The SpecialByte enum defines the special bytes
     */
    enum SpecialByte {
        StartDelimiter  = 0x7E, /**< Start delimiter */
        Escape          = 0x7D, /**< Escape caracter */
        XON             = 0x11, /**< XON */
        XOFF            = 0x13  /**< XOFF */
    };

    explicit        XBeePacket              (QObject *parent = 0);

    void            setStartDelimiter       (unsigned sd);
    void            setLength               (unsigned length);
    void            setFrameType            (ApiId type);
    void            setFrameId              (quint8 id);
    void            setChecksum             (unsigned cs);
    bool            setPacket               (const QByteArray & packet);

    QByteArray      packet                  () const;
    unsigned        startDelimiter          () const;
    quint16         length                  () const;
    ApiId           frameType               () const;
    quint8          frameId                 () const;
    unsigned        checksum                () const;

    virtual void    assemblePacket          ();
    virtual void    clear                   ();
    virtual QString toString                ();
    static QString  frameTypeToString       (const ApiId type);

    void            escapePacket            ();
    bool            unescapePacket          ();

private:
    bool            isSpecialByte           (const char c);

protected:
    virtual bool    parseApiSpecificData    (const QByteArray & data);
    void            createChecksum          (QByteArray array);

protected:
    QByteArray      m_packet;               /**< Contains the packet's data (sent or received)*/
private:
    unsigned        m_startDelimiter;       /**< The packet start delimiter */
    quint16         m_length;               /**< Frame-specific data length (Number of bytes between the length and the checksum) */
    ApiId           m_frameType;            /**< The frame's type */
    quint8          m_frameId;              /**< The frame's id */
    unsigned        m_checksum;             /**< Packet checksum */
};

} // END namepsace

#endif // XBEEPACKET_H
