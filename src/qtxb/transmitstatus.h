#ifndef TRANSMITSTATUS_H
#define TRANSMITSTATUS_H
#include "digimeshpacket.h"
#include <QByteArray>

class TransmitStatus : public DigiMeshPacket
{
    Q_OBJECT
public:
    explicit TransmitStatus(QObject *parent);

     void readPacket(QByteArray rx);
     void setDeliveryStatus(unsigned ds);
     void setTransmitRetryCount(unsigned trc);
     void setDiscoveryStatus(unsigned ds);
     unsigned deliveryStatus() const;
     unsigned transmitRetryCount() const;
     unsigned discoveryStatus() const;
     QByteArray reserved() const;

private:
     QByteArray m_reserved;
     unsigned m_deliveryStatus;
     unsigned m_transmitRetryCount;
     unsigned m_discoveryStatus;
};

#endif // TRANSMITSTATUS_H
