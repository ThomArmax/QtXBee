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

#ifndef TXSTATUSRESPONSE_H
#define TXSTATUSRESPONSE_H

#include "../xbeepacket.h"

namespace QtXBee {
namespace WPAN {

class TXStatusResponse : public XBeePacket
{
    Q_OBJECT
public:
    enum Status {
        Unknown     = -1,
        Success     = 0,
        NoACK       = 1,
        CCAFailure  = 2,
        Purged      = 3
    };

    explicit        TXStatusResponse        (QObject *parent = 0);
    virtual         ~TXStatusResponse       ();

    // Reimplemented from XBeePacket
    virtual void    clear                   ();
    virtual QString toString                ();

    void            setStatus               (const Status status);
    Status          status                  () const;

    static QString  statusToString          (const Status status);

protected:
    virtual bool    parseApiSpecificData    (const QByteArray &data);

private:
    Status          m_status;
};

}} // END namepsace

#endif // TXSTATUSRESPONSE_H
