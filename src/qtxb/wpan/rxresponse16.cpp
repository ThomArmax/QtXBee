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

#include "rxresponse16.h"

namespace QtXBee {
namespace Wpan {

RxResponse16::RxResponse16(QObject *parent) :
    RxBaseResponse(parent),
    m_sourceAddress(0)
{
    setFrameType(Rx16ResponseId);
}

RxResponse16::~RxResponse16()
{
}

void RxResponse16::clear()
Q_DECL_OVERRIDE
{
    RxBaseResponse::clear();
    m_sourceAddress = 0;
}

bool RxResponse16::parseApiSpecificData(const QByteArray &data)
Q_DECL_OVERRIDE
{
    if(data.size() < 4) {
        qWarning() << Q_FUNC_INFO << "Invalid data, expected at least 4 bytes, got" << data.size();
        return false;
    }
    setSourceAddress(data.mid(0, 2).toHex().toULongLong(0, 16));
    setRSSI(-1*data.mid(2, 1).toHex().toInt(0, 16));
    setOptions(data.mid(3, 1).toHex().toUInt(0, 16));
    if(data.size() > 4) {
        setData(data.mid(4));
    }

    return true;
}

QString RxResponse16::toString()
Q_DECL_OVERRIDE
{
    QString str;
    str.append(QString("Raw packet      : 0x%1\n").arg(QString(packet().toHex())));
    str.append(QString("Frame id        : %1 (0x%2)\n").arg(frameId(), 0, 16).arg(frameId(), 0, 16));
    str.append(QString("Frame type      : %1 (0x%2)\n").arg(frameTypeToString(frameType())).arg(QString::number(frameType(), 16)));
    str.append(QString("Start delimiter : 0x%1\n").arg(QString::number(startDelimiter(), 16)));
    str.append(QString("Length          : %1 bytes\n").arg(length()));
    str.append(QString("Checksum        : %1\n").arg(checksum()));
    str.append(QString("Source Address  : 0x%1\n").arg(sourceAddress(), 0, 16));
    if(!data().isEmpty())
    str.append(QString("Data            : 0x%1 (0x%2)\n").arg(QString(data())).arg(QString(data().toHex())));
    else
    str.append(QString("Data            : No data\n"));
    return str;
}

/**
 * @brief Sets the 16-bits packet's source address.
 * @param sourceAddress
 * @sa RxResponse16::sourceAddress()
 */
void RxResponse16::setSourceAddress(const quint16 sourceAddress)
{
    m_sourceAddress = sourceAddress;
}

/**
 * @brief Returns the 16-bits packet's source address.
 * @return the 16-bits packet's source address.
 * @sa RxResponse16::setSourceAddress()
 */
quint16 RxResponse16::sourceAddress() const
{
    return m_sourceAddress;
}

}} // END namespace
