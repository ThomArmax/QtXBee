#include "explicitadressingcommand.h"
#include "transmitrequest.h"

namespace QtXBee {

ExplicitAdressingCommand::ExplicitAdressingCommand(QObject *parent) :
    TransmitRequest(parent)
{
    setFrameType(XBeePacket::ZBExplicitTxRequest);
}

} // END namepsace
