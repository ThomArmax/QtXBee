#include "nodediscoveryresponseparser.h"
#include "remotenode.h"

#include <QDebug>

namespace QtXBee {

NodeDiscoveryResponseParser::NodeDiscoveryResponseParser()
{

}

NodeDiscoveryResponseParser::~NodeDiscoveryResponseParser()
{

}

/**
 * @brief Parses the ATCommandResponse's data
 * @param data the ATCommandResponse's data to be parsed
 * @return the associated RemoteNode in case of success; NULL otherwise.
 * @note You will have to take the ownership of the returned RemoteNode
 */
RemoteNode *NodeDiscoveryResponseParser::parseData(const QByteArray &data)
{
    QString ni;
    QByteArray my, sh, sl, rssi;
    RemoteNode * node = NULL;

    qDebug() << Q_FUNC_INFO << data.toHex();
    qDebug() << Q_FUNC_INFO << "packet size" << data.size();

    if(data.size() == 0)
        return NULL;

    if(data.size() > 13) {
        for(int i=12; i< data.size(); i++) {
            if(data.at(i) ==0)
                break;
            ni.append(QString(data.at(i)));
        }
    }

    node = new RemoteNode();

    my = data.mid(0, 2);
    sh = data.mid(2, 4);
    sl = data.mid(7, 4);

    rssi.append(data.at(11));

    node->setAddress(my.toHex().toInt());
    node->setSerialNumberHigh((quint32)sh.toHex().toUInt(0,16));
    node->setSerialNumberLow((quint32)sl.toHex().toUInt(0,16));
    node->setNodeIdentifier(ni);
    node->setRssi(-1*QString(rssi.toHex()).toInt(0,16));

    return node;
}

} // END namepsace
