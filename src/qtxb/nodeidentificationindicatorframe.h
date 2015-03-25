#ifndef NODEIDENTIFICATIONINDICATORFRAME_H
#define NODEIDENTIFICATIONINDICATORFRAME_H
#include "digimeshframe.h"
#include <QByteArray>

/**
 * @brief The NodeIdentificationIndicator frame is received when a module
 * transmits a node identification message to identify itself (when AO=0).
 *
 * The data portion of this frame is similar to a network discovery response frame (see ND command).
 */
class NodeIdentificationIndicatorFrame : public DigiMeshFrame
{
    Q_OBJECT
public:
    explicit NodeIdentificationIndicatorFrame(QObject *parent = 0);
    void readPacket(QByteArray rx);
};

#endif // NODEIDENTIFICATIONINDICATORFRAME_H
