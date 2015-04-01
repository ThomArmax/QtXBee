#include "digimeshframe.h"
#include <QDebug>

/**
 * @brief DigiMeshFrame's constructor
 * @param parent
 */
DigiMeshFrame::DigiMeshFrame(QObject *parent) :
    QObject(parent),
    m_startDelimiter(0x7E),
    m_length(0),
    m_frameType(UndefinedFrame),
    m_frameId(-1),
    m_checksum(-1)
{
}

/**
 * @brief Sets the frame's start delimiter.
 * By default the start delemiter is set to 0x7E
 * @sa DigiMeshFrame::startDelimiter()
 * @param sd
 */
void DigiMeshFrame::setStartDelimiter(unsigned sd) {
    m_startDelimiter = sd;
}

/**
 * @brief Sets the frame's length
 * @param l
 * @sa DigiMeshFrame::length()
 */
void DigiMeshFrame::setLength(unsigned l) {
    m_length = l;
}

/**
 * @brief Sets the frame's type
 * @param type
 * @sa DigiMeshFrame::frameType()
 */
void DigiMeshFrame::setFrameType(APIFrameType type) {
    m_frameType = type;
}

/**
 * @brief Sets the frame's id
 * @param id
 * @sa DigiMeshFrame::frameType()
 */
void DigiMeshFrame::setFrameId(unsigned id) {
    m_frameId = id;
}

/**
 * @brief Sets the checksum
 * @param cs
 * @sa DigiMeshFrame::checksum()
 */
void DigiMeshFrame::setChecksum(unsigned cs) {
    m_checksum = cs;
}

/**
 * @brief Returns the frame's start delimiter
 * @returns the frame's start delimiter
 * @sa DigiMeshFrame::setStartDelimiter()
 */
unsigned DigiMeshFrame::startDelimiter() const {
    return m_startDelimiter;
}

/**
 * @brief Returns the frame-specific data length (Number of bytes between the length and the checksum)
 * @returns the packet's length
 * @sa DigiMeshFrame::setLength()
 */
u_int16_t DigiMeshFrame::length() const {
    return m_length;
}

/**
 * @brief Returns the frame's type
 * @returns the frame's type
 * @sa DigiMeshFrame::setFrameType()
 * @sa DigiMeshFrame::APIFrameType
 */
DigiMeshFrame::APIFrameType DigiMeshFrame::frameType() const {
    return m_frameType;
}

/**
 * @brief Returns the frame's id
 * @returns the frame's id
 * @sa DigiMeshFrame::setFrameId()
 */
unsigned DigiMeshFrame::frameId() const {
    return m_frameId;
}

/**
 * @brief Returns the packet's checksum
 * @returns the packet's checksum
 * @sa DigiMeshFrame::setChecksum()
 */
unsigned DigiMeshFrame::checksum() const {
    return m_checksum;
}

/**
 * @brief Computes the checksum of the given QByteArray, and set it.
 * @param array
 * @sa DigiMeshFrame::setChecksum()
 * @sa DigiMeshFrame::checksum()
 */
