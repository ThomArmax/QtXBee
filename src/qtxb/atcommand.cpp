#include "atcommand.h"
#include "digimeshpacket.h"
#include <QDebug>

/**
 * @brief ATCommand's constructor
 * @param parent
 */
ATCommand::ATCommand(QObject *parent) :
    DigiMeshPacket(parent)
{
    setFrameType(DigiMeshPacket::ATCommandFrame);
    setFrameId(0x01);
}

/**
 * @brief Sets the AT Command
 * @param command
 */
void ATCommand::setCommand(const ATCommandType command) {
    int cmdMSB = (command>>8) & 0xFF;
    int cmdLSB = command & 0xFF;
    m_command.clear();
    m_command.append(cmdMSB);
    m_command.append(cmdLSB);
}

/**
 * @brief Sets the AT Command from the given QString
 * @param command
 */
void ATCommand::setCommand(const QString &command) {
    m_command.clear();
    m_command.append(command.at(0));
    m_command.append(command.at(1));
}

/**
 * @brief Sets command's parameter
 * @param param
 */
void ATCommand::setParameter(const QByteArray &param) {
    m_parameter.clear();
    m_parameter.append(param);
}

/**
 * @brief Returns the AT Command
 * @return the AT Command
 */
QByteArray ATCommand::command() const {
    return m_command;
}

/**
 * @brief Returns the command's parameter
 * @return the command's parameter
 */
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

/**
 * @brief Returns the given ATCommand::ATCommandType into QString
 * @param command the ATCommandType to be converted into QString
 * @return the given ATCommandType into QString
 */
QString ATCommand::atCommandToString(const ATCommandType command)
{
    QString at(atCommandToByteArray(command));
    return at;
}

/**
 * @brief Returns the given ATCommand::ATCommandType into QByteArray
 * @param command the ATCommandType to be converted into QByteArray
 * @return the given ATCommandType into QByteArray
 */
QByteArray ATCommand::atCommandToByteArray(const ATCommandType command)
{
    QByteArray at;
    at.append((command>>8)&0xFF);
    at.append(command&0xFF);
    return at;
}

/**
 * @brief Returns the ATCommand::ATCommandType corresponding to the given QByteArray
 * @param command
 * @return the ATCommandType corresponding to the given QByteArray.
 */
ATCommand::ATCommandType ATCommand::atCommandFromByteArray(const QByteArray &command)
{
    ATCommand::ATCommandType at;
    at = (ATCommand::ATCommandType) ( ( (command.at(0)&0xFF)<<8) + command.at(1) );

    return at;
}
