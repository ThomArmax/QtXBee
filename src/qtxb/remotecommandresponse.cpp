#include "remotecommandresponse.h"
#include "digimeshpacket.h"

RemoteCommandResponse::RemoteCommandResponse(QObject *parent) :
    DigiMeshPacketResponse(parent)
{
}

RemoteCommandResponse::RemoteCommandResponse(const QByteArray &data, QObject *parent) :
    DigiMeshPacketResponse(data, parent)
{

}

bool RemoteCommandResponse::setPacket(const QByteArray &data)
{
    Q_UNUSED(data);
    return false;
}
