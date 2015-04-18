#include "zbexplicittxrequest.h"
#include "zbtxrequest.h"

namespace QtXBee {
namespace ZigBee {

ZBExplicitTxRequest::ZBExplicitTxRequest(QObject *parent) :
    ZBTxRequest(parent)
{
    setFrameType(XBeePacket::ZBExplicitTxRequestId);
}

} } // END namepsace
