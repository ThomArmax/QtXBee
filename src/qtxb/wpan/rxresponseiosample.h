#ifndef RXRESPONSEIOSAMPLE_H
#define RXRESPONSEIOSAMPLE_H

#include "rxbaseresponse.h"

#include <QObject>

namespace QtXBee {
namespace WPAN {

class RxResponseIoSample : public RxBaseResponse
{
    Q_OBJECT
public:
    explicit RxResponseIoSample(QObject *parent = 0);
    virtual ~RxResponseIoSample();

};

}} // END namespace

#endif // RXRESPONSEIOSAMPLE_H
