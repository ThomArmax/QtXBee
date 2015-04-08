#ifndef RXRESPONSEIOSAMPLEBASE_H
#define RXRESPONSEIOSAMPLEBASE_H

#include "rxbaseresponse.h"

#include <QObject>

namespace QtXBee {
namespace WPAN {

class RxResponseIoSampleBase : public RxBaseResponse
{
    Q_OBJECT
public:
    explicit RxResponseIoSampleBase(QObject *parent = 0);
    virtual ~RxResponseIoSampleBase();

protected:
    quint8 m_samplesCount;
    quint16 m_channelIndicator;
};

}} // END namespace

#endif // RXRESPONSEIOSAMPLEBASE_H
