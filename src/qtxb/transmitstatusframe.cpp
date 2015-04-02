#include "transmitstatusframe.h"
#include "digimeshframe.h"
#include <QDebug>

namespace QtXBee {

TransmitStatusFrame::TransmitStatusFrame(QObject *parent) :
    DigiMeshFrame(parent)
{
    setFrameType(DigiMeshFrame::TransmitStatusFrame);
}
void TransmitStatusFrame::readPacket(QByteArray rx){
    m_packet.clear();
    m_packet.append(rx);
    setStartDelimiter(rx.at(0));
    setLength(rx.at(2));
    if(rx.size() == rx.at(2)+4){
        setFrameType((APIFrameType)rx.at(3));
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
void TransmitStatusFrame:: setDeliveryStatus(unsigned ds){
    m_deliveryStatus = ds;
}
void TransmitStatusFrame:: setTransmitRetryCount(unsigned trc){
    m_transmitRetryCount = trc;
}
void TransmitStatusFrame:: setDiscoveryStatus(unsigned ds){
    m_discoveryStatus = ds;
}
unsigned TransmitStatusFrame:: deliveryStatus() const{
    return m_deliveryStatus;
}
unsigned TransmitStatusFrame:: transmitRetryCount() const{
    return m_transmitRetryCount;
}
unsigned TransmitStatusFrame:: discoveryStatus() const{
    return m_discoveryStatus;
}
QByteArray TransmitStatusFrame:: reserved() const{
    return m_reserved;
}

} // END namepsace
