#include "explicitadressingcommand.h"
#include "transmitrequest.h"

namespace QtXBee {
namespace ZigBee {

ZBExplicitTxRequest::ZBExplicitTxRequest(QObject *parent) :
    ZBTxRequest(parent)
{
    setFrameType(XBeePacket::ZBExplicitTxRequestId);
}

} } // END namepsace
