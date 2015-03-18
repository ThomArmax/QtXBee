#include "atcommand.h"
#include "digimeshpacket.h"
#include <QDebug>

ATCommand::ATCommand(QObject *parent) :
    DigiMeshPacket(parent)
{
    setFrameType(DigiMeshPacket::ATCommandFrame);
    setFrameId(0x01);
}

void ATCommand::setCommand(const ATCommandType command) {
    int cmdMSB = (command>>8) & 0xFF;
    int cmdLSB = command & 0xFF;
    m_command.clear();
    m_command.append(cmdMSB);
    m_command.append(cmdLSB);
}

void ATCommand::setCommand(const QString &command) {
    m_command.clear();
    m_command.append(command.at(0));
    m_command.append(command.at(1));
}

void ATCommand::setParameter(const QByteArray &array) {
    m_parameter.clear();
    m_parameter.append(array);
}

QByteArray ATCommand::command() const {
    return m_command;
}

QByteArray ATCommand::parameter() const {
    return m_parameter;
}

void ATCommand::assemblePacket() {
    m_packet.clear();
    m_packet.append(frameType());
    m_packet.append(frameId());
    m_packet.append(command());
    m_packet.append(parameter());
    setLength(m_packet.size());
    createChecksum(m_packet);
    m_packet.append(checksum());
    m_packet.insert(0, startDelimiter());
    m_packet.insert(1, (length()>>8)&0xFF);
    m_packet.insert(2, length()&0xFF);
}

QString ATCommand::atCommandToString(const ATCommandType command)
{
    QString at(atCommandToByteArray(command));
    return at;
}

QByteArray ATCommand::atCommandToByteArray(const ATCommandType command)
{
    QByteArray at;
    at.append((command>>8)&0xFF);
    at.append(command&0xFF);
    return at;
}

ATCommand::ATCommandType ATCommand::atCommandFromByteArray(const QByteArray &command)
{
    ATCommand::ATCommandType at;
    at = (ATCommand::ATCommandType) ( ( (command.at(0)&0xFF)<<8) + command.at(1) );

    return at;
}
