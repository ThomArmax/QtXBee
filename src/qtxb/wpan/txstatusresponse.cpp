#include "txstatusresponse.h"
#include <QDebug>

namespace QtXBee {
namespace WPAN {

TXStatusResponse::TXStatusResponse(QObject *parent) :
    XBeePacket(parent)
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
    return QString();
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


}} // END namepsace
