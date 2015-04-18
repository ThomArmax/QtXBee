#ifndef ZBTXSTATUSRESPONSE_H
#define ZBTXSTATUSRESPONSE_H

#include "xbeepacket.h"

namespace QtXBee {
namespace ZigBee {

/**
 * @brief The ZBTxStatusResponse class indicate if the packet was transmitted successfully or not.
 *
 * When a ZBTxRequest is completed, the module sends a TX Status message.
 * This message will indicate if the packet was transmitted successfully or if there was a failure.
 * @sa ZBTxRequest
 */
class ZBTxStatusResponse : public XBeePacket
{
    Q_OBJECT
public:
    explicit    ZBTxStatusResponse      (QObject *parent);

     void       readPacket              (QByteArray rx);
     void       setDeliveryStatus       (unsigned ds);
     void       setTransmitRetryCount   (unsigned trc);
     void       setDiscoveryStatus      (unsigned ds);

     unsigned   deliveryStatus          () const;
     unsigned   transmitRetryCount      () const;
     unsigned   discoveryStatus         () const;
     QByteArray reserved                () const;

private:
     QByteArray m_reserved;
     unsigned   m_deliveryStatus;
     unsigned   m_transmitRetryCount;
     unsigned   m_discoveryStatus;
};

} } // END namepsace

#endif // ZBTXSTATUSRESPONSE_H
