#ifndef ZBEXPLICITRXRESPONSE_H
#define ZBEXPLICITRXRESPONSE_H

#include "xbeepacket.h"

namespace QtXBee {
namespace ZigBee {

class ZBExplicitRxResponse : public XBeePacket
{
    Q_OBJECT
public:
    explicit ZBExplicitRxResponse(QObject *parent = 0);
    void readPacket(QByteArray rx);
};

} } // END namepsace

#endif // ZBEXPLICITRXRESPONSE_H
