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

#include "rxbaseresponse.h"

namespace QtXBee {
namespace Wpan {

RxBaseResponse::RxBaseResponse(QObject *parent) :
    XBeeResponse(parent),
    m_rssi(-1),
    m_options(0)
{
}

RxBaseResponse::~RxBaseResponse()
{
}

void RxBaseResponse::clear()
Q_DECL_OVERRIDE
{
    XBeeResponse::clear();
    m_rssi = -1;
    m_options = 0;
}

QString RxBaseResponse::toString()
Q_DECL_OVERRIDE
{
    return QString();
}

/**
 * @brief Sets the RSSI (Received Signal Strength Indication)
 * @param rssi
 * @sa RxBaseResponse::rssi()
 */
void RxBaseResponse::setRSSI(const qint8 rssi)
{
    m_rssi = rssi;
}

/**
 * @brief Returns the RSSI (Received Signal Strength Indication)
 * @return the RSSI (Received Signal Strength Indication)
 * @sa RxBaseResponse::setRSSI()
 */
qint8 RxBaseResponse::rssi() const
{
    return m_rssi;
}

void RxBaseResponse::setOptions(const quint8 options)
{
    m_options = options;
}

quint8 RxBaseResponse::options() const
{
    return m_options;
}

}} // END namespace
