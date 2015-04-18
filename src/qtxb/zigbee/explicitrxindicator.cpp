#include "explicitrxindicator.h"

namespace QtXBee {
namespace ZigBee {

ExplicitRxIndicator::ExplicitRxIndicator(QObject *parent) :
    XBeePacket(parent)
{
    setFrameType(XBeePacket::ZBExplicitRxResponseId);
}
void ExplicitRxIndicator::readPacket(QByteArray rx){
    Q_UNUSED(rx)
}

} } // END namepsace
