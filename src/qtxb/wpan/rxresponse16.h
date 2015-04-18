#ifndef RXRESPONSE16_H
#define RXRESPONSE16_H

#include "rxbaseresponse.h"

#include <QObject>

namespace QtXBee {
namespace WPAN {

class RxResponse16 : public RxBaseResponse
{
    Q_OBJECT
public:
    explicit        RxResponse16            (QObject *parent = 0);
    virtual         ~RxResponse16           ();

    // Reimplemented from RXBaseResponse
    virtual void    clear                   ();
    virtual QString toString                ();

    void            setSourceAddress        (const quint16 sourceAddress);
    quint16         sourceAddress           () const;

protected:
    virtual bool    parseApiSpecificData    (const QByteArray &data);

private:
    quint16         m_sourceAddress;
};

}} // END namespace

#endif // RXRESPONSE16_H
