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

#ifndef RxRESPONSE16_H
#define RxRESPONSE16_H

#include "RxBaseResponse"

#include <QObject>

namespace QtXBee {
namespace Wpan {

/**
 * @brief The RxResponse16 class represents the reponse to a TxRequest16
 *
 * API identifier value: 0x81
 */
class RxResponse16 : public RxBaseResponse
{
    Q_OBJECT
public:
    explicit        RxResponse16            (QObject *parent = 0);
    virtual         ~RxResponse16           ();

    // Reimplemented from RxBaseResponse
    virtual void    clear                   ();
    virtual QString toString                ();

    void            setSourceAddress        (const quint16 sourceAddress);
    quint16         sourceAddress           () const;

protected:
    virtual bool    parseApiSpecificData    (const QByteArray &data);

private:
    quint16         m_sourceAddress;
};

}} // END namespace

#endif // RxRESPONSE16_H
