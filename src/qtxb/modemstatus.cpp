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

#include "modemstatus.h"
#include "xbeepacket.h"
#include <QDebug>

namespace QtXBee {

ModemStatus::ModemStatus(QObject *parent) :
    XBeePacket(parent)
{
    setFrameType(XBeePacket::ModemStatusResponseId);
}

ModemStatus::ModemStatus(const QByteArray &data, QObject *parent) :
    XBeePacket(parent)
{
    setFrameType(XBeePacket::ModemStatusResponseId);
    setData(data);
}

bool ModemStatus::setData(const QByteArray & data) {
    bool bRet = false;
    m_packet.clear();
    m_packet.append(data);
    setStartDelimiter(data.at(0));
    setLength(data.at(2));

    if(data.size() == data.at(2)+4) {
        setFrameType((ApiId)data.at(3));
        setStatus(data.at(4));
        setChecksum(data.at(5));
        bRet = true;
    }
    else {
        qDebug()<< Q_FUNC_INFO << "Invalid Packet !" << m_packet.toHex();
        m_packet.clear();
    }

    return bRet;
}

void ModemStatus::setStatus(unsigned s){
    m_status = s;
}

unsigned ModemStatus::status() const{
    return m_status;
}

} // END namepsace
