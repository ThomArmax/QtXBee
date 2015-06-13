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

#ifndef ATCOMMANDRESPONSE_H
#define ATCOMMANDRESPONSE_H

#include "XBeeResponse"
#include "ATCommand"
#include <QByteArray>

namespace QtXBee {

/**
 * @brief In response to an ATCommand message, the module will send an ATCommandResponse message.
 *
 * Some commands will send back multiple frames (for example, the ND (Node Discover) command).
 *
 * API identifier value: 0x88
 * @sa ATCommand
 */
class ATCommandResponse : public XBeeResponse
{
    Q_OBJECT
public:
    /**
     * @brief The CommandStatus enum
     */
    enum Status {
        Ok                  = 0,    /**< Ok */
        Error               = 1,    /**< Error */
        InvalidCommand      = 2,    /**< Invalid Command */
        InvalidParameter    = 3,    /**< Invalid Parameter */
        TxFailure           = 4     /**< Transmission failure */
    };

    explicit                    ATCommandResponse   (QObject *parent = 0);
                                ATCommandResponse   (const QByteArray &packet, QObject * parent = 0);

    // Reimplemented from XBeeResponse
    virtual QString             toString            ();
    virtual void                clear               ();

    void                        setATCommand        (ATCommand::ATCommandType at);
    void                        setATCommand        (const QByteArray & at);
    void                        setStatus    (const Status status);

    ATCommand::ATCommandType    atCommand           () const;
    Status                      status              () const;

    QString                     statusToString      () const;
    static QString              statusToString      (const ATCommandResponse::Status status);

protected:
    virtual bool                parseApiSpecificData(const QByteArray &data);

protected:
    ATCommand::ATCommandType    m_atCommand;
    Status                      m_status;
};

} // END namepsace

#endif // ATCOMMANDRESPONSE_H
