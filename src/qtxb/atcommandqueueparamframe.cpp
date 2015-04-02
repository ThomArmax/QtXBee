#include "atcommandframe.h"
#include "atcommandqueueparamframe.h"

namespace QtXBee {

ATCommandQueueParamFrame::ATCommandQueueParamFrame(QObject *parent) :
    ATCommandFrame(parent)
{
    setFrameType(ATCommandQueueFrame);
    setFrameId(0x00);
}

} // END namepsace
