#ifndef NODEDISCOVERYRESPONSEPARSER_H
#define NODEDISCOVERYRESPONSEPARSER_H

#include <QtCore>

namespace QtXBee {
class RemoteNode;

class NodeDiscoveryResponseParser
{
public:
    NodeDiscoveryResponseParser();
    ~NodeDiscoveryResponseParser();

    RemoteNode * parseData(const QByteArray & data);
};

} // END namepsace

#endif // NODEDISCOVERYRESPONSEPARSER_H
