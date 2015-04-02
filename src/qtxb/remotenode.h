#ifndef REMOTENODE_H
#define REMOTENODE_H

#include <QObject>

namespace QtXBee {

/**
 * @brief The RemoteNode class is used to represent a remote XBee node
 */
class RemoteNode : public QObject
{
    Q_OBJECT
public:
    explicit RemoteNode(QObject *parent = 0);
    ~RemoteNode();

    void setAddress(const quint16 my);
    void setSerialNumberHigh(const quint32 sh);
    void setSerialNumberLow(const quint32 sl);
    void setNodeIdentifier(const QString & ni);
    void setRssi(const qint8 rssi);

    quint16 address() const;
    quint32 serialNumberHigh() const;
    quint32 serialNumberLow() const;
    quint64 serialNumber() const;
    qint8 rssi() const;
    QString nodeIdentifier() const;

    virtual QString toString();

signals:
    void addressChanged             (); /**< @brief emitted when the address changes */
    void serialNumberHighChanged    (); /**< @brief emitted when the serial number's MSB changes */
    void serialNumberLowChanged     (); /**< @brief emitted when the serial number's LSB changes */
    void rssiChanged                (); /**< @brief emitted when the RSSI changes */
    void nodeIdentifierChanged      (); /**< @brief emitted when the node identifier changes */

protected:
    quint16 m_my;   /**< @brief Holds the address */
    quint32 m_sh;   /**< @brief Holds the serial number's MSB */
    quint32 m_sl;   /**< @brief Holds the serial number's LSB */
    qint8 m_rssi;   /**< @brief Holds the RSSI */
    QString m_ni;   /**< @brief Holds the node identifier */
};

} // END namepsace

#endif // REMOTENODE_H
