#ifndef RECEIVEPACKETFRAME_H
#define RECEIVEPACKETFRAME_H

#include "digimeshframe.h"

namespace QtXBee {

class ReceivePacketFrame : public DigiMeshFrame
{
    Q_OBJECT
public:
    explicit ReceivePacketFrame(QObject *parent);
    void setSrcAddr64(QByteArray sa64);
    void setSrcAddr16(QByteArray sa16);
    void setReceiveOptions(unsigned ro);
    void setData(QByteArray d);
    QByteArray srcAddr64() const;
    QByteArray srcAddr16() const;
    unsigned receiveOptions() const;
    QByteArray data() const;
    void readPacket(QByteArray rx);

private:
    QByteArray m_srcAddr64;
    QByteArray m_srcAddr16;
    unsigned m_receiveOptions;
    QByteArray m_data;
};

} // END namepsace

#endif // RECEIVEPACKETFRAME_H
