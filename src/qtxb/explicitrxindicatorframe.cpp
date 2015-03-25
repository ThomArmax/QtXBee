#include "explicitrxindicatorframe.h"

ExplicitRxIndicatorFrame::ExplicitRxIndicatorFrame(QObject *parent) :
    DigiMeshFrame(parent)
{
}
void ExplicitRxIndicatorFrame::readPacket(QByteArray rx){
    Q_UNUSED(rx)
}
