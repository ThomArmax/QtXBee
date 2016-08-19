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

#ifndef ZBIONODEINDENTIFICATIONRESPONSE_H
#define ZBIONODEINDENTIFICATIONRESPONSE_H

#include "XBeeResponse"

namespace QtXBee {
namespace ZigBee {

/**
 * @brief The NodeIdentificationIndicator frame is received when a module
 * transmits a node identification message to identify itself (when AO=0).
 *
 * The data portion of this frame is similar to a network discovery response frame (see ND command).
 */
class ZBIONodeIdentificationResponse : public XBeeResponse
{
    Q_OBJECT
public:
    explicit ZBIONodeIdentificationResponse(QObject *parent = 0);
    virtual bool setPacket(const QByteArray &packet);

    virtual QString toString() Q_DECL_OVERRIDE;

private:
    quint64 m_senderAddr64;
    quint16 m_senderAddr16;
    quint8 m_receiveOptions;
    quint16 m_remoteAddr16;
    quint64 m_remoteAddr64;
    QString m_nodeIdentifier;
    quint16 m_remoteParent16;
    quint8 m_deviceType;
    quint8 m_sourceEvent;
    quint16 m_digiProfileId;
    quint16 m_digiManufacturerId;
};

} } // END namepsace

#endif // ZBIONODEINDENTIFICATIONRESPONSE_H
