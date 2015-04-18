#ifndef TXREQUESTEXPLICIT_H
#define TXREQUESTEXPLICIT_H

#include "transmitrequest.h"

namespace QtXBee {
namespace ZigBee {

class ExplicitAdressingCommand : public TransmitRequest
{
    Q_OBJECT
public:
    explicit ExplicitAdressingCommand(QObject *parent = 0);

private:
    QByteArray m_sourceEndpoint;
    QByteArray m_destinationEndpoint;
    QByteArray m_clusterID;
    QByteArray m_profileID;
};

} } // END namepsace

#endif // TXREQUESTEXPLICIT_H
