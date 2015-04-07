#include "rxresponse64.h"

namespace QtXBee {
namespace WPAN {

RxResponse64::RxResponse64(QObject *parent) :
    RxBaseResponse(parent)
{
    setFrameType(RX64ResponseId);
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
    QString str;
    str.append(QString("Raw packet      : 0x%1\n").arg(QString(packet().toHex())));
    str.append(QString("Frame id        : %1 (0x%2)\n").arg(frameId(), 0, 16).arg(frameId(), 0, 16));
    str.append(QString("Frame type      : %1 (0x%2)\n").arg(frameTypeToString(frameType())).arg(QString::number(frameType(), 16)));
    str.append(QString("Start delimiter : 0x%1\n").arg(QString::number(startDelimiter(), 16)));
    str.append(QString("Length          : %1 bytes\n").arg(m_length));
    str.append(QString("Checksum        : %1\n").arg(checksum()));
    str.append(QString("Source Address  : 0x%1\n").arg(sourceAddress(), 0, 16));
    return str;
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
