#include "explicitadressingcommand.h"
#include "transmitrequest.h"

namespace QtXBee {
namespace ZigBee {

ExplicitAdressingCommand::ExplicitAdressingCommand(QObject *parent) :
    TransmitRequest(parent)
{
    setFrameType(XBeePacket::ZBExplicitTxRequest);
}

} } // END namepsace
