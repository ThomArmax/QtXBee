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

#ifndef REMOTECOMMANDRESPONSE_H
#define REMOTECOMMANDRESPONSE_H

#include "atcommandresponse.h"

#include <QObject>
#include <QByteArray>

namespace QtXBee {

/**
 * @brief The RemoteATCommandResponse class represents the response to a RemoteATCommandRequest.
 *
 * If a module receives a remote command response RF data frame in response to a RemoteATCommandRequest,
 * the module will send a RemoteCommandResponse message out the UART.
 * Some commands may send back multiple frames--for example, Node Discover (ND) command.
 *
 * @sa RemoteATCommandRequest
 */
class RemoteATCommandResponse : public ATCommandResponse
{
    Q_OBJECT
public:
    explicit        RemoteATCommandResponse (QObject *parent = 0);
                    RemoteATCommandResponse (const QByteArray & packet, QObject *parent = 0);

    // Reimplement from ATCommandResponse
    virtual QString toString                ();
    virtual void    clear                   ();

    // Setters
    void            setSourceAddress64      (const quint64 addr);
    void            setSourceAddress16      (const quint32 addr);

    // Getters
    quint64         sourceAddress64         () const;
    quint16         sourceAddress16         () const;

protected:
    virtual bool    parseApiSpecificData    (const QByteArray &data);

private:
    quint64         m_sourceAddress64;
    quint16         m_sourceAddress16;
};

} // END namepsace

#endif // REMOTECOMMANDRESPONSE_H
