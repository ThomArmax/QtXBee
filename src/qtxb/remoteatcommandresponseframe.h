#ifndef REMOTECOMMANDRESPONSE_H
#define REMOTECOMMANDRESPONSE_H

#include "digimeshframeresponse.h"
#include "atcommandframe.h"

#include <QObject>
#include <QByteArray>

/**
 * @brief The RemoteCommandResponse represent the response to a RemoteCommandRequest.
 *
 * If a module receives a remote command response RF data frame in response to a RemoteCommandRequest,
 * the module will send a RemoteCommandResponse message out the UART.
 * Some commands may send back multiple frames--for example, Node Discover (ND) command.
 *
 * @sa RemoteCommandRequest
 */
class RemoteATCommandResponseFrame : public DigiMeshFrameResponse
{
    Q_OBJECT
public:
    explicit RemoteATCommandResponseFrame(QObject *parent = 0);
    RemoteATCommandResponseFrame(const QByteArray & packet, QObject *parent = 0);

    // Reimplement from DigiMeshFrame
    virtual QString toString();
    virtual void clear();
    virtual bool setPacket(const QByteArray &packet);

    // Setters
    void setSourceAddress(const quint64 source);
    void setNetworkAddress(const quint32 network);
    void setATCommand(const ATCommandFrame::ATCommand command);
    void setCommandData(const QByteArray & data);

    // Getters
    quint64 sourceAddress() const;
    quint16 networkAddress() const;
    ATCommandFrame::ATCommand atCommand() const;
    QByteArray commandData() const;

private:
    quint64 m_sourceAddress;
    quint16 m_networkAddress;
    ATCommandFrame::ATCommand m_atCommand;
    QByteArray m_commandData;
};

#endif // REMOTECOMMANDRESPONSE_H
