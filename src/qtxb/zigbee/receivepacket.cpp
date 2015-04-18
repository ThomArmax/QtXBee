#include "receivepacket.h"
#include "xbeepacket.h"
#include <QDebug>

namespace QtXBee {
namespace ZigBee {

ReceivePacket::ReceivePacket(QObject *parent) :
    XBeePacket(parent)
{
    setFrameType(XBeePacket::ZBRXResponseId);
}
void ReceivePacket::setSrcAddr64(QByteArray sa64) {
    m_srcAddr64.clear();
    m_srcAddr64.append(sa64);
}
void ReceivePacket::setSrcAddr16(QByteArray sa16) {
    m_srcAddr16.clear();
    m_srcAddr16.append(sa16);
}
void ReceivePacket::setData(QByteArray d) {
    m_data.clear();
    m_data.append(d);
}
QByteArray ReceivePacket::srcAddr64() const {
    return m_srcAddr64;
}
QByteArray ReceivePacket::srcAddr16() const {
    return m_srcAddr16;
}
void ReceivePacket::setReceiveOptions(unsigned ro) {
    m_receiveOptions = ro;
}
unsigned ReceivePacket::receiveOptions() const {
    return m_receiveOptions;
}
QByteArray ReceivePacket::data() const {
    return m_data;
}
void ReceivePacket::readPacket(QByteArray rx) {
    setPacket(rx);
    setStartDelimiter(rx.at(0));
    setLength(rx.at(2));
    if(rx.size() == rx.at(2)+4 && rx.size() > 15) {
        setFrameType((ApiId)rx.at(3));
        m_srcAddr64.append(rx.at(4));
        m_srcAddr64.append(rx.at(5));
        m_srcAddr64.append(rx.at(6));
        m_srcAddr64.append(rx.at(7));
        m_srcAddr64.append(rx.at(8));
        m_srcAddr64.append(rx.at(9));
        m_srcAddr64.append(rx.at(10));
        m_srcAddr64.append(rx.at(11));
        m_srcAddr16.append(rx.at(12));
        m_srcAddr16.append(rx.at(13));
        setReceiveOptions(rx.at(14));
        int count = 15;
        while(count < rx.size()-1) {
            m_data.append(rx.at(count));
            count++;
        }
        setChecksum(rx.at(count));
    }else{

        qDebug()<< "Invalid Packet Received!";
        qDebug()<< rx.toHex();
        clear();
    }
}

} } // END namepsace
