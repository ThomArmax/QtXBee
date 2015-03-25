#include "remoteatcommandresponseframe.h"
#include "digimeshframe.h"

RemoteATCommandResponseFrame::RemoteATCommandResponseFrame(QObject *parent) :
    DigiMeshFrameResponse(parent)
{
}

RemoteATCommandResponseFrame::RemoteATCommandResponseFrame(const QByteArray &data, QObject *parent) :
    DigiMeshFrameResponse(parent)
{
    setPacket(data);
}

bool RemoteATCommandResponseFrame::setPacket(const QByteArray &data)
{
    Q_UNUSED(data);
    return false;
}
