#ifndef TXREQUEST64_H
#define TXREQUEST64_H

#include "../xbeepacket.h"
#include <QObject>

namespace QtXBee {
namespace WPAN {

/**
 * @brief The TXRequest64 class is used to send a message over 802.15.4 network using 64 bits addresses.
 *
 * API identifier value: 0x00
 */
class TXRequest64 : public XBeePacket
{
    Q_OBJECT
public:
    explicit TXRequest64(QObject *parent = 0);
    ~TXRequest64();

signals:

public slots:
};

} } // END namespace

#endif // TXREQUEST64_H
