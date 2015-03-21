#ifndef DIGIMESHPACKET_H
#define DIGIMESHPACKET_H

#include <QByteArray>
#include <QObject>

/**
 * @brief The DigiMeshPacket class is the base class to implement XBee packets
 */
class DigiMeshPacket : public QObject
{
    Q_OBJECT
public:
    enum APIFrameType {
        UndefinedFrame                      = 0x00, /**< Undefined frame. Invalid value. */
        ATCommandFrame                      = 0x08,
        ATCommandQueueFrame                 = 0x09,
        TXRequestFrame                      = 0x10,
        TXRequestExplicitFrame              = 0x11,
        RemoteCommandRequestFrame           = 0x17,
        CreateSourceRouteFrame              = 0x21,
        ATCommandResponseFrame              = 0x88,
        ModemStatusFrame                    = 0x8A,
        TransmitStatusFrame                 = 0x8B,
        RXIndicatorFrame                    = 0x90,
        RXIndicatorExplicitFrame            = 0x91,
        IODataSampleRXIndicatorFrame        = 0x92,
        SensorReadIndicatorFrame            = 0x94,
        NodeIdentificationIndicatorFrame    = 0x95,
        RemoteCommandResponseFrame          = 0x97,
        OverTheAirFirmwareUpdateFrame       = 0xA0,
        RouteRecordIndicatorFrame           = 0xA1,
        ManyToOneRouteRequestIndicator      = 0xA3
    };

    explicit DigiMeshPacket(QObject *parent = 0);

    void setStartDelimiter(unsigned sd);
    void setLength(unsigned l);
    void setFrameType(APIFrameType type);
    void setFrameId(unsigned id);
    void setChecksum(unsigned cs);

    QByteArray packet() const;
    unsigned startDelimiter() const;
    u_int16_t length() const;
    APIFrameType frameType() const;
    unsigned frameId() const;
    unsigned checksum() const;

    virtual void assemblePacket();
    virtual QString toString();
    static QString frameTypeToString(const APIFrameType type);

protected:
    void createChecksum(QByteArray array);

protected:
    QByteArray m_packet;
    unsigned m_startDelimiter;
    u_int16_t m_length;
    APIFrameType m_frameType;
    unsigned m_frameId;
    unsigned m_checksum;
};

/**
 * @enum DigiMeshPacket::APIFrameType
 * @brief The APIFrameType enum is used to identify the API frame type
 *
 * @var DigiMeshPacket::ATCommandFrame
 * Identifies a ATCommand<BR>
 * Used to query or set module parameters on the local device. This API command applies changes after executing the command.
 * (Changes made to module parameters take effect once changes are applied.)
 * The API example below illustrates an API frame when modifying the NJ parameter value of the module
 *
 * @var DigiMeshPacket::ATCommandQueueFrame
 * Identifies a ATCommandQueueParam<BR>
 * This API type allows module parameters to be queried or set. In contrast to the DigiMeshPacket::ATCommandFrame API type,
 * new parameter values are queued and not applied until either the DigiMeshPacket::ATCommandFrame (0x08) API type or the AC (Apply Changes) command is issued.
 * Register queries (reading parameter values) are returned immediately.
 *
 * @var DigiMeshPacket::TXRequestFrame
 * Identifies a TXRequest<BR>
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
 * @var DigiMeshPacket::TXRequestExplicitFrame
 * Identifies a TXRequestExplicit<BR>
 * Allows ZigBee application layer fields (endpoint and cluster ID) to be specified for a data transmission.
 * Similar to the DigiMeshPacket::TXRequestFrame, but also requires ZigBee application layer addressing fields to be specified
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
 * @var DigiMeshPacket::RemoteCommandRequestFrame
 * Identifies a ATCommandRemote<BR>
 * Used to query or set module parameters on a remote device. For parameter changes on the remote device to take effect,
 * changes must be applied, either by setting the apply changes options bit, or by sending an AC command to the remote.
 *
 * @var DigiMeshPacket::CreateSourceRouteFrame
 * This frame creates a source route in the module.
 * A source route specifies the complete route a packet should traverse to get from source to destination.
 * Source routing should be used with many-to-one routing for best results.
 * @note Both the 64-bit and 16-bit destination addresses are required when creating a source route.
 * These are obtained when a DigiMeshPacket::RouteRecordIndicatorFrame (0xA1) frame is received.
 *
 * @var DigiMeshPacket::ATCommandResponseFrame
 * Identifies a ATCommandResponse<BR>
 * In response to an DigiMeshPacket::ATCommandFrame message, the module will send an DigiMeshPacket::ATCommandResponseFrame.
 * Some commands will send back multiple frames (for example, the ND (Node Discover) command).
 *
 * @var DigiMeshPacket::ModemStatusFrame
 * Identifies a ModemStatus<BR>
 * RF module status messages are sent from the module in response to specific conditions.
 *
 * @var DigiMeshPacket::TransmitStatusFrame
 * Identifies a TransmitStatus<BR>
 * When a DigiMeshPacket::TXRequestFrame is completed, the module sends a TX Status message.
 * This message will indicate if the packet was transmitted successfully or if there was a failure.
 *
 * @var DigiMeshPacket::RXIndicatorFrame
 * Identifies a RXIndicator<BR>
 * When the module receives an RF packet, it is sent out the UART using this message type.
 *
 * @var DigiMeshPacket::RXIndicatorExplicitFrame
 * Identifies a RXIndicatorExplicit<BR>
 * When the modem receives a ZigBee RF packet it is sent out the UART using this message type (when AO=1).
 *
 * @var DigiMeshPacket::IODataSampleRXIndicatorFrame
 * When the module receives an IO sample frame from a remote device,
 * it sends the sample out the UART using this frame type (when AO=0).
 * Only modules running API firmware will send IO samples out the UART.
 *
 * @var DigiMeshPacket::SensorReadIndicatorFrame
 * When the module receives a sensor sample (from a Digi 1-wire sensor adapter), it is sent out the UART using this message type (when AO=0).
 *
 * @var DigiMeshPacket::NodeIdentificationIndicatorFrame
 * This frame is received when a module transmits a node identification message to identify itself (when AO=0).
 * The data portion of this frame is similar to a network discovery response frame (see ND command).
 *
 * @var DigiMeshPacket::RemoteCommandResponseFrame
 * Identifies a RemoteCommandResponse<BR>
 * If a module receives a remote command response RF data frame in response to a Remote AT Command Request,
 * the module will send a Remote AT Command Response message out the UART.
 * Some commands may send back multiple frames--for example, Node Discover (ND) command.
 *
 * @var DigiMeshPacket::OverTheAirFirmwareUpdateFrame
 * The Over-the-Air Firmware Update Status frame provides a status indication of a firmware update transmission attempt.
 * If a query command (0x01 0x51) is sent to a target with a 64-bit address of 0x0013A200 40522BAA through an
 * updater with 64-bit address 0x0013A200403E0750 and 16-bit address 0x0000, the following is the expected response.
 *
 * @var DigiMeshPacket::RouteRecordIndicatorFrame
 * The route record indicator is received whenever a device sends a ZigBee route record command.
 * This is used with many-to-one routing to create source routes for devices in a network.
 *
 * @var DigiMeshPacket::ManyToOneRouteRequestIndicator
 * The many-to-one route request indicator frame is sent out the UART whenever a many-to-one route request is received.
 **/

#endif // DIGIMESHPACKET_H
