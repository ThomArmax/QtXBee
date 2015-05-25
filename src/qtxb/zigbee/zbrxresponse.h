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

#ifndef ZBRxRESPONSE_H
#define ZBRxRESPONSE_H

#include "XBeeResponse"

namespace QtXBee {
namespace ZigBee {

class ZBRxResponse : public XBeeResponse
{
    Q_OBJECT
public:
    explicit    ZBRxResponse        (QObject *parent);

    void        setSrcAddr64        (QByteArray sa64);
    void        setSrcAddr16        (QByteArray sa16);
    void        setReceiveOptions   (unsigned ro);
    void        setData             (QByteArray d);

    QByteArray  srcAddr64           () const;
    QByteArray  srcAddr16           () const;
    unsigned    receiveOptions      () const;
    QByteArray  data                () const;
    void        readPacket          (QByteArray rx);

private:
    QByteArray  m_srcAddr64;
    QByteArray  m_srcAddr16;
    unsigned    m_receiveOptions;
    QByteArray  m_data;
};

} } // END namepsace

#endif // ZBRxRESPONSE_H
