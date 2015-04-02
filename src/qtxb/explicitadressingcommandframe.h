#ifndef TXREQUESTEXPLICIT_H
#define TXREQUESTEXPLICIT_H

#include "transmitrequestframe.h"

namespace QtXBee {

class ExplicitAdressingCommandFrame : public TransmitRequestFrame
{
    Q_OBJECT
public:
    explicit ExplicitAdressingCommandFrame(QObject *parent = 0);

private:
    QByteArray m_sourceEndpoint;
    QByteArray m_destinationEndpoint;
    QByteArray m_clusterID;
    QByteArray m_profileID;
};

} // END namepsace

#endif // TXREQUESTEXPLICIT_H
