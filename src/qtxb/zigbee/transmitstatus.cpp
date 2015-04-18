#include "transmitstatus.h"
#include "xbeepacket.h"
#include <QDebug>

namespace QtXBee {
namespace ZigBee {

TransmitStatus::TransmitStatus(QObject *parent) :
    XBeePacket(parent)
{
    setFrameType(XBeePacket::ZBTXStatusResponseId);
}
void TransmitStatus::readPacket(QByteArray rx){
    m_packet.clear();
    m_packet.append(rx);
    setStartDelimiter(rx.at(0));
    setLength(rx.at(2));
    if(rx.size() == rx.at(2)+4){
        setFrameType((ApiId)rx.at(3));
        setFrameId(rx.at(4));
        m_reserved.append(rx.at(5));
        m_reserved.append(rx.at(6));
        setTransmitRetryCount(rx.at(7));
        setDeliveryStatus(rx.at(8));
        setDiscoveryStatus(rx.at(9));
        setChecksum(rx.at(10));
    }else{

        qDebug()<< "Invalid Packet Received!";
        qDebug()<< m_packet.toHex();
        m_packet.clear();
    }
}
void TransmitStatus:: setDeliveryStatus(unsigned ds){
    m_deliveryStatus = ds;
}
void TransmitStatus:: setTransmitRetryCount(unsigned trc){
    m_transmitRetryCount = trc;
}
void TransmitStatus:: setDiscoveryStatus(unsigned ds){
    m_discoveryStatus = ds;
}
unsigned TransmitStatus:: deliveryStatus() const{
    return m_deliveryStatus;
}
unsigned TransmitStatus:: transmitRetryCount() const{
    return m_transmitRetryCount;
}
unsigned TransmitStatus:: discoveryStatus() const{
    return m_discoveryStatus;
}
QByteArray TransmitStatus:: reserved() const{
    return m_reserved;
}

} } // END namepsace
