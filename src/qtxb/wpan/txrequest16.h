#ifndef TXREQUEST16_H
#define TXREQUEST16_H

#include "../xbeepacket.h"
#include <QObject>

namespace QtXBee {
namespace WPAN {

class TXRequest16 : public XBeePacket
{
    Q_OBJECT
public:
    explicit TXRequest16(QObject *parent = 0);
    ~TXRequest16();

signals:

public slots:
};

} } // END namespace

#endif // TXREQUEST16_H
