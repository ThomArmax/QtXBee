#include "atcommand.h"
#include "atcommandqueueparam.h"

ATCommandQueueParam::ATCommandQueueParam(QObject *parent) :
    ATCommand(parent)
{
    setFrameType(ATCommandQueueFrame);
    setFrameId(0x00);
}