void DigiMeshFrame::createChecksum(QByteArray array) {
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
QByteArray DigiMeshFrame::packet() const {
    return m_packet;
}

bool DigiMeshFrame::setPacket(const QByteArray &packet) {
    m_packet = packet;
    assemblePacket();
    return true;
}

/**
 * @brief Assembles the packet to be able to send it.
 *
 * Overload this function to create your own packet.
 * @note This method does nothing.
 */
void DigiMeshFrame::assemblePacket() {

}

void DigiMeshFrame::clear() {
    m_packet.clear();
    m_startDelimiter = 0x7E;
    m_length = 0;
    m_frameType = UndefinedFrame;
    m_frameId = -1;
    m_checksum = -1;
}

/**
 * @brief Returns a debug string containing all packet's informations.
 * @returns a debug string containing all packet's informations.
 */
QString DigiMeshFrame::toString() {
    QString str;
    str.append(QString("Raw packet      : 0x%1\n").arg(QString(packet().toHex())));
    str.append(QString("Frame id        : %1 (0x%2)\n").arg(frameId(), 0, 16).arg(frameId(), 0, 16));
    str.append(QString("Frame type      : %1 (0x%2)\n").arg(frameTypeToString(frameType())).arg(QString::number(frameType(), 16)));
    str.append(QString("Start delimiter : 0x%1\n").arg(QString::number(startDelimiter(), 16)));
    str.append(QString("Length          : %1 bytes\n").arg(m_length));
    str.append(QString("Checksum        : %1\n").arg(checksum()));

    return str;
}

/**
 * @brief Returns the given frame type APIFrameType into a human readable string
 * @returns the given frame type APIFrameType into a human readable string
 * @param type
 */
QString DigiMeshFrame::frameTypeToString(const APIFrameType type) {
    QString str;
    switch(type) {
    case ATCommandFrame                     : str = "AT Command";                           break;
    case ATCommandQueueFrame                : str = "AT Command - Queue Parameter Value";   break;
    case TXRequestFrame                     : str = "Transmit Request";                     break;
    case ExplicitAddressingCommandFrame     : str = "Explicit Addressing Command Frame";    break;
    case RemoteATCommandRequestFrame        : str = "Remote AT Command Request";            break;
    case ATCommandResponseFrame             : str = "ATCommandResponse";                    break;
    case ModemStatusFrame                   : str = "Modem Status";                         break;
    case TransmitStatusFrame                : str = "Transmit Status";                      break;
    case RXIndicatorFrame                   : str = "RXIndicator";                          break;
    case ExplicitRxIndicatorFrame           : str = "Explicit Rx Indicator";                break;
    case NodeIdentificationIndicatorFrame   : str = "Node Identification Indicator";        break;
    case RemoteATCommandResponseFrame       : str = "Remote Command Response";              break;
    default                                 : str = "Unknown";                              break;
    }
    return str;
}

void DigiMeshFrame::escapePacket()
{
    int escapeBytes = 0;
    QByteArray escapedPacked;
    int i;

    // Skip byte 0 (start delimiter)
    for (i=1; i<m_packet.size(); i++) {
        if (isSpecialByte(m_packet.at(i))) {
            qDebug() << Q_FUNC_INFO << "packet requires escaping for byte" << i << "(" <<QByteArray().append(m_packet.at(i)).toHex() << ")";
            escapeBytes++;
        }
    }

    if (escapeBytes == 0) {
        qDebug() << "No need to escape packet" << m_packet.toHex();
        return;
    }
    else {
        qDebug() << Q_FUNC_INFO << "packet need to be escaped";

        int pos = 1;

        escapedPacked.reserve(m_packet.size() + escapeBytes);
        escapedPacked[0] = startDelimiter();

        for (i = 1; i < m_packet.size(); i++) {
            if (isSpecialByte(m_packet[i])) {
                escapedPacked[pos] = StartDelimiter;
                escapedPacked[++pos] = 0x20 ^ m_packet[i];

                qDebug() << Q_FUNC_INFO << "xor'd byte is" << QString("0x%1").arg(escapedPacked[pos]);
            } else {
                escapedPacked[pos] = m_packet[i];
            }
            pos++;
        }
        qDebug() << Q_FUNC_INFO << m_packet.toHex() << "===>" << escapedPacked.toHex();
        m_packet.clear();
        m_packet = escapedPacked;
    }
}

bool DigiMeshFrame::unescapePacket()
{
    QByteArray unEscapedPacket;
    int escapeBytes = 0;
    int i = 0;
    int pos = 0;

    for(i=0; i<m_packet.size(); i++) {
        if(m_packet.at(i) == Escape) {
            escapeBytes++;
        }
    }

    if (escapeBytes == 0) {
        return true;
    }

    unEscapedPacket.reserve(m_packet.size() - escapeBytes);

    for(i = 0; i<m_packet.size(); i++) {
        if (m_packet[i] == (char)Escape) {
            // discard escape byte and un-escape following byte
            unEscapedPacket[pos] = 0x20 ^ m_packet[++i];
        } else {
            unEscapedPacket[pos] = m_packet[i];
        }
        pos++;
    }

    qDebug() << Q_FUNC_INFO << m_packet.toHex() << "====>" << unEscapedPacket.toHex();
    return true;
}

bool DigiMeshFrame::isSpecialByte(const char c)
{
    return  c == StartDelimiter ||
            c == Escape ||
            c == XON ||
            c == XOFF;
}
