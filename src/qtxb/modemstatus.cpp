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

#include "ModemStatus"
#include <QDebug>

namespace QtXBee {

ModemStatus::ModemStatus(QObject *parent) :
    XBeeResponse(parent),
    m_status(Unkown)
{
    setFrameType(ModemStatusResponseId);
}

ModemStatus::ModemStatus(const QByteArray &packet, QObject *parent) :
    XBeeResponse(parent),
    m_status(Unkown)
{
    setFrameType(ModemStatusResponseId);
    setPacket(packet);
}

bool ModemStatus::parseApiSpecificData(const QByteArray &data)
Q_DECL_OVERRIDE
{
    if(data.size() != 1) {
        qDebug() << Q_FUNC_INFO << "bad data !";
        return false;
    }
    setStatus((Status)data.at(0));
    return true;
}

void ModemStatus::setStatus(Status status)
{
    m_status = status;
}

ModemStatus::Status ModemStatus::status() const
{
    return m_status;
}

QString ModemStatus::statusToString() const
{
    QString str;
    switch(m_status) {
    case HardwareReset          : str = "Hardware Reset";           break;
    case WatchdogTimerReset     : str = "Watchdog Timer Reset";     break;
    case Associated             : str = "Associated";               break;
    case Disassociated          : str = "Disassociated";            break;
    case SynchronizationLost    : str = "Synchronization Lost";     break;
    case CoordinatorRealignment : str = "Coordinator Realignment";  break;
    case CoordinatorStarted     : str = "Coordinator Started";      break;
    default                     : str = "Unknown";                  break;
    }
    return str;
}

QString ModemStatus::toString()
Q_DECL_OVERRIDE
{
    QString str;
    str.append(QString("Raw packet      : 0x%1\n").arg(QString(packet().toHex())));
    str.append(QString("Frame type      : %1 (0x%2)\n").arg(frameTypeToString(frameType())).arg(QString::number(frameType(), 16)));
    str.append(QString("Start delimiter : 0x%1\n").arg(QString::number(startDelimiter(), 16)));
    str.append(QString("Length          : %1 bytes\n").arg(length()));
    str.append(QString("Checksum        : %1\n").arg(checksum()));
    str.append(QString("Status          : %1 (0x%2)").arg(statusToString()).arg(m_status,0,16));

    return str;
}

} // END namepsace
