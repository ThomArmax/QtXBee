#include "remoteatcommandrequestframe.h"

/**
 * @brief RemoteATCommandRequestFrame's constructor
 * @param parent parent object
 */
RemoteATCommandRequestFrame::RemoteATCommandRequestFrame(QObject *parent) :
    DigiMeshFrame(parent),
    m_destinationAddress(0),
    m_networkAddress(0),
    m_options(0),
    m_atCommand(ATCommandFrame::Command_Undefined),
    m_commandParameter(0)
{
    setFrameType(DigiMeshFrame::RemoteATCommandRequestFrame);
}

// Reimplemented from DigiMeshFrame
void RemoteATCommandRequestFrame::assemblePacket() {

}

void RemoteATCommandRequestFrame::clear() {
    m_destinationAddress = 0;
    m_networkAddress = 0;
    m_options = 0;
    m_atCommand = ATCommandFrame::Command_Undefined;
    m_commandParameter = 0;
}

QString RemoteATCommandRequestFrame::toString() {
    return QString();
}

// Setters
/**
 * @brief Sets the address of the destination device
 *
 * The following addresses are also supported:
 * - 0x0000000000000000 - Reserved 64-bit address for the coordinator
 * - 0x000000000000FFFF - Broadcast address
 * @param dest
 */
void RemoteATCommandRequestFrame::setDestinationAddress(const quint64 dest) {
    m_destinationAddress = dest;
}

/**
 * @brief Sets the 16-bit address of the destination device, if known.
 *
 * Set to 0xFFFE if the address is unknown, or if sending a broadcast.
 * @param network
 */
void RemoteATCommandRequestFrame::setNetworkAddress(const quint32 network) {
    m_networkAddress = network;
}

/**
 * @brief Sets the remote command options.
 */
void RemoteATCommandRequestFrame::setCommandOptions(const RemoteCommandOptions options) {
    m_options = options;
}

/**
 * @brief Sets the command to be performed on the remote device
 * @param command
 */
void RemoteATCommandRequestFrame::setATCommand(const ATCommandFrame::ATCommand command) {
    m_atCommand = command;
}

/**
 * @brief Sets the command's parameter.
 *
 * If present, indicates the requested parameter value to set the given register.
 * If no characters present, the register is queried.
 * @param parameter
 */
void RemoteATCommandRequestFrame::setCommandParameter(const quint8 parameter) {
   m_commandParameter = parameter;
}

// Getters
quint64 RemoteATCommandRequestFrame::destinationAddress() const {
    return m_destinationAddress;
}

quint16 RemoteATCommandRequestFrame::networkAddress() const {
    return m_networkAddress;
}

ATCommandFrame::ATCommand RemoteATCommandRequestFrame::atCommand() const {
    return m_atCommand;
}

quint8 RemoteATCommandRequestFrame::commandParameter() {
    return m_commandParameter;
}
