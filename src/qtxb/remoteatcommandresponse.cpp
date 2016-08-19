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

#include "RemoteATCommandResponse"

#include <QDebug>

namespace QtXBee {

RemoteATCommandResponse::RemoteATCommandResponse(QObject *parent) :
    ATCommandResponse(parent)
{
    setFrameType(RemoteATCommandResponseId);
}

RemoteATCommandResponse::RemoteATCommandResponse(const QByteArray &data, QObject *parent) :
    ATCommandResponse(parent)
{
    setFrameType(RemoteATCommandResponseId);
    setPacket(data);
}

void RemoteATCommandResponse::clear() {
    ATCommandResponse::clear();
    m_sourceAddress64   = 0;
    m_sourceAddress16   = 0;
}

bool RemoteATCommandResponse::parseApiSpecificData(const QByteArray &data)
{
    if(data.size() < 13) {
        qDebug() << Q_FUNC_INFO << "bad data !";
        return false;
    }
    setFrameId(data.at(0));
    setSourceAddress64(data.mid(1, 8).toHex().toULong(0,16));
    setSourceAddress16(data.mid(9, 2).toHex().toUInt(0,16));
    setATCommand((ATCommand::ATCommandType) data.mid(11, 2).toHex().toUInt(0,16));
    setStatus((Status) data.at(13));
    if(data.size() > 14) {
        for(int i=14; i < data.size(); i++) {
            m_data.append(data.at(i));
        }
    }

    return true;
}

QString RemoteATCommandResponse::toString()
{
    QString str;
    str.append(QString("Raw packet                   : 0x%1\n").arg(QString(packet().toHex())));
    str.append(QString("Start delimiter              : 0x%1\n").arg(QString::number(startDelimiter(), 16)));
    str.append(QString("Frame type                   : %1 (0x%2)\n").arg(frameTypeToString(frameType())).arg(QString::number(frameType(), 16)));
    str.append(QString("Length                       : %1 bytes\n").arg(length()));
    str.append(QString("Frame id                     : %1\n").arg(frameId()));
    if(!m_data.isEmpty())
    str.append(QString("Data                         : 0x%1 (%2)\n").arg(QString(m_data.toHex())).arg(QString(m_data)));
    else
    str.append(QString("Data                         : No data\n"));
    str.append(QString("Source Address 64bits        : 0x%1\n").arg(m_sourceAddress64, 0, 16));
    str.append(QString("Source Address 16bits        : 0x%1\n").arg(m_sourceAddress16, 0, 16));
    str.append(QString("AT Command                   : %1 (0x%2)\n").arg(ATCommand::atCommandToString(m_atCommand)).arg(m_atCommand, 0,16));
    str.append(QString("Command Status               : %1 (0x%2)\n").arg(statusToString()).arg(m_status, 0, 16));
    str.append(QString("Checksum                     : %1\n").arg(checksum()));

    return  str;
}

// Setters
/**
 * @brief Sets the 64-bit address of the source device.
 * @param addr
 * @sa RemoteATCommandResponse::setSourceAddress64()
 * @sa RemoteATCommandResponse::sourceAddress16()
 */
void RemoteATCommandResponse::setSourceAddress64(const quint64 addr) {
    m_sourceAddress64 = addr;
}

/**
 * @brief Sets the 16-bit address of the source device.
 * @param addr
 * @sa RemoteATCommandResponse::setSourceAddress16()
 * @sa RemoteATCommandResponse::sourceAddress64()
 */
void RemoteATCommandResponse::setSourceAddress16(const quint32 addr) {
    m_sourceAddress16 = addr;
}

// Getters
/**
 * @brief Returns the 64-bits address of the source device
 * @return the 64-bits address of the source device
 * @sa RemoteATCommandResponse::setSourceAddress64()
 * @sa RemoteATCommandResponse::sourceAddress16()
 */
quint64 RemoteATCommandResponse::sourceAddress64() const {
    return m_sourceAddress64;
}

/**
 * @brief Returns the 16-bits address of the source device
 * @return the 16-bits address of the source device
 * @sa RemoteATCommandResponse::setSourceAddress16()
 * @sa RemoteATCommandResponse::sourceAddress64()
 */
quint16 RemoteATCommandResponse::sourceAddress16() const {
    return m_sourceAddress16;
}

} // END namepsace
