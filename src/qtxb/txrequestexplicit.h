#ifndef TXREQUESTEXPLICIT_H
#define TXREQUESTEXPLICIT_H

#include "txrequest.h"
#include <QByteArray>

class TXRequestExplicit : public TXRequest
{
    Q_OBJECT
public:
    explicit TXRequestExplicit(QObject *parent = 0);

private:
    QByteArray m_sourceEndpoint;
    QByteArray m_destinationEndpoint;
    QByteArray m_clusterID;
    QByteArray m_profileID;
};

#endif // TXREQUESTEXPLICIT_H
