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

#include "zbtxstatusresponse.h"
#include <QDebug>

namespace QtXBee {
namespace ZigBee {

ZBTxStatusResponse::ZBTxStatusResponse(QObject *parent) :
    XBeeResponse(parent)
{
    setFrameType(ZBTxStatusResponseId);
}
void ZBTxStatusResponse::readPacket(QByteArray rx){
    m_packet.clear();
    m_packet.append(rx);
    setStartDelimiter(rx.at(0));
    setLength(rx.at(2));
    if(rx.size() == rx.at(2)+4){
        setFrameType((ApiId)rx.at(3));
        setFrameId(rx.at(4));
        m_reserved.append(rx.at(5));
        m_reserved.append(rx.at(6));
        setTransmitRetryCount(rx.at(7));
        setDeliveryStatus(rx.at(8));
        setDiscoveryStatus(rx.at(9));
        setChecksum(rx.at(10));
    }else{

        qDebug()<< "Invalid Packet Received!";
        qDebug()<< m_packet.toHex();
        m_packet.clear();
    }
}
void ZBTxStatusResponse::setDeliveryStatus(unsigned ds){
    m_deliveryStatus = ds;
}
void ZBTxStatusResponse::setTransmitRetryCount(unsigned trc){
    m_transmitRetryCount = trc;
}
void ZBTxStatusResponse::setDiscoveryStatus(unsigned ds){
    m_discoveryStatus = ds;
}
unsigned ZBTxStatusResponse::deliveryStatus() const{
    return m_deliveryStatus;
}
unsigned ZBTxStatusResponse::transmitRetryCount() const{
    return m_transmitRetryCount;
}
unsigned ZBTxStatusResponse::discoveryStatus() const{
    return m_discoveryStatus;
}
QByteArray ZBTxStatusResponse::reserved() const{
    return m_reserved;
}

} } // END namepsace
