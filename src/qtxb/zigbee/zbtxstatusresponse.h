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

#ifndef ZBTxSTATUSRESPONSE_H
#define ZBTxSTATUSRESPONSE_H

#include "xbeepacket.h"

namespace QtXBee {
namespace ZigBee {

/**
 * @brief The ZBTxStatusResponse class indicate if the packet was transmitted successfully or not.
 *
 * When a ZBTxRequest is completed, the module sends a Tx Status message.
 * This message will indicate if the packet was transmitted successfully or if there was a failure.
 * @sa ZBTxRequest
 */
class ZBTxStatusResponse : public XBeePacket
{
    Q_OBJECT
public:
    explicit    ZBTxStatusResponse      (QObject *parent);

     void       readPacket              (QByteArray rx);
     void       setDeliveryStatus       (unsigned ds);
     void       setTransmitRetryCount   (unsigned trc);
     void       setDiscoveryStatus      (unsigned ds);

     unsigned   deliveryStatus          () const;
     unsigned   transmitRetryCount      () const;
     unsigned   discoveryStatus         () const;
     QByteArray reserved                () const;

private:
     QByteArray m_reserved;
     unsigned   m_deliveryStatus;
     unsigned   m_transmitRetryCount;
     unsigned   m_discoveryStatus;
};

} } // END namepsace

#endif // ZBTxSTATUSRESPONSE_H
