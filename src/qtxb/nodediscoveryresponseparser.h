#ifndef NODEDISCOVERYRESPONSEPARSER_H
#define NODEDISCOVERYRESPONSEPARSER_H

#include <QtCore>

class RemoteNode;

class NodeDiscoveryResponseParser
{
public:
    NodeDiscoveryResponseParser();
    ~NodeDiscoveryResponseParser();

    RemoteNode * parseData(const QByteArray & data);
};

#endif // NODEDISCOVERYRESPONSEPARSER_H
