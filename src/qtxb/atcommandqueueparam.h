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

#ifndef ATCOMMANDQUEUEPARAM_H
#define ATCOMMANDQUEUEPARAM_H

#include "atcommand.h"
#include <QByteArray>

namespace QtXBee {

/**
 * @brief The ATCommandQueueParam class allows module parameters to be queried or set.
 *
 * In contrast to the ATCommand API type, new parameter values are queued and not applied
 * until either the ATCommand (0x08) API type or the AC (Apply Changes) command is issued.
 * Register queries (reading parameter values) are returned immediately.
 */
class ATCommandQueueParam : public ATCommand
{
    Q_OBJECT
public:
    explicit ATCommandQueueParam(QObject *parent);
};

} // END namepsace

#endif // ATCOMMANDQUEUEPARAM_H
