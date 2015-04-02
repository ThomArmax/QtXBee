#ifndef EXPLICITRXINDICATOR_H
#define EXPLICITRXINDICATOR_H

#include "xbeepacket.h"

namespace QtXBee {

class ExplicitRxIndicator : public XBeePacket
{
    Q_OBJECT
public:
    explicit ExplicitRxIndicator(QObject *parent = 0);
    void readPacket(QByteArray rx);
};

} // END namepsace

#endif // EXPLICITRXINDICATOR_H
