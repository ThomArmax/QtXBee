#include "rxbaseresponse.h"

namespace QtXBee {
namespace WPAN {

RxBaseResponse::RxBaseResponse(QObject *parent) :
    XBeeResponse(parent),
    m_rssi(-1),
    m_options(0)
{
}

RxBaseResponse::~RxBaseResponse()
{
}

void RxBaseResponse::clear()
Q_DECL_OVERRIDE
{
    XBeeResponse::clear();
    m_rssi = -1;
    m_options = 0;
}

QString RxBaseResponse::toString()
Q_DECL_OVERRIDE
{
    return QString();
}

void RxBaseResponse::setRSSI(const qint8 rssi)
{
    m_rssi = rssi;
}

qint8 RxBaseResponse::rssi() const
{
    return m_rssi;
}

void RxBaseResponse::setOptions(const quint8 options)
{
    m_options = options;
}

quint8 RxBaseResponse::options() const
{
    return m_options;
}

}} // END namespace
