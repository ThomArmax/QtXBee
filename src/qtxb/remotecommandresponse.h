#ifndef REMOTECOMMANDRESPONSE_H
#define REMOTECOMMANDRESPONSE_H

#include "digimeshpacketresponse.h"

#include <QObject>
#include <QByteArray>

class RemoteCommandResponse : public DigiMeshPacketResponse
{
    Q_OBJECT
public:
    explicit RemoteCommandResponse(QObject *parent = 0);
    RemoteCommandResponse(const QByteArray & packet, QObject *parent = 0);

    virtual bool setPacket(const QByteArray &packet);
};

#endif // REMOTECOMMANDRESPONSE_H
