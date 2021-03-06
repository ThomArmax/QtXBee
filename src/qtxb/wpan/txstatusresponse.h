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

#ifndef TxSTATUSRESPONSE_H
#define TxSTATUSRESPONSE_H

#include "../XBeeResponse"

namespace QtXBee {
namespace Wpan {

/**
 * @brief The TxStatusResponse class is used to indicate if a packet (TxRequest64 or TxRequest16)
 * was transmitted successfully or if there was a failure.
 *
 * API identifier value: 0x89
 */
class TxStatusResponse : public XBeeResponse
{
    Q_OBJECT
public:
    /**
     * @brief The Status enum
     */
    enum Status {
        Unknown     = -1,   /**< @brief Unknown, invalid value */
        Success     = 0,    /**< @brief Success */
        NoACK       = 1,    /**< @brief No acknowledgment */
        CCAFailure  = 2,    /**< @brief CCA Failure */
        Purged      = 3     /**< @brief Purged */
    };

    explicit        TxStatusResponse        (QObject *parent = 0);
    virtual         ~TxStatusResponse       ();

    // Reimplemented from XBeeResponse
    virtual void    clear                   () Q_DECL_OVERRIDE;
    virtual QString toString                () Q_DECL_OVERRIDE;

    void            setStatus               (const Status status);
    Status          status                  () const;

    static QString  statusToString          (const Status status);

protected:
    virtual bool    parseApiSpecificData    (const QByteArray &data) Q_DECL_OVERRIDE;

private:
    Status          m_status;
};

}} // END namepsace

#endif // TxSTATUSRESPONSE_H
