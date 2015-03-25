#include "atcommandframe.h"
#include "atcommandqueueparamframe.h"

ATCommandQueueParamFrame::ATCommandQueueParamFrame(QObject *parent) :
    ATCommandFrame(parent)
{
    setFrameType(ATCommandQueueFrame);
    setFrameId(0x00);
}
