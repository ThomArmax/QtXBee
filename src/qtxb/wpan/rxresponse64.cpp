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

#include "RxResponse64"

#include <QDebug>

namespace QtXBee {
namespace Wpan {

RxResponse64::RxResponse64(QObject *parent) :
    RxBaseResponse(parent),
    m_sourceAddress(0)
{
    setFrameType(Rx64ResponseId);
}

RxResponse64::~RxResponse64()
{
}

void RxResponse64::clear()
{
    RxBaseResponse::clear();
    m_sourceAddress = 0;
}

bool RxResponse64::parseApiSpecificData(const QByteArray &data)
{
    if(data.size() < 9) {
        qWarning() << Q_FUNC_INFO << "Invalid data, expected at least 9 bytes, got" << data.size();
        return false;
    }
    setSourceAddress(data.mid(0, 8).toHex().toULongLong(0, 16));
    setRSSI(-1*data.mid(8, 1).toHex().toInt(0, 16));
    setOptions(data.mid(9, 1).toHex().toUInt(0, 16));
    if(data.size() > 10) {
        setData(data.mid(10));
    }

    return true;
}

QString RxResponse64::toString()
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
 * @brief Sets the 64-bits packet's source address.
 * @param sourceAddress
 * @sa RxResponse64::sourceAddress()
 */
void RxResponse64::setSourceAddress(const quint64 sourceAddress)
{
    m_sourceAddress = sourceAddress;
}

/**
 * @brief Returns the 64-bits packet's source address.
 * @return the 64-bits packet's source address.
 * @sa RxResponse64::setSourceAddress()
 */
quint64 RxResponse64::sourceAddress() const
{
    return m_sourceAddress;
}

}} // END namespace
