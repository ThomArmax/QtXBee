#include "digimeshframeresponse.h"

DigiMeshFrameResponse::DigiMeshFrameResponse(QObject *parent) :
    DigiMeshFrame(parent),
    m_status(Error)
{

}

DigiMeshFrameResponse::~DigiMeshFrameResponse()
{

}

bool DigiMeshFrameResponse::setPacket(const QByteArray &data)
{
    Q_UNUSED(data)
    return false;
}

QByteArray DigiMeshFrameResponse::data() const
{
    return m_data;
}

void DigiMeshFrameResponse::setCommandStatus(const CommandStatus status)
{
    m_status = status;
}

QString DigiMeshFrameResponse::statusToString(const DigiMeshFrameResponse::CommandStatus status)
{
    QString st = "Unknown";
    switch(status) {
    case Ok                 : st = "OK"                 ; break;
    case Error              : st = "Error"              ; break;
    case InvalidCommand     : st = "Invalid Command"    ; break;
    case InvalidParameter   : st = "Invalid Parameter"  ; break;
    case TXFailure          : st = "Tx Failure"         ; break;
    }

    return st;
}
