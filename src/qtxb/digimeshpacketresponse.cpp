#include "digimeshpacketresponse.h"

DigiMeshPacketResponse::DigiMeshPacketResponse(QObject *parent) :
    DigiMeshPacket(parent)
{

}

DigiMeshPacketResponse::DigiMeshPacketResponse(const QByteArray &data, QObject *parent) :
    DigiMeshPacket(parent)
{
    setPacket(data);
}

DigiMeshPacketResponse::~DigiMeshPacketResponse()
{

}

bool DigiMeshPacketResponse::setPacket(const QByteArray &data)
{
    Q_UNUSED(data)
    return false;
}

QByteArray DigiMeshPacketResponse::data() const {
    return m_data;
}
