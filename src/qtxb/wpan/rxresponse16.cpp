#include "rxresponse16.h"

namespace QtXBee {
namespace WPAN {

RxResponse16::RxResponse16(QObject *parent) :
    RxBaseResponse(parent),
    m_sourceAddress(0)
{
}

RxResponse16::~RxResponse16()
{
}

void RxResponse16::clear()
Q_DECL_OVERRIDE
{
    RxBaseResponse::clear();
    m_sourceAddress = 0;
}

bool RxResponse16::setPacket(const QByteArray &packet)
Q_DECL_OVERRIDE
{
    Q_UNUSED(packet)
    return false;
}

QString RxResponse16::toString()
Q_DECL_OVERRIDE
{
    return QString();
}

void RxResponse16::setSourceAddress(const quint16 sourceAddress)
{
    m_sourceAddress = sourceAddress;
}

quint16 RxResponse16::sourceAddress() const
{
    return m_sourceAddress;
}

}} // END namespace
