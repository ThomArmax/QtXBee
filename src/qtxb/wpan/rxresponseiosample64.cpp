#include "rxresponseiosample64.h"

namespace QtXBee {
namespace WPAN {

RxResponseIoSample64::RxResponseIoSample64(QObject *parent) :
    RxResponseIoSampleBase(parent)
{
    setFrameType(RX64IOResponseId);
}

RxResponseIoSample64::~RxResponseIoSample64()
{

}

}} // END namespace
