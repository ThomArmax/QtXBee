#include "zbexplicitrxresponse.h"

namespace QtXBee {
namespace ZigBee {

ZBExplicitRxResponse::ZBExplicitRxResponse(QObject *parent) :
    XBeePacket(parent)
{
    setFrameType(XBeePacket::ZBExplicitRxResponseId);
}
void ZBExplicitRxResponse::readPacket(QByteArray rx){
    Q_UNUSED(rx)
}

} } // END namepsace
