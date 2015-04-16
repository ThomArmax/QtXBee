#include "rxresponse64.h"

#include <QDebug>

namespace QtXBee {
namespace WPAN {

RxResponse64::RxResponse64(QObject *parent) :
    RxBaseResponse(parent),
    m_sourceAddress(0)
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

bool RxResponse64::parseApiSpecificData(const QByteArray &data)
Q_DECL_OVERRIDE
{
    if(data.size() < 9) {
        qWarning() << Q_FUNC_INFO << "Invalid data, expected at least 9 bytes, got" << data.size();
        return false;
    }
    setSourceAddress(data.mid(0, 8).toHex().toULongLong(0, 16));
    setRSSI(-1*data.mid(8, 1).toHex().toInt(0, 16));
    setOptions(data.mid(9, 1).toHex().toUInt(0, 16));
    if(data.size() > 10) {
        setData(data.mid(10));
    }

    return true;
}

QString RxResponse64::toString()
Q_DECL_OVERRIDE
{
    QString str;
    str.append(QString("Raw packet      : 0x%1\n").arg(QString(packet().toHex())));
    str.append(QString("Frame id        : %1 (0x%2)\n").arg(frameId(), 0, 16).arg(frameId(), 0, 16));
    str.append(QString("Frame type      : %1 (0x%2)\n").arg(frameTypeToString(frameType())).arg(QString::number(frameType(), 16)));
    str.append(QString("Start delimiter : 0x%1\n").arg(QString::number(startDelimiter(), 16)));
    str.append(QString("Length          : %1 bytes\n").arg(length()));
    str.append(QString("Checksum        : %1\n").arg(checksum()));
    str.append(QString("Source Address  : 0x%1\n").arg(sourceAddress(), 0, 16));
    if(!data().isEmpty())
    str.append(QString("Data            : 0x%1 (0x%2)\n").arg(QString(data())).arg(QString(data().toHex())));
    else
    str.append(QString("Data            : No data\n"));
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
