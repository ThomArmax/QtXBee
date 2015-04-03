#include "modemstatus.h"
#include "xbeepacket.h"
#include <QDebug>

namespace QtXBee {

ModemStatus::ModemStatus(QObject *parent) :
    XBeePacket(parent)
{
    setFrameType(XBeePacket::ModemStatusResponseId);
}

ModemStatus::ModemStatus(const QByteArray &data, QObject *parent) :
    XBeePacket(parent)
{
    setFrameType(XBeePacket::ModemStatusResponseId);
    setData(data);
}

bool ModemStatus::setData(const QByteArray & data) {
    bool bRet = false;
    m_packet.clear();
    m_packet.append(data);
    setStartDelimiter(data.at(0));
    setLength(data.at(2));

    if(data.size() == data.at(2)+4) {
        setFrameType((ApiId)data.at(3));
        setStatus(data.at(4));
        setChecksum(data.at(5));
        bRet = true;
    }
    else {
        qDebug()<< Q_FUNC_INFO << "Invalid Packet !" << m_packet.toHex();
        m_packet.clear();
    }

    return bRet;
}

void ModemStatus::setStatus(unsigned s){
    m_status = s;
}

unsigned ModemStatus::status() const{
    return m_status;
}

} // END namepsace
