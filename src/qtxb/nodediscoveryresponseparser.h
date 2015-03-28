#ifndef NODEDISCOVERYRESPONSEPARSER_H
#define NODEDISCOVERYRESPONSEPARSER_H

#include <QtCore>

class NodeDiscoveryResponseParser
{
public:
    NodeDiscoveryResponseParser();
    ~NodeDiscoveryResponseParser();

    bool setPacketData(const QByteArray & data);

private:
    quint32 sh;
    quint32 sl;
    QString ni;

};

#endif // NODEDISCOVERYRESPONSEPARSER_H
