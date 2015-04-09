#include "atcommandresponse.h"
#include <QDebug>

namespace QtXBee {

ATCommandResponse::ATCommandResponse(QObject *parent) :
    XBeeResponse(parent),
    m_atCommand(ATCommand::Command_Undefined)
{
    XBeePacket::setFrameType(XBeePacket::ATCommandResponseId);
}

ATCommandResponse::ATCommandResponse(const QByteArray &data, QObject *parent)  :
    XBeeResponse(parent),
    m_atCommand(ATCommand::Command_Undefined)
{
    XBeePacket::setFrameType(XBeePacket::ATCommandResponseId);
    setPacket(data);
}

bool ATCommandResponse::parseApiSpecificData(const QByteArray &data)
{
    QByteArray at;
    int i;
    if(data.size() < 3) {
        qDebug() << Q_FUNC_INFO << "bad packet";
        return false;
    }
    setFrameId(data.at(0));
    at.append(data.at(1));
    at.append(data.at(2));
    setATCommand(at);
    setCommandStatus((CommandStatus)(unsigned char)data.at(3));
    for(i=4; i<data.size();i++) {
        m_data.append(data.at(i));
    }

    return true;
}

void ATCommandResponse::setATCommand(ATCommand::ATCommandType at)
{
    m_atCommand = at;
}

void ATCommandResponse::setATCommand(const QByteArray &at)
{
    if(at.size() != 2) {
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
