#include "explicitrxindicatorframe.h"

namespace QtXBee {

ExplicitRxIndicatorFrame::ExplicitRxIndicatorFrame(QObject *parent) :
    DigiMeshFrame(parent)
{
    setFrameType(DigiMeshFrame::ExplicitRxIndicatorFrame);
}
void ExplicitRxIndicatorFrame::readPacket(QByteArray rx){
    Q_UNUSED(rx)
}

} // END namepsace
