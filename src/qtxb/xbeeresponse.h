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

#ifndef XBEERESPONSE_H
#define XBEERESPONSE_H

#include "XBeePacket"
#include <QObject>
#include <QDebug>

namespace QtXBee {

/**
 * @brief The XBeeResponse class is the base to create API frames responses.
 */
class XBeeResponse : public XBeePacket
{
    Q_OBJECT
public:
    /**
     * @brief The CommandStatus enum
     * @todo Move the enum in ATCommandResponse
     */
    enum CommandStatus {
        Ok                  = 0,    /**< Ok */
        Error               = 1,    /**< Error */
        InvalidCommand      = 2,    /**< Invalid Command */
        InvalidParameter    = 3,    /**< Invalid Parameter */
        TxFailure           = 4     /**< Transmission failure */
    };

    explicit        XBeeResponse    (QObject *parent = 0);
                    ~XBeeResponse   ();

    // Reimplemented from XBeePacket
    virtual void    clear           ();

    void            setData         (const QByteArray & data);
    void            setCommandStatus(const CommandStatus status);

    QByteArray      data            () const;
    CommandStatus   commandStatus   () const;

    static QString  statusToString  (const XBeeResponse::CommandStatus status);

protected:
    QByteArray      m_data;
    CommandStatus   m_status;
};

} // END namepsace

#endif // XBEERESPONSE_H
