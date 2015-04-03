#include "txrequest16.h"

namespace QtXBee {
namespace WPAN {

TXRequest16::TXRequest16(QObject *parent) :
    XBeePacket(parent),
    m_destinationAddress(0xFFFF)
{
    setFrameType(TXRequest16Id);
}

TXRequest16::~TXRequest16()
{

}

void TXRequest16::assemblePacket()
Q_DECL_OVERRIDE
{
    m_packet.clear();

    m_packet.append(frameType());
    m_packet.append(frameId());

    for(i=1; i>=0; i--) {
        m_packet.append(m_destinationAddress >> (i*8)&0xFF);
    }
    /** @todo Handle Options */
    m_packet.append(0);
    /** @todo Check data's size (up to 100 bytes per packet) */
    for(int i=0; i<m_data.size(); i++) {
        m_packet.append(m_data.at(i));
    }

    setLength(m_packet.size());
    createChecksum(m_packet);

    m_packet.append(checksum());
    m_packet.insert(0, startDelimiter());
    m_packet.insert(1, (length()>>8)&0xFF);
    m_packet.insert(2, length()&0xFF);
}

/**
 * @brief Sets the 16 bits packet's destination address
 * @note To send the packet on the broadcast set the address to 0xFFFF
 * @param address the destination address
 */
void TXRequest16::setDestinationAddress(const quint16 address)
{
    m_destinationAddress = address;
}

/**
  @brief Returns the packet's destination address.
 * @return the packet's destination address.
 */
quint16 TXRequest16::destinationAddress() const
{
    return m_destinationAddress;
}

/**
 * @brief Sets the data to be sent (Up to 100 bytes per packet)
 * @param data the data to be sent
 */
void TXRequest16::setData(const QByteArray &data)
{
    m_data = data;
}

/**
 * @brief Returns the data to be sent
 * @return the data to be sent
 */
QByteArray TXRequest16::data() const
{
    return m_data;
}

}} // END namespace
