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

#include "rxresponseiosamplebase.h"
#include <QDebug>

namespace QtXBee {
namespace Wpan {

RxResponseIoSampleBase::RxResponseIoSampleBase(QObject *parent) :
    RxBaseResponse(parent),
    m_samplesCount(0),
    m_channelMask(0)
{
}

RxResponseIoSampleBase::~RxResponseIoSampleBase()
{
}

void RxResponseIoSampleBase::clear()
{
    RxBaseResponse::clear();
    m_samplesCount = 0;
    m_channelMask = 0;
}

bool RxResponseIoSampleBase::parseApiSpecificData(const QByteArray &data)
{
    Q_UNUSED(data)
    if(data.size() != length()-1) {
        qWarning() << Q_FUNC_INFO << "bad packet size";
        return false;
    }

    if((ApiId)data.at(0) != frameType()) {
        qWarning() << Q_FUNC_INFO << "bad frame api id";
        return false;
    }

    // source address 16 data.at(1)
    setRSSI(-1*data.mid(2, 1).toHex().toInt(0, 16));

    // option byte data.at(3);

    setSampleCount(data.at(4));

    setChannelMask(data.mid(5, 2).toHex().toUInt(0, 16));

    return false;
}

QString RxResponseIoSampleBase::toString()
{
    return QString();
}

}} // END namespace
