#include "remoteatcommandresponse.h"
#include "xbeepacket.h"

namespace QtXBee {

RemoteATCommandResponse::RemoteATCommandResponse(QObject *parent) :
    XBeeResponse(parent)
{
    setFrameType(XBeePacket::RemoteATCommandResponseId);
}

RemoteATCommandResponse::RemoteATCommandResponse(const QByteArray &data, QObject *parent) :
    XBeeResponse(parent)
{
    setFrameType(XBeePacket::RemoteATCommandResponseId);
    setPacket(data);
}

void RemoteATCommandResponse::clear() {
    XBeeResponse::clear();
    m_sourceAddress     = 0;
    m_networkAddress    = 0;
    m_atCommand         = ATCommand::Command_Undefined;
    m_commandData.clear();
}

bool RemoteATCommandResponse::parseApiSpecificData(const QByteArray &data)
Q_DECL_OVERRIDE
{
    if(data.size() < 13) {
        qDebug() << Q_FUNC_INFO << "bad data !";
        return false;
    }
    setFrameId(data.at(0));
    setSourceAddress(data.mid(1, 8).toHex().toULong());
    setNetworkAddress(data.mid(9, 1).toHex().toUInt());
    setATCommand((ATCommand::ATCommandType) data.mid(11, 1).toHex().toUInt());
    setCommandStatus((CommandStatus) data.at(13));
    if(data.size() > 14) {
        for(int i=0; i < data.size()-1; i++) {
            m_commandData.append(data.at(i));
        }
    }

    return true;
}

QString RemoteATCommandResponse::toString()
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
void RemoteATCommandResponse::setSourceAddress(const quint64 source) {
    m_sourceAddress = source;
}

void RemoteATCommandResponse::setNetworkAddress(const quint32 network) {
    m_networkAddress = network;
}

void RemoteATCommandResponse::setATCommand(const ATCommand::ATCommandType command) {
    m_atCommand = command;
}

void RemoteATCommandResponse::setCommandData(const QByteArray & data) {
    m_commandData = data;
}

// Getters
quint64 RemoteATCommandResponse::sourceAddress() const {
    return m_sourceAddress;
}

quint16 RemoteATCommandResponse::networkAddress() const {
    return m_networkAddress;
}

ATCommand::ATCommandType RemoteATCommandResponse::atCommand() const {
    return m_atCommand;
}

QByteArray RemoteATCommandResponse::commandData() const {
    return m_commandData;
}

} // END namepsace
