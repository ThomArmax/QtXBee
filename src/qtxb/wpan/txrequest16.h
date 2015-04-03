#ifndef TXREQUEST16_H
#define TXREQUEST16_H

#include "../xbeepacket.h"
#include <QObject>

namespace QtXBee {
namespace WPAN {

/**
 * @brief The TXRequest16 class is used to send a message over 802.15.4 network using 16 bits addresses.
 *
 * API identifier value: 0x01
 */
class TXRequest16 : public XBeePacket
{
    Q_OBJECT
public:
    explicit TXRequest16(QObject *parent = 0);
    ~TXRequest16();

    // Reimplemented from XBeePacket
    virtual void assemblePacket();
    virtual void clear();
    virtual QString toString();

    void setDestinationAddress(const quint16 address);
    quint16 destinationAddress() const;
    void setData(const QByteArray & data);
    QByteArray data() const;

private:
    quint16 m_destinationAddress;
    QByteArray m_data;
};

} } // END namespace

#endif // TXREQUEST16_H
