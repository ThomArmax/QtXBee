#ifndef RXRESPONSEIOSAMPLEBASE_H
#define RXRESPONSEIOSAMPLEBASE_H

#include "rxbaseresponse.h"

#include <QObject>

namespace QtXBee {
namespace WPAN {

/**
 * @todo Implement RxResponseIoSampleBase class
 */
class RxResponseIoSampleBase : public RxBaseResponse
{
    Q_OBJECT
public:
    explicit        RxResponseIoSampleBase  (QObject *parent = 0);
    virtual         ~RxResponseIoSampleBase ();

    // Reimplemented from RxBaseResponse
    virtual void    clear                   ();
    virtual bool    setPacket               (const QByteArray & packet);
    virtual QString toString                ();

protected:
    quint8          m_samplesCount;
    quint16         m_channelIndicator;
};

}} // END namespace

#endif // RXRESPONSEIOSAMPLEBASE_H
