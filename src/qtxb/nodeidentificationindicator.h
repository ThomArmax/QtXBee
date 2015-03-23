#ifndef NODEIDENTIFICATIONINDICATOR_H
#define NODEIDENTIFICATIONINDICATOR_H
#include "digimeshpacket.h"
#include <QByteArray>

/**
 * @brief The NodeIdentificationIndicator frame is received when a module
 * transmits a node identification message to identify itself (when AO=0).
 *
 * The data portion of this frame is similar to a network discovery response frame (see ND command).
 */
class NodeIdentificationIndicator : public DigiMeshPacket
{
    Q_OBJECT
public:
    explicit NodeIdentificationIndicator(QObject *parent = 0);
    void readPacket(QByteArray rx);
};

#endif // NODEIDENTIFICATIONINDICATOR_H
