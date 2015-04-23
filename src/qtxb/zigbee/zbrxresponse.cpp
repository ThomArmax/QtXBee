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

#include "zbrxresponse.h"
#include "xbeepacket.h"
#include <QDebug>

namespace QtXBee {
namespace ZigBee {

ZBRxResponse::ZBRxResponse(QObject *parent) :
    XBeePacket(parent)
{
    setFrameType(XBeePacket::ZBRxResponseId);
}
void ZBRxResponse::setSrcAddr64(QByteArray sa64) {
    m_srcAddr64.clear();
    m_srcAddr64.append(sa64);
}
void ZBRxResponse::setSrcAddr16(QByteArray sa16) {
    m_srcAddr16.clear();
    m_srcAddr16.append(sa16);
}
void ZBRxResponse::setData(QByteArray d) {
    m_data.clear();
    m_data.append(d);
}
QByteArray ZBRxResponse::srcAddr64() const {
    return m_srcAddr64;
}
QByteArray ZBRxResponse::srcAddr16() const {
    return m_srcAddr16;
}
void ZBRxResponse::setReceiveOptions(unsigned ro) {
    m_receiveOptions = ro;
}
unsigned ZBRxResponse::receiveOptions() const {
    return m_receiveOptions;
}
QByteArray ZBRxResponse::data() const {
    return m_data;
}
void ZBRxResponse::readPacket(QByteArray rx) {
    setPacket(rx);
    setStartDelimiter(rx.at(0));
    setLength(rx.at(2));
    if(rx.size() == rx.at(2)+4 && rx.size() > 15) {
        setFrameType((ApiId)rx.at(3));
        m_srcAddr64.append(rx.at(4));
        m_srcAddr64.append(rx.at(5));
        m_srcAddr64.append(rx.at(6));
        m_srcAddr64.append(rx.at(7));
        m_srcAddr64.append(rx.at(8));
        m_srcAddr64.append(rx.at(9));
        m_srcAddr64.append(rx.at(10));
        m_srcAddr64.append(rx.at(11));
        m_srcAddr16.append(rx.at(12));
        m_srcAddr16.append(rx.at(13));
        setReceiveOptions(rx.at(14));
        int count = 15;
        while(count < rx.size()-1) {
            m_data.append(rx.at(count));
            count++;
        }
        setChecksum(rx.at(count));
    }else{

        qDebug()<< "Invalid Packet Received!";
        qDebug()<< rx.toHex();
        clear();
    }
}

} } // END namepsace
