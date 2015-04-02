#include "atcommandresponse.h"
#include <QDebug>

namespace QtXBee {

ATCommandResponse::ATCommandResponse(QObject *parent) :
    XBeeResponse(parent),
    m_atCommand(ATCommand::Command_Undefined)
{
    setFrameType(XBeePacket::ATCommandResponseFrame);
}

ATCommandResponse::ATCommandResponse(const QByteArray &data, QObject *parent)  :
    XBeeResponse(parent),
    m_atCommand(ATCommand::Command_Undefined)
{
    setFrameType(XBeePacket::ATCommandResponseFrame);
    setPacket(data);
}

bool ATCommandResponse::setPacket(const QByteArray &packet)
Q_DECL_OVERRIDE
{
    bool bRet = false;
    QByteArray at, lenArr;
    m_packet.clear();
    m_packet.append(packet);
    m_data.clear();
    setStartDelimiter(packet.at(0));
    if(packet.size() < 3) {
        qDebug() << Q_FUNC_INFO << "bad packet !";
        return false;
    }
    lenArr.append(packet.at(1));
    lenArr.append(packet.at(2));
    //setLength((unsigned char)packet.at(2) + ((unsigned char)packet.at(1)<<8));
    setLength(lenArr.toHex().toInt(0,16));
    if(packet.size() == packet.at(2)+4) {
        setFrameType((APIFrameType)((unsigned char)packet.at(3)&0xFF));
        setFrameId(packet.at(4));
        at.append(packet.at(5));
        at.append(packet.at(6));
        setATCommand(at);
        setCommandStatus((CommandStatus)(unsigned char)packet.at(7));
        int count = 8;
        while(count < packet.size()-1) {
            m_data.append(packet.at(count));
            count++;
        }
        setChecksum(packet.at(packet.size()-1));
        bRet = true;
    }
    else {
        qDebug() << Q_FUNC_INFO << "Invalid Packet !" << m_packet.toHex();
        m_packet.clear();
    }

    return bRet;
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

QString ATCommandResponse::toString() {
    QString str;
    str.append(QString("Raw packet      : 0x%1\n").arg(QString(packet().toHex())));
    str.append(QString("Frame id        : %1 (0x%2)\n").arg(frameId(), 0, 16).arg(frameId(), 0, 16));
    str.append(QString("Frame type      : %1 (0x%2)\n").arg(frameTypeToString(frameType())).arg(QString::number(frameType(), 16)));
    str.append(QString("AT command      : %1 (0x%2)\n").arg(ATCommand::atCommandToString(m_atCommand)).arg(QString::number(m_atCommand, 16)));
    str.append(QString("Start delimiter : 0x%1\n").arg(QString::number(startDelimiter(), 16)));
    str.append(QString("Length          : %1 bytes\n").arg(m_length));
    if(!m_data.isEmpty())
    str.append(QString("Data            : 0x%1\n").arg(QString(m_data.toHex())));
    else
    str.append(QString("Data            : No data\n"));
    str.append(QString("Checksum        : %1\n").arg(checksum()));
    str.append(QString("Command Status  : %1 (0x%2)").arg(statusToString(m_status)).arg(m_status,0,16));

    return str;
}

} // END namepsace
