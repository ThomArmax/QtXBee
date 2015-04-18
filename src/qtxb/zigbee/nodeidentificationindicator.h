#ifndef NODEIDENTIFICATIONINDICATOR_H
#define NODEIDENTIFICATIONINDICATOR_H

#include "xbeeresponse.h"

namespace QtXBee {
namespace ZigBee {

/**
 * @brief The NodeIdentificationIndicator frame is received when a module
 * transmits a node identification message to identify itself (when AO=0).
 *
 * The data portion of this frame is similar to a network discovery response frame (see ND command).
 */
class NodeIdentificationIndicator : public XBeeResponse
{
    Q_OBJECT
public:
    explicit NodeIdentificationIndicator(QObject *parent = 0);
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

} } // END namepsace

#endif // NODEIDENTIFICATIONINDICATOR_H
