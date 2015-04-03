#include "txrequest64.h"

namespace QtXBee {
namespace WPAN {


TXRequest64::TXRequest64(QObject *parent) : XBeePacket(parent)
{
    setFrameType(TXRequest64Id);
}

TXRequest64::~TXRequest64()
{

}

}} // END namespace
