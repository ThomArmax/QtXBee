#ifndef REMOTECOMMANDRESPONSE_H
#define REMOTECOMMANDRESPONSE_H

#include "digimeshframeresponse.h"

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

    virtual bool setPacket(const QByteArray &packet);
};

#endif // REMOTECOMMANDRESPONSE_H
