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

#ifndef MODEMSTATUS_H
#define MODEMSTATUS_H

#include "XBeeResponse"
#include <QByteArray>

namespace QtXBee {

/**
 * @brief The ModemStatus class represents the XBee module status.
 *
 * RF module status messages are sent from the module in response to specific conditions.
 *
 * API identifier value: 0x8A
 */
class ModemStatus : public XBeeResponse
{
    Q_OBJECT
public:
    enum Status {
        HardwareReset           = 0x00,
        WatchdogTimerReset      = 0x01,
        Associated              = 0x02,
        Disassociated           = 0x03,
        SynchronizationLost     = 0x04,
        CoordinatorRealignment  = 0x05,
        CoordinatorStarted      = 0x06,
        Unkown                  = 0xFF
    };

    explicit    ModemStatus         (QObject *parent);
                ModemStatus         (const QByteArray & packet, QObject * parent = 0);

    QString     toString            () Q_DECL_OVERRIDE;

    void        setStatus           (Status status);
    Status      status              () const;
    QString     statusToString      () const;

private:
    bool        parseApiSpecificData(const QByteArray & data) Q_DECL_OVERRIDE;

private:
    Status      m_status;
};

} // END namepsace

#endif // MODEMSTATUS_H
