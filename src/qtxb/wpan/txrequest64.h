#ifndef TXREQUEST64_H
#define TXREQUEST64_H

#include "../xbeepacket.h"
#include <QObject>

namespace QtXBee {
namespace WPAN {


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
