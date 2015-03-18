#ifndef DIGIMESHPACKETRESPONSE_H
#define DIGIMESHPACKETRESPONSE_H

#include "digimeshpacket.h"
#include <QObject>

class DigiMeshPacketResponse : public DigiMeshPacket
{
    Q_OBJECT
public:
    explicit DigiMeshPacketResponse(QObject *parent = 0);
    DigiMeshPacketResponse(const QByteArray & packet, QObject *parent = 0);
    ~DigiMeshPacketResponse();

    virtual bool setPacket(const QByteArray &packet);
    virtual QByteArray data() const;

signals:

public slots:

protected:
    QByteArray m_data;
};

#endif // DIGIMESHPACKETRESPONSE_H
