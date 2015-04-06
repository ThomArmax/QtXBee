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
 *
 * Currently, there are 18 API frames types designed by Digi :
 *  - AT Command
 *  - AT Command - Queue Parameter value
 *  - ZigBee Transmit Request
 *  - Explicitit Adressing ZigBee Command Frame
 *  - Remote Command Request
 *  - Create Source Route
 *  - AT Command Response
 *  - Modem Status
 *  - ZigBee Transmit Status
 *  - ZigBee Receive Packet (AO=0)
 *  - ZigBee Explicit Rx Indicator (AO=1)
 *  - ZigBee IO Data Sample Rx Indicator
 *  - XBee Sensor Read Indicator (AO=0)
 *  - Node Identification Indicator (AO=0)
 *  - Remote Command Response
 *  - Over-the-Air Firmware Update Status
 *  - Route Record Indicator
 *  - Many-to-One Route Request Indicator
 *
 * @note Digi may add new API frames to future versions of firmware, so please build into your software interface the ability to
 * filter out additional API frames with unknown Frame Types.
 */
class XBeePacket : public QObject
{
    Q_OBJECT
public:

    enum ApiId {
        TXRequest64Id                   = 0x00,
        TXRequest16Id                   = 0x01,
        ATCommandId                     = 0x08,
        ATCommandQueueId                = 0x09,
        ZBTXRequestId                   = 0x10,
        ZBExplicitTxRequest             = 0x11,
        RemoteATCommandRequestId        = 0x17,
        CreateSourceRouteId             = 0x21,
        RX64ResponseId                  = 0x80,
        RX16ResponseId                  = 0x81,
        RX64IOResponseId                = 0x82,
        RX16IOResponseId                = 0x83,
        ATCommandResponseId             = 0x88,
        TXStatusResponseId              = 0x89,
        ModemStatusResponseId           = 0x8A,
        ZBTXStatusResponseId            = 0x8B,
        ZBRXResponseId                  = 0x90,
        ZBExplicitRxResponseId          = 0x91,
        ZBIOSampleResponseId            = 0x92,
        XBeeSensorReadIndicatorId       = 0x94,
        ZBIONodeIdentificationId        = 0x95,
        RemoteATCommandResponseId       = 0x97,
        OverTheAirFirmwareUpdateId      = 0xA0,
        RouteRecordIndicatorId          = 0xA1,
        ManyToOneRouteRequestId         = 0xA3,
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

    explicit XBeePacket(QObject *parent = 0);

    void setStartDelimiter(unsigned sd);
    void setLength(unsigned l);
    void setFrameType(ApiId type);
    void setFrameId(unsigned id);
    void setChecksum(unsigned cs);

    QByteArray packet() const;
    virtual bool setPacket(const QByteArray & packet);
    unsigned startDelimiter() const;
    quint16 length() const;
    ApiId frameType() const;
    unsigned frameId() const;
    unsigned checksum() const;

    virtual void assemblePacket();
    virtual void clear();
    virtual QString toString();
    static QString frameTypeToString(const ApiId type);

    void escapePacket();
    bool unescapePacket();

private:
    bool isSpecialByte(const char c);
protected:
    void createChecksum(QByteArray array);

protected:
    QByteArray m_packet;        /**< Contains the packet's data (sent or received)*/
    unsigned m_startDelimiter;  /**< The packet start delimiter */
    quint16 m_length;           /**< Frame-specific data length (Number of bytes between the length and the checksum) */
    ApiId m_frameType;          /**< The frame's type */
    unsigned m_frameId;         /**< The frame's id */
    unsigned m_checksum;        /**< Packet checksum */
};

} // END namepsace

#endif // XBEEPACKET_H

