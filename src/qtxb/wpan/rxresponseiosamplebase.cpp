#include "rxresponseiosamplebase.h"

namespace QtXBee {
namespace WPAN {

RxResponseIoSampleBase::RxResponseIoSampleBase(QObject *parent) :
    RxBaseResponse(parent),
    m_samplesCount(0),
    m_channelIndicator(0)
{
}

RxResponseIoSampleBase::~RxResponseIoSampleBase()
{
}

void RxResponseIoSampleBase::clear()
{
    RxBaseResponse::clear();
    m_samplesCount = 0;
    m_channelIndicator = 0;
}

bool RxResponseIoSampleBase::setPacket(const QByteArray &packet)
{
    if(RxBaseResponse::setPacket(packet)) {

    }
    return false;
}

QString RxResponseIoSampleBase::toString()
{
    return QString();
}

}} // END namespace
