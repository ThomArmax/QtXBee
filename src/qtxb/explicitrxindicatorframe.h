#ifndef EXPLICITRXINDICATOR_H
#define EXPLICITRXINDICATOR_H

#include "digimeshframe.h"

class ExplicitRxIndicatorFrame : public DigiMeshFrame
{
    Q_OBJECT
public:
    explicit ExplicitRxIndicatorFrame(QObject *parent = 0);
    void readPacket(QByteArray rx);
};

#endif // EXPLICITRXINDICATOR_H
