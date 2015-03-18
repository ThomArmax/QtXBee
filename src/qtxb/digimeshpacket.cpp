#include "digimeshpacket.h"

DigiMeshPacket::DigiMeshPacket(QObject *parent) :
    QObject(parent),
    m_startDelimiter(0x7E),
    m_length(-1),
    m_frameType(Undefined),
    m_frameId(-1),
    m_checksum(-1)
{
}

void DigiMeshPacket::setStartDelimiter(unsigned sd) {
    m_startDelimiter = sd;
}

void DigiMeshPacket::setLength(unsigned l) {
    m_length = l;
}

void DigiMeshPacket::setFrameType(APIFrameType type) {
    m_frameType = type;
}

void DigiMeshPacket::setFrameId(unsigned id) {
    m_frameId = id;
}

void DigiMeshPacket::setChecksum(unsigned cs) {
    m_checksum = cs;
}

unsigned DigiMeshPacket::startDelimiter() const {
    return m_startDelimiter;
}

u_int16_t DigiMeshPacket::length() const {
    return m_length;
}

DigiMeshPacket::APIFrameType DigiMeshPacket::frameType() const {
    return m_frameType;
}

unsigned DigiMeshPacket::frameId() const {
    return m_frameId;
}

unsigned DigiMeshPacket::checksum() const {
    return m_checksum;
}

void DigiMeshPacket::createChecksum(QByteArray array) {
    int len = array.size();
    unsigned int sum = 0x00;
    unsigned int ff = 0xFF;
    unsigned int fe = 0xFE;
    for(int i=0;i<len;i++)
    {
        unsigned int a = array.at(i);
        if (a == (unsigned int)4294967295){
            a = ff;
        } else if (a == (unsigned int)4294967294){
            a = fe;
        }

        sum += a;
    }
    setChecksum((ff - sum) & 0x000000FF);
}

QByteArray DigiMeshPacket::packet() const {
    return m_packet;
}

void DigiMeshPacket::assemblePacket() {

}

QString DigiMeshPacket::toString() {
    QString str;
    str.append(QString("Packet %1\n").arg(QString(packet().toHex())));
    str.append(QString("Frame type : %1\n").arg(frameTypeToString(frameType())));
    str.append(QString("Start delimiter : 0x%1\n").arg(QString::number(startDelimiter(), 16)));
    str.append(QString("Length : %1 bytes\n").arg(m_length));
    str.append(QString("Checksum : %1").arg(checksum()));

    return str;
}

QString DigiMeshPacket::frameTypeToString(const APIFrameType type) {
    QString str;
    switch(type) {
    case ATCommandFrame                     : str = "ATCommand";                    break;
    case ATCommandQueueFrame                : str = "ATCommandQueue";               break;
    case TXRequestFrame                     : str = "TXRequest";                    break;
    case TXRequestExplicitFrame             : str = "TXRequestExplicit";            break;
    case RemoteCommandRequestFrame          : str = "RemoteCommandRequest";         break;
    case ATCommandResponseFrame             : str = "ATCommandResponse";            break;
    case ModemStatusFrame                   : str = "ModemStatus";                  break;
    case TransmitStatusFrame                : str = "TransmitStatus";               break;
    case RXIndicatorFrame                   : str = "RXIndicator";                  break;
    case RXIndicatorExplicitFrame           : str = "RXIndicatorExplicit";          break;
    case NodeIdentificationIndicatorFrame   : str = "NodeIdentificationIndicator";  break;
    case RemoteCommandResponseFrame         : str = "RemoteCommandResponseFrame";   break;
    default                                 : str = "Unknown";                      break;
    }
    return str;
}
