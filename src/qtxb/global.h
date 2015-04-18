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

#ifndef GLOBAL
#define GLOBAL

#include <QtGlobal>

/**
 * @file global.h Defines global properties and glob enums.
 */
namespace QtXBee {

/**
 * @brief The DeviceType enum
 */
enum DeviceType {
    Coordinator,
    Router,
    EndDevice
};

/**
 * @brief The HardwareVersion enum
 */
enum HardwareVersion {
    XBeeSerie1 = 0x17,      /**< XBee Serie 1 hardware version */
    XBeeSerie1Pro,          /**< XBee Serie 1 Pro hardware version */
    XBeeSeriel2,            /**< XBee Serie 2 hardware version */
    XBeeSerie2Pro,          /**< XBee Serie 2 hardware version */
    XBeeSerieUnknown        /**< Unkown/Invalid hardware version */
};

typedef quint64 XBee64BitsAddr;
typedef quint16 XBee16BitsAddr;

} // END namespace

#endif // GLOBAL

