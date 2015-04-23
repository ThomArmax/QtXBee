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

#ifndef RxRESPONSE64_H
#define RxRESPONSE64_H

#include "rxbaseresponse.h"

#include <QObject>

namespace QtXBee {
namespace Wpan {


class RxResponse64 : public RxBaseResponse
{
    Q_OBJECT
public:
    explicit        RxResponse64        (QObject * parent = 0);
    virtual         ~RxResponse64       ();

    // Reimplemented from RxBaseResponse
    virtual void    clear               ();
    virtual QString toString            ();

    void            setSourceAddress    (const quint64 sourceAddress);
    quint64         sourceAddress       () const;

protected:
    virtual bool    parseApiSpecificData(const QByteArray &data);

private:
    quint64         m_sourceAddress;
};

}} // END namespace

#endif // RxRESPONSE64_H
