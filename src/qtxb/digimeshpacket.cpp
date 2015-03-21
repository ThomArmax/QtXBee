#include "digimeshpacket.h"

/**
 * @brief DigiMeshPacket's constructor
 * @param parent
 */
DigiMeshPacket::DigiMeshPacket(QObject *parent) :
    QObject(parent),
    m_startDelimiter(0x7E),
    m_length(-1),
    m_frameType(UndefinedFrame),
    m_frameId(-1),
    m_checksum(-1)
{
}

/**
 * @brief Sets the frame's start delimiter.
 * By default the start delemiter is set to 0x7E
 * @sa DigiMeshPacket::startDelimiter()
 * @param sd
 */
void DigiMeshPacket::setStartDelimiter(unsigned sd) {
    m_startDelimiter = sd;
}

/**
 * @brief Sets the frame's length
 * @param l
 * @sa DigiMeshPacket::length()
 */
void DigiMeshPacket::setLength(unsigned l) {
    m_length = l;
}

/**
 * @brief Sets the frame's type
 * @param type
 * @sa DigiMeshPacket::frameType()
 */
void DigiMeshPacket::setFrameType(APIFrameType type) {
    m_frameType = type;
}

/**
 * @brief Sets the frame's id
 * @param id
 * @sa DigiMeshPacket::frameType()
 */
void DigiMeshPacket::setFrameId(unsigned id) {
    m_frameId = id;
}

/**
 * @brief Sets the checksum
 * @param cs
 * @sa DigiMeshPacket::checksum()
 */
void DigiMeshPacket::setChecksum(unsigned cs) {
    m_checksum = cs;
}

/**
 * @brief Returns the frame's start delimiter
 * @returns the frame's start delimiter
 * @sa DigiMeshPacket::setStartDelimiter()
 */
unsigned DigiMeshPacket::startDelimiter() const {
    return m_startDelimiter;
}

/**
 * @brief Returns the packet's length
 * @returns the packet's length
 * @sa DigiMeshPacket::setLength()
 */
u_int16_t DigiMeshPacket::length() const {
    return m_length;
}

/**
 * @brief Returns the frame's type
 * @returns the frame's type
 * @sa DigiMeshPacket::setFrameType()
 * @sa DigiMeshPacket::APIFrameType
 */
DigiMeshPacket::APIFrameType DigiMeshPacket::frameType() const {
    return m_frameType;
}

/**
 * @brief Returns the frame's id
 * @returns the frame's id
 * @sa DigiMeshPacket::setFrameId()
 */
unsigned DigiMeshPacket::frameId() const {
    return m_frameId;
}

/**
 * @brief Returns the packet's checksum
 * @returns the packet's checksum
 * @sa DigiMeshPacket::setChecksum()
 */
unsigned DigiMeshPacket::checksum() const {
    return m_checksum;
}

/**
 * @brief Computes the checksum of the given QByteArray, and set it.
 * @param array
 * @sa DigiMeshPacket::setChecksum()
 */
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

/**
 * @brief Returns the frame's packet (raw data)
 * @returns the frame's packet (raw data)
 */
QByteArray DigiMeshPacket::packet() const {
    return m_packet;
}

/**
 * @brief Assembles the packet to be able to send it.
 *
 * Overload this function to create your own packet.
 */
void DigiMeshPacket::assemblePacket() {

}

/**
 * @brief Returns a debug string containing all packet's informations.
 * @returns a debug string containing all packet's informations.
 */
QString DigiMeshPacket::toString() {
    QString str;
    str.append(QString("Packet %1\n").arg(QString(packet().toHex())));
    str.append(QString("Frame type : %1\n").arg(frameTypeToString(frameType())));
    str.append(QString("Start delimiter : 0x%1\n").arg(QString::number(startDelimiter(), 16)));
    str.append(QString("Length : %1 bytes\n").arg(m_length));
    str.append(QString("Checksum : %1").arg(checksum()));

    return str;
}

/**
 * @brief Returns the given frame type APIFrameType in a human redable string.
 * @returns the given frame type APIFrameType in a human redable string.
 * @param type
 */
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
