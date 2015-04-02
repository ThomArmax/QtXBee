#ifndef TRANSMITSTATUSFRAME_H
#define TRANSMITSTATUSFRAME_H

#include "digimeshframe.h"

namespace QtXBee {

/**
 * @brief The TransmitRequestFrame class indicate if the packet was transmitted successfully or not.
 *
 * When a TransmitRequestFrame is completed, the module sends a TX Status message.
 * This message will indicate if the packet was transmitted successfully or if there was a failure.
 * @sa TransmitRequestFrame
 */
class TransmitStatusFrame : public DigiMeshFrame
{
    Q_OBJECT
public:
    explicit TransmitStatusFrame(QObject *parent);

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

} // END namepsace

#endif // TRANSMITSTATUSFRAME_H
