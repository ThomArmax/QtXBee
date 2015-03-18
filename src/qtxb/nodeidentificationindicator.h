#ifndef NODEIDENTIFICATIONINDICATOR_H
#define NODEIDENTIFICATIONINDICATOR_H
#include "digimeshpacket.h"
#include <QByteArray>

class NodeIdentificationIndicator : public DigiMeshPacket
{
    Q_OBJECT
public:
    explicit NodeIdentificationIndicator(QObject *parent = 0);
    void readPacket(QByteArray rx);
};

#endif // NODEIDENTIFICATIONINDICATOR_H
