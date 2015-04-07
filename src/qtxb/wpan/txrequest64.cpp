#include "txrequest64.h"

namespace QtXBee {
namespace WPAN {


TXRequest64::TXRequest64(QObject *parent) : XBeePacket(parent)
{
    setFrameType(TXRequest64Id);
}

TXRequest64::~TXRequest64()
{

}

void TXRequest64::assemblePacket()
Q_DECL_OVERRIDE
{
    int i = 0;

    m_packet.clear();

    m_packet.append(frameType());
    m_packet.append(frameId());

    for(i=7; i>=0; i--) {
        m_packet.append(m_destinationAddress >> (i*8)&0xFF);
    }
    /** @todo Handle Options */
    m_packet.append(QByteArray::number(0));
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

void TXRequest64::clear()
Q_DECL_OVERRIDE
{
    m_packet.clear();
    m_data.clear();
    m_destinationAddress = 0xFFFFFFFF;
}

QString TXRequest64::toString()
Q_DECL_OVERRIDE
{
    return QString();
}

void TXRequest64::setDestinationAddress(const quint64 address)
{
    m_destinationAddress = address;
}

/**
  @brief Returns the packet's destination address.
 * @return the packet's destination address.
 */
quint64 TXRequest64::destinationAddress() const
{
    return m_destinationAddress;
}

/**
 * @brief Sets the data to be sent (Up to 100 bytes per packet)
 * @param data the data to be sent
 */
void TXRequest64::setData(const QByteArray &data)
{
    m_data = data;
}

/**
 * @brief Returns the data to be sent
 * @return the data to be sent
 */
QByteArray TXRequest64::data() const
{
    return m_data;
}


}} // END namespace
