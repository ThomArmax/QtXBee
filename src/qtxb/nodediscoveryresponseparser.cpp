#include "nodediscoveryresponseparser.h"
#include <QDebug>

NodeDiscoveryResponseParser::NodeDiscoveryResponseParser()
{

}

NodeDiscoveryResponseParser::~NodeDiscoveryResponseParser()
{

}

bool NodeDiscoveryResponseParser::setPacketData(const QByteArray &data)
{
    QString ni;
    QByteArray my, sh, sl, rssi;
    qDebug() << Q_FUNC_INFO << data.toHex();
    qDebug() << Q_FUNC_INFO << "packet size" << data.size();

    if(data.size() == 0)
        return false;

    if(data.size() > 13) {
        for(int i=12; i< data.size(); i++) {
            if(data.at(i) ==0)
                break;
            ni.append(QString(data.at(i)));
        }
    }

    my = data.mid(0, 2);
    sh = data.mid(2, 4);
    sl = data.mid(7, 4);

    rssi.append(data.at(11));

    qDebug() << Q_FUNC_INFO << "MY             " << qPrintable(QString("0x").append(my.toHex()));
    qDebug() << Q_FUNC_INFO << "SH             " << qPrintable(QString("0x").append(sh.toHex()));
    qDebug() << Q_FUNC_INFO << "SL             " << qPrintable(QString("0x").append(sl.toHex()));
    qDebug() << Q_FUNC_INFO << "RSSI           " << qPrintable(QString("%1 dBm").arg(-1*QString(rssi.toHex()).toInt(0, 16)));
    qDebug() << Q_FUNC_INFO << "NODE IDENTIFIER" << qPrintable(ni);
    return true;
}
