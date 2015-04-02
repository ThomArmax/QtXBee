#ifndef NODEIDENTIFICATIONINDICATORFRAME_H
#define NODEIDENTIFICATIONINDICATORFRAME_H

#include "digimeshframeresponse.h"

namespace QtXBee {

/**
 * @brief The NodeIdentificationIndicator frame is received when a module
 * transmits a node identification message to identify itself (when AO=0).
 *
 * The data portion of this frame is similar to a network discovery response frame (see ND command).
 */
class NodeIdentificationIndicatorFrame : public DigiMeshFrameResponse
{
    Q_OBJECT
public:
    explicit NodeIdentificationIndicatorFrame(QObject *parent = 0);
    virtual bool setPacket(const QByteArray &packet);

    virtual QString toString();

private:
    quint64 m_senderAddr64;
    quint16 m_senderAddr16;
    quint8 m_receiveOptions;
    quint16 m_remoteAddr16;
    quint64 m_remoteAddr64;
    QString m_nodeIdentifier;
    quint16 m_remoteParent16;
    quint8 m_deviceType;
    quint8 m_sourceEvent;
    quint16 m_digiProfileId;
    quint16 m_digiManufacturerId;
};

} // END namepsace

#endif // NODEIDENTIFICATIONINDICATORFRAME_H
