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

#ifndef REMOTEATCOMMANDREQUEST_H
#define REMOTEATCOMMANDREQUEST_H

#include "atcommand.h"

namespace QtXBee {

/**
 * @brief The RemoteATCommandRequest class is used to query or set module parameters on a remote device.
 *
 * For parameter changes on the remote device to take effect, changes must be applied,
 * either by setting the apply changes options bit, or by sending an AC command to the remote.
 */
class RemoteATCommandRequest : public ATCommand
{
    Q_OBJECT
public:
    /**
     * @brief The RemoteCommandOption enum defines the remote command options
     */
    enum RemoteCommandOption {
        DisableRetriesAndRouteRepair    = 0x01, /**< Disable retries and route repair */
        ApplyChanges                    = 0x02, /**< Apply changes */
        EnabledAPSEncryption            = 0x20, /**< Enable APS encryption (if EE=1) */
        UseExtendedTxTimeout            = 0x40  /**< Use the extended transmision timeout */
    };
    Q_DECLARE_FLAGS(RemoteCommandOptions, RemoteCommandOption)

    explicit                RemoteATCommandRequest  (QObject *parent = 0);

    // Reimplemented from ATCommand
    virtual void            assemblePacket          ();
    virtual void            clear                   ();
    virtual QString         toString                ();

    // Setters
    void                    setDestinationAddress64 (const quint64 dest);
    void                    setDestinationAddress16 (const quint32 dest);
    void                    setCommandOptions       (const RemoteCommandOptions options);

    // Getters
    quint64                 destinationAddress64    () const;
    quint16                 destinationAddress16    () const;
    RemoteCommandOptions    commandOptions          () const;

protected:
    quint64                 m_destinationAddress64;
    quint16                 m_destinationAddress16;
    RemoteCommandOptions    m_options;
};

} // END namepsace

#endif // REMOTEATCOMMANDREQUEST_H
