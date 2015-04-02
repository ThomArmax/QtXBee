#include "remoteatcommandresponseframe.h"
#include "digimeshframe.h"

namespace QtXBee {

RemoteATCommandResponseFrame::RemoteATCommandResponseFrame(QObject *parent) :
    DigiMeshFrameResponse(parent)
{
    setFrameType(DigiMeshFrame::RemoteATCommandResponseFrame);
}

RemoteATCommandResponseFrame::RemoteATCommandResponseFrame(const QByteArray &data, QObject *parent) :
    DigiMeshFrameResponse(parent)
{
    setFrameType(DigiMeshFrame::RemoteATCommandResponseFrame);
    setPacket(data);
}

void RemoteATCommandResponseFrame::clear() {
    DigiMeshFrameResponse::clear();
    m_sourceAddress     = 0;
    m_networkAddress    = 0;
    m_atCommand         = (ATCommandFrame::ATCommand)0;
    m_commandData.clear();
}

bool RemoteATCommandResponseFrame::setPacket(const QByteArray &packet)
Q_DECL_OVERRIDE
{
    bool bRet = false;
    m_packet.clear();
    m_packet.append(packet);
    m_data.clear();

    if(packet.size() < 18) {
        qWarning() << Q_FUNC_INFO << "Bad packet size !";
        return bRet;
    }

    setStartDelimiter(packet.at(0));
    setLength((unsigned char)packet.at(2) + ((unsigned char)packet.at(1)<<8));
    setSourceAddress(packet.mid(5, 8).toHex().toULong());
    setNetworkAddress(packet.mid(13, 1).toHex().toUInt());
    setATCommand((ATCommandFrame::ATCommand) packet.mid(15, 1).toHex().toUInt());
    setCommandStatus((CommandStatus) packet.at(17));
    if(packet.size() > 18) {
        for(int i=0; i < packet.size()-1; i++) {
            m_commandData.append(packet.at(i));
        }
    }
    setChecksum(packet.at(packet.size()-1));

    return bRet;
}

QString RemoteATCommandResponseFrame::toString()
Q_DECL_OVERRIDE
{
    QString str;
    str.append(QString("Raw packet                   : 0x%1\n").arg(QString(packet().toHex())));
    str.append(QString("Start delimiter              : 0x%1\n").arg(QString::number(startDelimiter(), 16)));
    str.append(QString("Frame type                   : %1 (0x%2)\n").arg(frameTypeToString(frameType())).arg(QString::number(frameType(), 16)));
    str.append(QString("Length                       : %1 bytes\n").arg(m_length));
    if(!m_data.isEmpty())
    str.append(QString("Data                         : 0x%1\n").arg(QString(m_data.toHex())));
    else
    str.append(QString("Data                         : No data\n"));
    str.append(QString("Source Address 64bits        : 0x%1\n").arg(m_sourceAddress, 0, 16));
    str.append(QString("Source Address 16bits        : 0x%1\n").arg(m_networkAddress, 0, 16));
    str.append(QString("AT Command                   : 0x%1\n").arg(m_atCommand, 0,16));
    str.append(QString("Command Status               : %1 (0x%2)\n").arg(statusToString(m_status)).arg(m_status, 0, 16));
    str.append(QString("Command Data                 : 0x%1\n").arg(QString(m_data.toHex())));
    str.append(QString("Checksum                     : %1\n").arg(checksum()));

    return  str;
}

// Setters
void RemoteATCommandResponseFrame::setSourceAddress(const quint64 source) {
    m_sourceAddress = source;
}

void RemoteATCommandResponseFrame::setNetworkAddress(const quint32 network) {
    m_networkAddress = network;
}

void RemoteATCommandResponseFrame::setATCommand(const ATCommandFrame::ATCommand command) {
    m_atCommand = command;
}

void RemoteATCommandResponseFrame::setCommandData(const QByteArray & data) {
    m_commandData = data;
}

// Getters
quint64 RemoteATCommandResponseFrame::sourceAddress() const {
    return m_sourceAddress;
}

quint16 RemoteATCommandResponseFrame::networkAddress() const {
    return m_networkAddress;
}

ATCommandFrame::ATCommand RemoteATCommandResponseFrame::atCommand() const {
    return m_atCommand;
}

QByteArray RemoteATCommandResponseFrame::commandData() const {
    return m_commandData;
}

} // END namepsace
