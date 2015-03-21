#include "atcommandresponse.h"
#include <QDebug>

ATCommandResponse::ATCommandResponse(QObject *parent) :
    DigiMeshPacketResponse(parent),
    m_atCommand(ATCommand::Command_Undefined),
    m_commandStatus(InvalidCommand)
{
}

ATCommandResponse::ATCommandResponse(const QByteArray &data, QObject *parent)  :
    DigiMeshPacketResponse(data, parent),
    m_atCommand(ATCommand::Command_Undefined),
    m_commandStatus(InvalidCommand)
{
    setPacket(data);
}

bool ATCommandResponse::setPacket(const QByteArray &packet)
Q_DECL_OVERRIDE
{
    bool bRet = false;
    QByteArray at;
    m_packet.clear();
    m_packet.append(packet);
    setStartDelimiter(packet.at(0));
    setLength(packet.at(2) + (packet.at(1)<<8));
    if(packet.size() == packet.at(2)+4) {
        setFrameType((APIFrameType)(packet.at(3)&0xFF));
        setFrameId(packet.at(4));
        at.append(packet.at(5));
        at.append(packet.at(6));
        setATCommand(at);
        setCommandStatus((Status)packet.at(7));
        int count = 8;
        while(count < packet.size()-1) {
            m_data.append(packet.at(count));
            count++;
        }
        setChecksum(packet.at(count));
        bRet = true;
    }
    else {
        qDebug() << Q_FUNC_INFO << "Invalid Packet !" << m_packet.toHex();
        m_packet.clear();
    }

    return bRet;
}

void ATCommandResponse::setCommandStatus(Status cs){
    m_commandStatus = cs;
}

void ATCommandResponse::setATCommand(ATCommand::ATCommandType at)
{
    m_atCommand = at;
}

void ATCommandResponse::setATCommand(const QByteArray &at)
{
    if(at.isNull() || at.isEmpty() || at.size() != 2) {
        qWarning() << Q_FUNC_INFO << "invalid at command" << at;
        return;
    }

    m_atCommand = ATCommand::atCommandFromByteArray(at);
}

ATCommand::ATCommandType ATCommandResponse::atCommand() const {
    return m_atCommand;
}

unsigned ATCommandResponse::commandStatus() const {
    return m_commandStatus;
}

QString ATCommandResponse::toString() {
    QString str;
    str.append(QString("Raw packet      : 0x%1\n").arg(QString(packet().toHex())));
    str.append(QString("Frame type      : %1 (0x%2)\n").arg(frameTypeToString(frameType())).arg(QString::number(frameType(), 16)));
    str.append(QString("AT command      : %1 (0x%2)\n").arg(ATCommand::atCommandToString(m_atCommand)).arg(QString::number(m_atCommand, 16)));
    str.append(QString("Start delimiter : 0x%1\n").arg(QString::number(startDelimiter(), 16)));
    str.append(QString("Length          : %1 bytes\n").arg(m_length));
    str.append(QString("Data            : 0x%1 (%2)\n").arg(QString(m_data.toHex())).arg(QString(m_data)));
    str.append(QString("Checksum        : %1\n").arg(checksum()));
    str.append(QString("Command Status  : %1 (0x%2)").arg(statusToString(m_commandStatus)).arg(m_commandStatus,0,16));

    return str;
}

QString ATCommandResponse::statusToString(const ATCommandResponse::Status status) {
    QString st = "Unknown";
    switch(status) {
    case Ok : st = "OK"; break;
    case Error : st = "Error"; break;
    case InvalidCommand : st = "Invalid Command"; break;
    case InvalidParameter : st = "Invalid Parameter"; break;
    case TXFailure : st = "Tx Failure"; break;
    }

    return st;
}
