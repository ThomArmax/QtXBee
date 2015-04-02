#ifndef EXPLICITRXINDICATOR_H
#define EXPLICITRXINDICATOR_H

#include "digimeshframe.h"

namespace QtXBee {

class ExplicitRxIndicatorFrame : public DigiMeshFrame
{
    Q_OBJECT
public:
    explicit ExplicitRxIndicatorFrame(QObject *parent = 0);
    void readPacket(QByteArray rx);
};

} // END namepsace

#endif // EXPLICITRXINDICATOR_H
