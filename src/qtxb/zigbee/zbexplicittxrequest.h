#ifndef ZBEXPLICITTXRESPONSE_H
#define ZBEXPLICITTXRESPONSE_H

#include "zbtxrequest.h"

namespace QtXBee {
namespace ZigBee {

class ZBExplicitTxRequest : public ZBTxRequest
{
    Q_OBJECT
public:
    explicit ZBExplicitTxRequest(QObject *parent = 0);

private:
    QByteArray m_sourceEndpoint;
    QByteArray m_destinationEndpoint;
    QByteArray m_clusterID;
    QByteArray m_profileID;
};

} } // END namepsace

#endif // ZBEXPLICITTXRESPONSE_H
