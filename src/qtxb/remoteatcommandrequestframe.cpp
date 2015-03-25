#include "remoteatcommandrequestframe.h"

RemoteATCommandRequestFrame::RemoteATCommandRequestFrame(QObject *parent) :
    DigiMeshFrame(parent)
{
    setFrameType(DigiMeshFrame::RemoteATCommandRequestFrame);
}
