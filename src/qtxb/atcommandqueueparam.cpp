#include "atcommand.h"
#include "atcommandqueueparam.h"

namespace QtXBee {

ATCommandQueueParam::ATCommandQueueParam(QObject *parent) :
    ATCommand(parent)
{
    setFrameType(ATCommandQueueFrame);
    setFrameId(0x00);
}

} // END namepsace
