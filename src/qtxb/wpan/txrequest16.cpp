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

#include "txrequest16.h"

namespace QtXBee {
namespace Wpan {

TxRequest16::TxRequest16(QObject *parent) :
    XBeePacket(parent),
    m_destinationAddress(0xFFFF)
{
    setFrameType(TxRequest16Id);
}

TxRequest16::~TxRequest16()
{

}

void TxRequest16::assemblePacket()
Q_DECL_OVERRIDE
{
    int i = 0;

    m_packet.clear();

    m_packet.append(frameType());
    m_packet.append(frameId());

    for(i=1; i>=0; i--) {
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

void TxRequest16::clear()
Q_DECL_OVERRIDE
{
    XBeePacket::clear();
    m_data.clear();
    m_destinationAddress = 0xFFFF;
}

QString TxRequest16::toString()
Q_DECL_OVERRIDE
{
    return QString();
}

/**
 * @brief Sets the 16 bits packet's destination address
 * @note To send the packet on the broadcast set the address to 0xFFFF
 * @param address the destination address
 */
void TxRequest16::setDestinationAddress(const quint16 address)
{
    m_destinationAddress = address;
}

/**
  @brief Returns the packet's destination address.
 * @return the packet's destination address.
 */
quint16 TxRequest16::destinationAddress() const
{
    return m_destinationAddress;
}

/**
 * @brief Sets the data to be sent (Up to 100 bytes per packet)
 * @param data the data to be sent
 */
void TxRequest16::setData(const QByteArray &data)
{
    m_data = data;
}

/**
 * @brief Returns the data to be sent
 * @return the data to be sent
 */
QByteArray TxRequest16::data() const
{
    return m_data;
}

}} // END namespace
