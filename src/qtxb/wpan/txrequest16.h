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

#ifndef TxREQUEST16_H
#define TxREQUEST16_H

#include "../XBeePacket"
#include <QObject>

namespace QtXBee {
namespace Wpan {

/**
 * @brief The TxRequest16 class is used to send a message over 802.15.4 network using 16 bits addresses.
 *
 * API identifier value: 0x01
 */
class TxRequest16 : public XBeePacket
{
    Q_OBJECT
public:
    explicit        TxRequest16             (QObject *parent = 0);
                    ~TxRequest16            ();

    // Reimplemented from XBeePacket
    virtual void    assemblePacket          () Q_DECL_OVERRIDE;
    virtual void    clear                   () Q_DECL_OVERRIDE;
    virtual QString toString                () Q_DECL_OVERRIDE;

    void            setDestinationAddress   (const quint16 address);
    void            setData                 (const QByteArray & data);

    quint16         destinationAddress      () const;
    QByteArray      data                    () const;

private:
    quint16         m_destinationAddress;
    QByteArray      m_data;
};

} } // END namespace

#endif // TxREQUEST16_H
