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

#include "byteutils.h"

namespace QtXBee {

/**
 * @brief Returns the given quint8 converted into QByteArray
 * @param number
 * @return the given quint8 converted into QByteArray
 */
QByteArray ByteUtils::uintToByteArray(quint8 number)
{
    return QByteArray::number(number);
}

/**
 * @brief Returns the given quint16 converted into QByteArray
 * @param number
 * @return the given quint16 converted into QByteArray
 */
QByteArray ByteUtils::uintToByteArray(quint16 number)
{
    QByteArray array;
    int i = 0;
    for(i=1; i>=0; i--) {
        array.append(number >> (i*8)&0xFF);
    }
    return array;
}

/**
 * @brief Returns the given quint32 converted into QByteArray
 * @param number
 * @return the given quint32 converted into QByteArray
 */
QByteArray ByteUtils::uintToByteArray(quint32 number)
{
    QByteArray array;
    int i = 0;
    for(i=3; i>=0; i--) {
        array.append(number >> (i*8)&0xFF);
    }
    return array;
}

/**
 * @brief Returns the given quint64 converted into QByteArray
 * @param number
 * @return the given quint64 converted into QByteArray
 */
QByteArray ByteUtils::uintToByteArray(quint64 number)
{
    QByteArray array;
    int i = 0;
    for(i=7; i>=0; i--) {
        array.append(number >> (i*8)&0xFF);
    }
    return array;
}

} // END namespace
