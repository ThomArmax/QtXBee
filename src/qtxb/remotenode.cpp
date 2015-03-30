#include "remotenode.h"

RemoteNode::RemoteNode(QObject *parent) : QObject(parent)
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

quint16 RemoteNode::address() const {
    return m_my;
}

quint32 RemoteNode::serialNumberHigh() const {
    return m_sh;
}

quint32 RemoteNode::serialNumberLow() const {
    return m_sl;
}

qint8 RemoteNode::rssi() const {
    return m_rssi;
}

QString RemoteNode::nodeIdentifier() const {
    return m_ni;
}
