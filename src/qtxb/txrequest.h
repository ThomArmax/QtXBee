#ifndef TXREQUEST_H
#define TXREQUEST_H

#include "digimeshpacket.h"


#include <QByteArray>

class TXRequest : public DigiMeshPacket
{
    Q_OBJECT
public:
    explicit TXRequest(QObject *parent = 0);
    void setBroadcastRadius(int rad);
    void setTransmitOptions(unsigned to);
    void setDestAddr64(QByteArray da64);
    void setDestAddr16(QByteArray da16);
    void setData(QByteArray d);
    QByteArray destAddr64() const;
    QByteArray destAddr16() const;
    unsigned broadcastRadius() const;
    unsigned transmitOptions() const;
    QByteArray getData() const;
    void assemblePacket();

private:
    QByteArray m_destAddr64;
    QByteArray m_destAddr16;
    unsigned m_broadcastRadius;
    unsigned m_transmitOptions;
    QByteArray m_data;
};

#endif // TXREQUEST_H
