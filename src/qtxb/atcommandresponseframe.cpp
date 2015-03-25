#include "atcommandresponseframe.h"
#include <QDebug>

ATCommandResponseFrame::ATCommandResponseFrame(QObject *parent) :
    DigiMeshFrameResponse(parent),
    m_atCommand(ATCommandFrame::Command_Undefined)
{
    setFrameType(DigiMeshFrame::ATCommandResponseFrame);
}

ATCommandResponseFrame::ATCommandResponseFrame(const QByteArray &data, QObject *parent)  :
    DigiMeshFrameResponse(parent),
    m_atCommand(ATCommandFrame::Command_Undefined)
{
    setFrameType(DigiMeshFrame::ATCommandResponseFrame);
    setPacket(data);
}

bool ATCommandResponseFrame::setPacket(const QByteArray &packet)
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
        setCommandStatus((CommandStatus)packet.at(7));
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

void ATCommandResponseFrame::setATCommand(ATCommandFrame::ATCommand at)
{
    m_atCommand = at;
}

void ATCommandResponseFrame::setATCommand(const QByteArray &at)
{
    if(at.isNull() || at.isEmpty() || at.size() != 2) {
        qWarning() << Q_FUNC_INFO << "invalid at command" << at;
        return;
    }

    m_atCommand = ATCommandFrame::atCommandFromByteArray(at);
}

ATCommandFrame::ATCommand ATCommandResponseFrame::atCommand() const {
    return m_atCommand;
}

QString ATCommandResponseFrame::toString() {
    QString str;
    str.append(QString("Raw packet      : 0x%1\n").arg(QString(packet().toHex())));
    str.append(QString("Frame type      : %1 (0x%2)\n").arg(frameTypeToString(frameType())).arg(QString::number(frameType(), 16)));
    str.append(QString("AT command      : %1 (0x%2)\n").arg(ATCommandFrame::atCommandToString(m_atCommand)).arg(QString::number(m_atCommand, 16)));
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
