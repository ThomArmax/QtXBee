#include "transmitrequest.h"
#include "xbeepacket.h"

namespace QtXBee {

TransmitRequest::TransmitRequest(QObject *parent) :
    XBeePacket(parent)
{
    unsigned zero = 0x00;
    unsigned oxff = 0xFF;
    unsigned oxfe = 0xFE;
    m_destAddr16.append(oxff);
    m_destAddr16.append(oxfe);
    m_destAddr64.append(zero);
    m_destAddr64.append(zero);
    m_destAddr64.append(zero);
    m_destAddr64.append(zero);
    m_destAddr64.append(zero);
    m_destAddr64.append(zero);
    m_destAddr64.append(oxff);
    m_destAddr64.append(oxff);

    m_broadcastRadius = 1;
    m_transmitOptions = 0x00;
    setFrameType(ZBTXRequestId);
    setFrameId(0x01);
}
void TransmitRequest::setBroadcastRadius(int rad){
    m_broadcastRadius = rad;
}
void TransmitRequest::setTransmitOptions(unsigned to){
    m_transmitOptions = to;
}
void TransmitRequest::setDestAddr64(QByteArray da64){
    m_destAddr64.clear();
    m_destAddr64.append(da64);
}
void TransmitRequest::setDestAddr16(QByteArray da16){
    m_destAddr16.clear();
    m_destAddr16.append(da16);
}
void TransmitRequest::setData(QByteArray d){
    m_data.clear();
    m_data.append(d);
}
QByteArray TransmitRequest::destAddr64() const{
    return m_destAddr64;
}
QByteArray TransmitRequest::destAddr16() const{
    return m_destAddr16;
}
unsigned TransmitRequest::broadcastRadius() const{
    return m_broadcastRadius;
}
unsigned TransmitRequest::transmitOptions() const{
    return m_transmitOptions;
}
QByteArray TransmitRequest::getData() const{
    return m_data;
}
void TransmitRequest::assemblePacket(){
    m_packet.clear();
    m_packet.append(frameType());
    m_packet.append(frameId());
    m_packet.append(destAddr64());
    m_packet.append(destAddr16());
    m_packet.append(broadcastRadius());
    m_packet.append(transmitOptions());
    m_packet.append(getData());
    setLength(m_packet.size());
    createChecksum(m_packet);
    m_packet.append(checksum());
    m_packet.insert(0, startDelimiter());
    m_packet.insert(1, (length()>>8)&0xFF);
    m_packet.insert(2, length()&0xFF);
}

} // END namepsace
