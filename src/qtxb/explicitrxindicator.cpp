#include "explicitrxindicator.h"

namespace QtXBee {

ExplicitRxIndicator::ExplicitRxIndicator(QObject *parent) :
    XBeePacket(parent)
{
    setFrameType(XBeePacket::ExplicitRxIndicatorFrame);
}
void ExplicitRxIndicator::readPacket(QByteArray rx){
    Q_UNUSED(rx)
}

} // END namepsace
