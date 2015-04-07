#ifndef RXRESPONSE64_H
#define RXRESPONSE64_H

#include "rxbaseresponse.h"

#include <QObject>

namespace QtXBee {
namespace WPAN {


class RxResponse64 : public RxBaseResponse
{
    Q_OBJECT
public:
    explicit RxResponse64(QObject * parent = 0);
    virtual ~RxResponse64();

    // Reimplemented from RXBaseResponse
    virtual void clear();
    virtual bool setPacket(const QByteArray & packet);
    virtual QString toString();

    void setSourceAddress(const quint64 sourceAddress);
    quint64 sourceAddress() const;

private:
    quint64 m_sourceAddress;
};

}} // END namespace

#endif // RXRESPONSE64_H
