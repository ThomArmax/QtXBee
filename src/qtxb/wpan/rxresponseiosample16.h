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

#ifndef RxRESPONSEIOSAMPLE16_H
#define RxRESPONSEIOSAMPLE16_H

#include "rxresponseiosamplebase.h"

namespace QtXBee {
namespace Wpan {

/**
 * @todo To be implemented
 */
class RxResponseIoSample16 : public RxResponseIoSampleBase
{
public:
    explicit RxResponseIoSample16(QObject * parent = 0);
    virtual ~RxResponseIoSample16();
};

}} // END namespace

#endif // RxRESPONSEIOSAMPLE16_H
