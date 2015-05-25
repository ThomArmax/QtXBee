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

#include "RemoteATCommandRequest"
#include <QDebug>

namespace QtXBee {

/**
 * @brief RemoteATCommandRequest's constructor
 * @param parent parent object
 */
RemoteATCommandRequest::RemoteATCommandRequest(QObject *parent) :
    ATCommand(parent),
    m_destinationAddress64(0),
    m_destinationAddress16(0),
    m_options(ApplyChanges)
{
    setFrameType(RemoteATCommandRequestId);
}
// Reimplemented from XBeePacket
void RemoteATCommandRequest::assemblePacket()
Q_DECL_OVERRIDE
{
    int i;

    m_packet.clear();
    m_packet.append(frameType());
    m_packet.append(frameId());
    for(i=7; i>=0; i--) {
        m_packet.append(destinationAddress64() >> (i*8)&0xFF);
    }
    for(i=1; i>=0; i--) {
        m_packet.append(destinationAddress16() >> (i*8)&0xFF);
    }
    m_packet.append(commandOptions());
    m_packet.append(atCommandToByteArray(command()));
    setLength(m_packet.size());
    createChecksum(m_packet);
    m_packet.append(checksum());
    m_packet.insert(0, startDelimiter());
    m_packet.insert(1, (length()>>8)&0xFF);
    m_packet.insert(2, length()&0xFF);
}

void RemoteATCommandRequest::clear()
Q_DECL_OVERRIDE
{
    XBeePacket::clear();
    m_destinationAddress64  = 0;
    m_destinationAddress16  = 0;
    m_options               = 0;
}

QString RemoteATCommandRequest::toString()
Q_DECL_OVERRIDE
{
    return QString();
}

// Setters
/**
 * @brief Sets the 64-bits address of the destination device
 *
 * The following addresses are also supported:
 * - 0x0000000000000000 - Reserved 64-bit address for the coordinator
 * - 0x000000000000FFFF - Broadcast address
 * @param dest
 * @sa RemoteATCommandRequest::destinationAddress64()
 * @sa RemoteATCommandRequest::setDestinationAddress16()
 */
void RemoteATCommandRequest::setDestinationAddress64(const quint64 dest)
{
    m_destinationAddress64 = dest;
}

/**
 * @brief Sets the 16-bit address of the destination device, if known.
 *
 * Set to 0xFFFE if the address is unknown, or if sending a broadcast.
 * @param dest
 * @sa RemoteATCommandRequest::destinationAddress16()
 * @sa RemoteATCommandRequest::setDestinationAddress64()
 */
void RemoteATCommandRequest::setDestinationAddress16(const quint32 dest)
{
    m_destinationAddress16 = dest;
}

/**
 * @brief Sets the remote command options.
 */
void RemoteATCommandRequest::setCommandOptions(const RemoteCommandOptions options)
{
    m_options = options;
}

// Getters
/**
 * @brief Returns the 64-bits address of the destination device
 * @return the 64-bits address of the destination device
 * @sa RemoteATCommandRequest::setDestinationAddress64()
 * @sa RemoteATCommandRequest::destinationAddress16()
 */
quint64 RemoteATCommandRequest::destinationAddress64() const
{
    return m_destinationAddress64;
}

/**
 * @brief Returns the 16-bits address of the destination device
 * @return the 16-bits address of the destination device
 * @sa RemoteATCommandRequest::setDestinationAddress16()
 * @sa RemoteATCommandRequest::destinationAddress64()
 */
quint16 RemoteATCommandRequest::destinationAddress16() const
{
    return m_destinationAddress16;
}

/**
 * @brief Returns the RemoteATCommandRequest's options
 * @return the RemoteATCommandRequest's options
 */
RemoteATCommandRequest::RemoteCommandOptions RemoteATCommandRequest::commandOptions() const
{
    return m_options;
}

} // END namepsace
