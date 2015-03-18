#include "atcommandresponse.h"
#include <QDebug>

ATCommandResponse::ATCommandResponse(QObject *parent) :
    DigiMeshPacketResponse(parent)
{
}

ATCommandResponse::ATCommandResponse(const QByteArray &data, QObject *parent)  :
    DigiMeshPacketResponse(data, parent)
{
    setPacket(data);
}

bool ATCommandResponse::setPacket(const QByteArray &packet)
Q_DECL_OVERRIDE
{
    bool bRet = false;
    m_packet.clear();
    m_packet.append(packet);
    setStartDelimiter(packet.at(0));
    setLength(packet.at(2) + (packet.at(1)<<8));
    if(packet.size() == packet.at(2)+4) {
        setFrameType((APIFrameType)(packet.at(3)&0xFF));
        setFrameId(packet.at(4));
        setATCommand(QByteArray().append(packet.at(5)).append(packet.at(6)));
        setCommandStatus(packet.at(7));
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

void ATCommandResponse::setCommandStatus(unsigned cs){
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

    m_atCommand = (ATCommand::ATCommandType) ( ( (at.at(0)&0xFF)<<8) + at.at(1) );
}

ATCommand::ATCommandType ATCommandResponse::atCommand() const {
    return m_atCommand;
}

unsigned ATCommandResponse::commandStatus() const{
    return m_commandStatus;
}

QString ATCommandResponse::toString() {
    QString str;
    str.append(QString("Packet %1\n").arg(QString(packet().toHex())));
    str.append(QString("Frame type : %1 (0x%2)\n").arg(frameTypeToString(frameType())).arg(QString::number(frameType(), 16)));
    str.append(QString("AT command : %1 (0x%2)\n").arg(ATCommand::atCommandToString(m_atCommand)).arg(QString::number(m_atCommand, 16)));
    str.append(QString("Start delimiter : 0x%1\n").arg(QString::number(startDelimiter(), 16)));
    str.append(QString("Length : %1 bytes\n").arg(m_length));
    str.append(QString("Data : 0x%1 (%2)\n").arg(QString(m_data.toHex())).arg(QString(m_data)));
    str.append(QString("Checksum : %1").arg(checksum()));

    return str;
}
