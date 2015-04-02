#ifndef REMOTECOMMANDRESPONSE_H
#define REMOTECOMMANDRESPONSE_H

#include "xbeeresponse.h"
#include "atcommand.h"

#include <QObject>
#include <QByteArray>

namespace QtXBee {

/**
 * @brief The RemoteCommandResponse represent the response to a RemoteCommandRequest.
 *
 * If a module receives a remote command response RF data frame in response to a RemoteCommandRequest,
 * the module will send a RemoteCommandResponse message out the UART.
 * Some commands may send back multiple frames--for example, Node Discover (ND) command.
 *
 * @sa RemoteCommandRequest
 */
class RemoteATCommandResponse : public XBeeResponse
{
    Q_OBJECT
public:
    explicit RemoteATCommandResponse(QObject *parent = 0);
    RemoteATCommandResponse(const QByteArray & packet, QObject *parent = 0);

    // Reimplement from XBeePacket
    virtual QString toString();
    virtual void clear();
    virtual bool setPacket(const QByteArray &packet);

    // Setters
    void setSourceAddress(const quint64 source);
    void setNetworkAddress(const quint32 network);
    void setATCommand(const ATCommand::ATCommandType command);
    void setCommandData(const QByteArray & data);

    // Getters
    quint64 sourceAddress() const;
    quint16 networkAddress() const;
    ATCommand::ATCommandType atCommand() const;
    QByteArray commandData() const;

private:
    quint64 m_sourceAddress;
    quint16 m_networkAddress;
    ATCommand::ATCommandType m_atCommand;
    QByteArray m_commandData;
};

} // END namepsace

#endif // REMOTECOMMANDRESPONSE_H