/**
 * @enum XBeePacket::ApiId
 * @brief The ApiId enum identifies sent/received frame's type
 *
 * @var XBeePacket::ATCommandFrame
 * Identifies an AT Command Frame (ATCommand)<BR>
 * Used to query or set module parameters on the local device. This API command applies changes after executing the command.
 * (Changes made to module parameters take effect once changes are applied.)
 * The API example below illustrates an API frame when modifying the NJ parameter value of the module
 *
 * @var XBeePacket::ATCommandQueueFrame
 * Identifies an AT Command - Queue Parameter Value Frame (ATCommandQueueParam)<BR>
 * This API type allows module parameters to be queried or set. In contrast to the XBeePacket::ATCommandFrame API type,
 * new parameter values are queued and not applied until either the XBeePacket::ATCommandFrame (0x08) API type or the AC (Apply Changes) command is issued.
 * Register queries (reading parameter values) are returned immediately.
 *
 * @var XBeePacket::TXRequestFrame
 * Identifies a ZigBee Transmit Request Frame (TransmitRequest)<BR>
 * A Transmit Request API frame causes the module to send data as an RF packet to the specified destination.
 * The 64-bit destination address should be set to 0x000000000000FFFF for a broadcast transmission (to all devices).
 * The coordinator can be addressed by either setting the 64-bit address to all 0x00s and the 16-bit address to 0xFFFE,
 * OR by setting the 64-bit address to the coordinator's 64-bit address and the 16-bit address to 0x0000.
 * For all other transmissions, setting the 16-bit address to the correct 16-bit address can help improve performance when transmitting to multiple destinations.
 * If a 16-bit address is not known, this field should be set to 0xFFFE (unknown).
 * The Transmit Status frame (0x8B) will indicate the discovered 16-bit address, if successful.
 * The broadcast radius can be set from 0 up to NH. If set to 0, the value of NH specifies the broadcast radius (recommended).
 * This parameter is only used for broadcast transmissions.
 * The maximum number of payload bytes can be read with the NP command.
 *
 * @var XBeePacket::ExplicitAddressingCommandFrame
 * Identifies an Explicit Addressing Command Frame (ExplicitAdressingCommandFrame)<BR>
 * Allows ZigBee application layer fields (endpoint and cluster ID) to be specified for a data transmission.
 * Similar to the XBeePacket::TXRequestFrame, but also requires ZigBee application layer addressing fields to be specified
 * (endpoints, cluster ID, profile ID). An Explicit Addressing Request API frame causes the module to send data as an RF
 * packet to the specified destination, using the specified source and destination endpoints, cluster ID, and profile ID.
 * The 64-bit destination address should be set to 0x000000000000FFFF for a broadcast transmission (to all devices).
 * The coordinator can be addressed by either setting the 64-bit address to all 0x00s and the 16-bit address to 0xFFFE,
 * OR by setting the 64-bit address to the coordinator's 64-bit address and the 16-bit address to 0x0000.
 * For all other transmissions, setting the 16-bit address to the correct 16-bit address can help improve performance when transmitting to multiple destinations.
 * If a 16-bit address is not known, this field should be set to 0xFFFE (unknown).
 * The Transmit Status frame (0x8B) will indicate the discovered 16-bit address, if successful.
 * The broadcast radius can be set from 0 up to NH. If set to 0, the value of NH specifies the broadcast radius (recommended).
 * This parameter is only used for broadcast transmissions.
 * The maximum number of payload bytes can be read with the NP command.
 * @note if source routing is used, the RF payload will be reduced by two bytes per intermediate hop in the source route.
 *
 * @var XBeePacket::RemoteATCommandRequestFrame
 * Identifies a Remote Command Request Frame (RemoteATCommandRequestFrame)<BR>
 * Used to query or set module parameters on a remote device. For parameter changes on the remote device to take effect,
 * changes must be applied, either by setting the apply changes options bit, or by sending an AC command to the remote.
 *
 * @var XBeePacket::CreateSourceRouteFrame
 * Identifies A Create Source Route Frame (CreateSourceRoute)
 * This frame creates a source route in the module.
 * A source route specifies the complete route a packet should traverse to get from source to destination.
 * Source routing should be used with many-to-one routing for best results.
 * @note Both the 64-bit and 16-bit destination addresses are required when creating a source route.
 * These are obtained when a XBeePacket::RouteRecordIndicatorFrame (0xA1) frame is received.
 *
 * @var XBeePacket::ATCommandResponseFrame
 * Identifies an AT Command Response Frame (ATCommandResponseFrame)<BR>
 * In response to an XBeePacket::ATCommandFrame message, the module will send an XBeePacket::ATCommandResponseFrame.
 * Some commands will send back multiple frames (for example, the ND (Node Discover) command).
 *
 * @var XBeePacket::ModemStatusFrame
 * Identifies a Modem Status Frame (ModemStatusFrame)<BR>
 * RF module status messages are sent from the module in response to specific conditions.
 *
 * @var XBeePacket::TransmitStatusFrame
 * Identifies a ZigBee Transmit Status (TransmitStatusFrame)<BR>
 * When a XBeePacket::TXRequestFrame is completed, the module sends a TX Status message.
 * This message will indicate if the packet was transmitted successfully or if there was a failure.
 *
 * @var XBeePacket::RXIndicatorFrame
 * Identifies a ZigBee Receive Packet Frame when AO=0 (ReceivePacketFrame)<BR>
 * When the module receives an RF packet, it is sent out the UART using this message type.
 *
 * @var XBeePacket::ExplicitRxIndicatorFrame
 * Identifies a ZigBee Explicit Rx Indicator when AO=1 (ExplicitRxIndicatorFrame)<BR>
 * When the modem receives a ZigBee RF packet it is sent out the UART using this message type (when AO=1).
 *
 * @var XBeePacket::IODataSampleRXIndicatorFrame
 * When the module receives an IO sample frame from a remote device,
 * it sends the sample out the UART using this frame type (when AO=0).
 * Only modules running API firmware will send IO samples out the UART.
 *
 * @var XBeePacket::SensorReadIndicatorFrame
 * When the module receives a sensor sample (from a Digi 1-wire sensor adapter), it is sent out the UART using this message type (when AO=0).
 *
 * @var XBeePacket::NodeIdentificationIndicatorFrame
 * Identifies a Node Identification Indicator Frame (NodeIdentificationIndicatorFrame)<BR>
 * This frame is received when a module transmits a node identification message to identify itself (when AO=0).
 * The data portion of this frame is similar to a network discovery response frame (see ND command).
 *
 * @var XBeePacket::RemoteATCommandResponseFrame
 * Identifies a Remote Command Response Frame (RemoteATCommandResponseFrame)<BR>
 * If a module receives a remote command response RF data frame in response to a Remote AT Command Request,
 * the module will send a Remote AT Command Response message out the UART.
 * Some commands may send back multiple frames--for example, Node Discover (ND) command.
 *
 * @var XBeePacket::OverTheAirFirmwareUpdateFrame
 * The Over-the-Air Firmware Update Status frame provides a status indication of a firmware update transmission attempt.
 * If a query command (0x01 0x51) is sent to a target with a 64-bit address of 0x0013A200 40522BAA through an
 * updater with 64-bit address 0x0013A200403E0750 and 16-bit address 0x0000, the following is the expected response.
 *
 * @var XBeePacket::RouteRecordIndicatorFrame
 * The route record indicator is received whenever a device sends a ZigBee route record command.
 * This is used with many-to-one routing to create source routes for devices in a network.
 *
 * @var XBeePacket::ManyToOneRouteRequestIndicator
 * The many-to-one route request indicator frame is sent out the UART whenever a many-to-one route request is received.
 **/
