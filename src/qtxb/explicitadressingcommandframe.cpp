#include "explicitadressingcommandframe.h"
#include "transmitrequestframe.h"

namespace QtXBee {

ExplicitAdressingCommandFrame::ExplicitAdressingCommandFrame(QObject *parent) :
    TransmitRequestFrame(parent)
{
    setFrameType(DigiMeshFrame::ExplicitAddressingCommandFrame);
}

} // END namepsace
