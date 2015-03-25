#include "remoteatcommandresponseframe.h"
#include "digimeshframe.h"

RemoteATCommandResponseFrame::RemoteATCommandResponseFrame(QObject *parent) :
    DigiMeshFrameResponse(parent)
{
    setFrameType(DigiMeshFrame::RemoteATCommandResponseFrame);
}

RemoteATCommandResponseFrame::RemoteATCommandResponseFrame(const QByteArray &data, QObject *parent) :
    DigiMeshFrameResponse(parent)
{
    setFrameType(DigiMeshFrame::RemoteATCommandResponseFrame);
    setPacket(data);
}

bool RemoteATCommandResponseFrame::setPacket(const QByteArray &data)
{
    Q_UNUSED(data);
    return false;
}
