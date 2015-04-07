#include "rxresponse64.h"

namespace QtXBee {
namespace WPAN {

RxResponse64::RxResponse64(QObject *parent) :
    RxBaseResponse(parent)
{
}

RxResponse64::~RxResponse64()
{
}

void RxResponse64::clear()
Q_DECL_OVERRIDE
{
    RxBaseResponse::clear();
    m_sourceAddress = 0;
}

bool RxResponse64::setPacket(const QByteArray &packet)
Q_DECL_OVERRIDE
{
    Q_UNUSED(packet)
    return false;
}

QString RxResponse64::toString()
Q_DECL_OVERRIDE
{
    return QString();
}

void RxResponse64::setSourceAddress(const quint64 sourceAddress)
{
    m_sourceAddress = sourceAddress;
}

quint64 RxResponse64::sourceAddress() const
{
    return m_sourceAddress;
}

}} // END namespace
