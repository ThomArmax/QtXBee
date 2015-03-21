#ifndef TXREQUEST_H
#define TXREQUEST_H

#include "digimeshpacket.h"


#include <QByteArray>

/**
 * @brief The TXRequest class causes the module to send data as an RF packet to the specified destination.
 *
 * The 64-bit destination address should be set to 0x000000000000FFFF for a broadcast transmission (to all devices).
 * The coordinator can be addressed by either setting the 64-bit address to all 0x00s and the 16-bit address to 0xFFFE,
 * OR by setting the 64-bit address to the coordinator's 64-bit address and the 16-bit address to 0x0000.
 * For all other transmissions, setting the 16-bit address to the correct 16-bit address can help improve performance
 * when transmitting to multiple destinations. If a 16-bit address is not known, this field should be set to 0xFFFE (unknown).
 * The Transmit Status frame (0x8B) will indicate the discovered 16-bit address, if successful.
 * The broadcast radius can be set from 0 up to NH. If set to 0, the value of NH specifies the broadcast radius (recommended).
 * This parameter is only used for broadcast transmissions.
 * The maximum number of payload bytes can be read with the NP command.
 * @note if source routing is used, the RF payload will be reduced by two bytes per intermediate hop in the source route.
 *
 * @sa TransmitStatus
 */
class TXRequest : public DigiMeshPacket
{
    Q_OBJECT
public:
    explicit TXRequest(QObject *parent = 0);
    void setBroadcastRadius(int rad);
    void setTransmitOptions(unsigned to);
    void setDestAddr64(QByteArray da64);
    void setDestAddr16(QByteArray da16);
    void setData(QByteArray d);
    QByteArray destAddr64() const;
    QByteArray destAddr16() const;
    unsigned broadcastRadius() const;
    unsigned transmitOptions() const;
    QByteArray getData() const;
    void assemblePacket();

private:
    QByteArray m_destAddr64;
    QByteArray m_destAddr16;
    unsigned m_broadcastRadius;
    unsigned m_transmitOptions;
    QByteArray m_data;
};

#endif // TXREQUEST_H
