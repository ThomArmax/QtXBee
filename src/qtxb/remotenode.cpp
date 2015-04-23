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

#include "remotenode.h"

namespace QtXBee {

RemoteNode::RemoteNode(QObject *parent) :
    QObject (parent),
    m_my    (0),
    m_sh    (0),
    m_sl    (0),
    m_rssi  (0),
    m_ni    (QString())
{

}

RemoteNode::~RemoteNode()
{

}

/**
 * @brief Sets the RemoteNode's address (16 bits address)
 *
 * The RemoteNode::addressChanged() signal will be emitted is the
 * address changes.
 * @param my
 * @sa RemoteNode::address()
 * @sa RemoteNode::addressChanged()
 */
void RemoteNode::setAddress(const quint16 my) {
    if(m_my != my) {
        m_my = my;
        emit addressChanged();
    }
}

/**
 * @brief Sets the serial number (MSB part)
 *
 * The RemoteNode::serialNumberHighChanged() signal will be emitted is the
 * serial number changes.
 * @param my
 * @sa RemoteNode::serialNumberHigh()
 * @sa RemoteNode::serialNumberHighChanged()
 */
void RemoteNode::setSerialNumberHigh(const quint32 sh) {
    if(m_sh != sh) {
        m_sh = sh;
        emit serialNumberHighChanged();
    }
}

/**
 * @brief Sets the serial number (LSB part)
 *
 * The RemoteNode::serialNumberLowChanged() signal will be emitted is the
 * serial number changes.
 * @param my
 * @sa RemoteNode::serialNumberLow()
 * @sa RemoteNode::serialNumberLowChanged()
 */
void RemoteNode::setSerialNumberLow(const quint32 sl) {
    if(m_sl != sl) {
        m_sl = sl;
        emit serialNumberLowChanged();
    }
}

/**
 * @brief Sets the node identifier
 *
 * The RemoteNode::nodeIdentifierChanged() signal will be emitted is the
 * node identifier changes.
 * @param my
 * @sa RemoteNode::nodeIdentifier()
 * @sa RemoteNode::nodeIdentifierChanged()
 */
void RemoteNode::setNodeIdentifier(const QString & ni) {
    if(m_ni != ni) {
        m_ni = ni;
        emit nodeIdentifierChanged();
    }
}

/**
 * @brief Sets the RSSI (Received Signal Strength Indication)
 *
 * The RemoteNode::rssiChanged() signal will be emitted is the
 * node identifier changes.
 * @param rssi
 * @sa RemoteNode::rssi()
 * @sa RemoteNode::rssiChanged()
 */
void RemoteNode::setRssi(const qint8 rssi) {
    if(m_rssi != rssi) {
        m_rssi = rssi;
        emit rssiChanged();
    }
}

/**
 * @brief Returns the RemoteNode's address (16 bits address)
 * @return the RemoteNode's address (16 bits address)
 * @sa RemoteNode::setAddress()
 * @sa RemoteNode::addressChanged()
 */
quint16 RemoteNode::address() const {
    return m_my;
}

/**
 * @brief Returns the RemoteNode' serial number (MSB part)
 * @return the serial number (MSB part)
 * @sa RemoteNode::setSerialNumberHigh()
 * @sa RemoteNode::serialNumberHighChanged()
 * @sa RemoteNode::serialNumberLow()
 * @sa RemoteNode::serialNumber()
 */
quint32 RemoteNode::serialNumberHigh() const {
    return m_sh;
}

/**
 * @brief Returns the RemoteNode' serial number (LSB part)
 * @return the serial number (LSB part)
 * @sa RemoteNode::setSerialNumberLow()
 * @sa RemoteNode::serialNumberLowChanged()
 * @sa RemoteNode::serialNumberHigh()
 * @sa RemoteNode::serialNumber()
 */
quint32 RemoteNode::serialNumberLow() const {
    return m_sl;
}

/**
 * @brief Returns the RemoteNode' serial number (64 bits)
 * @return the RemoteNode' serial number (64 bits)
 * @sa RemoteNode::serialNumberHigh()
 * @sa RemoteNode::serialNumberLow()
 * @sa RemoteNode::setSerialNumberHigh()
 * @sa RemoteNode::setSerialNumberLow()
 */
quint64 RemoteNode::serialNumber() const {
    return ((quint64)m_sh<<32) + m_sl;
}

/**
 * @brief Returns the RSSI (Received Signal Strength Indication)
 * @return the RSSI (Received Signal Strength Indication)
 * @sa RemoteNode::setRssi()
 * @sa RemoteNode::rssiChanged()
 */
qint8 RemoteNode::rssi() const {
    return m_rssi;
}

/**
 * @brief Returns the node identifier
 * @return the node identifier
 * @sa RemoteNode::setNodeIdentifier()
 * @sa RemoteNode::nodeIdentifierChanged()
 */
QString RemoteNode::nodeIdentifier() const {
    return m_ni;
}

/**
 * @brief Returns the RemoteNode's properties in a human readable string.
 * @return the RemoteNode's properties in a human readable string.
 */
QString RemoteNode::toString() {
    QString str;
    if(!nodeIdentifier().isEmpty())
    str += QString("Node '%1', ").arg(nodeIdentifier());
    str += QString("Addr 0x%1, ").arg(QString::number(m_my, 16));
    str += QString("Serial number 0x%1, ").arg(QString::number(serialNumber(), 16));
    str += QString("RSSI %1 dBm").arg(m_rssi);
    return str;
}

} // END namepsace
