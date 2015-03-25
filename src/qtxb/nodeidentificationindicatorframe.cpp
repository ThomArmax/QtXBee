#include "nodeidentificationindicatorframe.h"

NodeIdentificationIndicatorFrame::NodeIdentificationIndicatorFrame(QObject *parent) :
    DigiMeshFrame(parent)
{
}
void NodeIdentificationIndicatorFrame::readPacket(QByteArray rx){
    Q_UNUSED(rx)
}
