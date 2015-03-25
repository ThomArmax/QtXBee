#include "atcommandframe.h"
#include <QDebug>

/**
 * @brief ATCommandFrame's constructor
 * @param parent
 */
ATCommandFrame::ATCommandFrame(QObject *parent) :
    DigiMeshFrame(parent)
{
    setFrameType(DigiMeshFrame::ATCommandFrame);
    setFrameId(0x01);
}

/**
 * @brief Sets the AT Command
 * @param command
 */
void ATCommandFrame::setCommand(const ATCommand command) {
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
void ATCommandFrame::setCommand(const QString &command) {
    m_command.clear();
    m_command.append(command.at(0));
    m_command.append(command.at(1));
}

/**
 * @brief Sets command's parameter
 * @param param
 */
void ATCommandFrame::setParameter(const QByteArray &param) {
    m_parameter.clear();
    m_parameter.append(param);
}

/**
 * @brief Returns the AT Command
 * @return the AT Command
 */
QByteArray ATCommandFrame::command() const {
    return m_command;
}

/**
 * @brief Returns the command's parameter
 * @return the command's parameter
 */
QByteArray ATCommandFrame::parameter() const {
    return m_parameter;
}

void ATCommandFrame::assemblePacket() {
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
 * @brief Returns the given ATCommandFrame::ATCommand into QString
 * @param command the ATCommand to be converted into QString
 * @return the given ATCommand into QString
 */
QString ATCommandFrame::atCommandToString(const ATCommand command)
{
    QString at(atCommandToByteArray(command));
    return at;
}

/**
 * @brief Returns the given ATCommandFrame::ATCommand into QByteArray
 * @param command the ATCommand to be converted into QByteArray
 * @return the given ATCommand into QByteArray
 */
QByteArray ATCommandFrame::atCommandToByteArray(const ATCommand command)
{
    QByteArray at;
    at.append((command>>8)&0xFF);
    at.append(command&0xFF);
    return at;
}

/**
 * @brief Returns the ATCommandFrame::ATCommand corresponding to the given QByteArray
 * @param command
 * @return the ATCommandFrame::ATCommand corresponding to the given QByteArray.
 */
ATCommandFrame::ATCommand ATCommandFrame::atCommandFromByteArray(const QByteArray &command)
{
    ATCommandFrame::ATCommand at;
    at = (ATCommandFrame::ATCommand) ( ( (command.at(0)&0xFF)<<8) + command.at(1) );

    return at;
}
