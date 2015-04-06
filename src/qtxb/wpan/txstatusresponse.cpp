#include "txstatusresponse.h"
#include <QDebug>

namespace QtXBee {
namespace WPAN {

TXStatusResponse::TXStatusResponse(QObject *parent) :
    XBeePacket(parent),
    m_status(Unknown)
{
    setFrameType(TXStatusResponseId);
}

TXStatusResponse::~TXStatusResponse()
{

}

void TXStatusResponse::clear()
Q_DECL_OVERRIDE
{

}

QString TXStatusResponse::toString()
Q_DECL_OVERRIDE
{
    QString str;
    str.append(QString("Raw packet      : 0x%1\n").arg(QString(packet().toHex())));
    str.append(QString("Frame id        : %1 (0x%2)\n").arg(frameId(), 0, 16).arg(frameId(), 0, 16));
    str.append(QString("Frame type      : %1 (0x%2)\n").arg(frameTypeToString(frameType())).arg(QString::number(frameType(), 16)));
    str.append(QString("Start delimiter : 0x%1\n").arg(QString::number(startDelimiter(), 16)));
    str.append(QString("Length          : %1 bytes\n").arg(m_length));
    str.append(QString("Checksum        : %1\n").arg(checksum()));
    str.append(QString("Status          : %1 (0x%2)\n").arg(statusToString(m_status)).arg(m_status, 0, 16));

    return str;
}

bool TXStatusResponse::setPacket(const QByteArray &packet)
Q_DECL_OVERRIDE
{
    m_packet.clear();
    m_packet.append(packet);
    quint8 apiId = 0;

    if(packet.size() < 6) {
        qDebug() << Q_FUNC_INFO << "bad packet !";
        return false;
    }

    setStartDelimiter(packet.at(0));
    setLength((unsigned char)packet.at(2) + ((unsigned char)packet.at(1)<<8));
    apiId = packet.at(3);
    if(apiId != m_frameType) {
        qDebug() << Q_FUNC_INFO << "Bad frame type!";
        return false;
    }
    setFrameId(packet.at(4));
    setStatus((Status)packet.at(5));
    setChecksum(packet.at(6));

    return true;
}

void TXStatusResponse::setStatus(const Status status)
{
    m_status = status;
}

TXStatusResponse::Status TXStatusResponse::status() const
{
    return m_status;
}

QString TXStatusResponse::statusToString(const Status status)
{
    QString str = "Unknown";

    switch(status) {
    case Success    : str = "Success"               ; break;
    case NoACK      : str = "No Acknowledgement)"   ; break;
    case CCAFailure : str = "CCA Failure"           ; break;
    case Purged     : str = "Purged"                ; break;
    default         : break;
    }

    return str;
}


}} // END namepsace
