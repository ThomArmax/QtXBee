#include "rxindicator.h"
#include "digimeshpacket.h"
#include <QDebug>

RXIndicator::RXIndicator(QObject *parent) :
    DigiMeshPacket(parent)
{
}
void RXIndicator::setSrcAddr64(QByteArray sa64) {
    m_srcAddr64.clear();
    m_srcAddr64.append(sa64);
}
void RXIndicator::setSrcAddr16(QByteArray sa16) {
    m_srcAddr16.clear();
    m_srcAddr16.append(sa16);
}
void RXIndicator::setData(QByteArray d) {
    m_data.clear();
    m_data.append(d);
}
QByteArray RXIndicator::srcAddr64() const {
    return m_srcAddr64;
}
QByteArray RXIndicator::srcAddr16() const {
    return m_srcAddr16;
}
void RXIndicator::setReceiveOptions(unsigned ro) {
    m_receiveOptions = ro;
}
unsigned RXIndicator::receiveOptions() const {
    return m_receiveOptions;
}
QByteArray RXIndicator::data() const {
    return m_data;
}
void RXIndicator::readPacket(QByteArray rx) {

    m_packet.clear();
    m_packet.append(rx);
    setStartDelimiter(rx.at(0));
    setLength(rx.at(2));
    if(rx.size() == rx.at(2)+4 && rx.size() > 15) {
        setFrameType((APIFrameType)rx.at(3));
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
        qDebug()<< m_packet.toHex();
        m_packet.clear();
    }
}
