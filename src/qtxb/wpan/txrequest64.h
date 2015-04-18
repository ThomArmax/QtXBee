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

#ifndef TXREQUEST64_H
#define TXREQUEST64_H

#include "../xbeepacket.h"
#include <QObject>

namespace QtXBee {
namespace Wpan {

/**
 * @brief The TXRequest64 class is used to send a message over 802.15.4 network using 64 bits addresses.
 *
 * API identifier value: 0x00
 */
class TXRequest64 : public XBeePacket
{
    Q_OBJECT
public:
    explicit        TXRequest64             (QObject *parent = 0);
                    ~TXRequest64            ();

    // Reimplemented from XBeePacket
    virtual void    assemblePacket          ();
    virtual void    clear                   ();
    virtual QString toString                ();

    void            setDestinationAddress   (const quint64 address);
    void            setData                 (const QByteArray & data);

    quint64         destinationAddress      () const;
    QByteArray      data                    () const;

private:
    quint64         m_destinationAddress;
    QByteArray      m_data;
};

} } // END namespace

#endif // TXREQUEST64_H
