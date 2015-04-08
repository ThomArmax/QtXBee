#include "rxresponseiosample16.h"

namespace QtXBee {
namespace WPAN {

RxResponseIoSample16::RxResponseIoSample16(QObject *parent) :
    RxResponseIoSampleBase(parent)
{
    setFrameType(RX16IOResponseId);
}

RxResponseIoSample16::~RxResponseIoSample16()
{
}

}} // END namespace
