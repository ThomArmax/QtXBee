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

#include "txstatusresponse.h"
#include <QDebug>

namespace QtXBee {
namespace WPAN {

TXStatusResponse::TXStatusResponse(QObject *parent) :
    XBeePacket(parent),
    m_status(Unknown)
{
    setFrameType(TXStatusResponseId);
}

TXStatusResponse::~TXStatusResponse()
{

}

void TXStatusResponse::clear()
Q_DECL_OVERRIDE
{
    XBeePacket::clear();
    setStatus(Unknown);
}

QString TXStatusResponse::toString()
Q_DECL_OVERRIDE
{
    QString str;
    str.append(QString("Raw packet      : 0x%1\n").arg(QString(packet().toHex())));
    str.append(QString("Frame id        : %1 (0x%2)\n").arg(frameId()).arg(frameId(), 0, 16));
    str.append(QString("Frame type      : %1 (0x%2)\n").arg(frameTypeToString(frameType())).arg(QString::number(frameType(), 16)));
    str.append(QString("Start delimiter : 0x%1\n").arg(QString::number(startDelimiter(), 16)));
    str.append(QString("Length          : %1 bytes\n").arg(length()));
    str.append(QString("Checksum        : %1\n").arg(checksum()));
    str.append(QString("Status          : %1 (0x%2)\n").arg(statusToString(m_status)).arg(m_status, 0, 16));

    return str;
}

bool TXStatusResponse::parseApiSpecificData(const QByteArray &data)
{
    if(data.size() != 2) {
        qDebug() << Q_FUNC_INFO << "invalid data";
        return false;
    }

    setFrameId(data.mid(0,1).toHex().toUInt(0,16));
    setStatus((Status)data.at(1));

    return true;
}

void TXStatusResponse::setStatus(const Status status)
{
    m_status = status;
}

TXStatusResponse::Status TXStatusResponse::status() const
{
    return m_status;
}

QString TXStatusResponse::statusToString(const Status status)
{
    QString str = "Unknown";

    switch(status) {
    case Success    : str = "Success"               ; break;
    case NoACK      : str = "No Acknowledgement"    ; break;
    case CCAFailure : str = "CCA Failure"           ; break;
    case Purged     : str = "Purged"                ; break;
    default         : break;
    }

    return str;
}


}} // END namepsace
