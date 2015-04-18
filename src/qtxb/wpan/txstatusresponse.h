#ifndef TXSTATUSRESPONSE_H
#define TXSTATUSRESPONSE_H

#include "../xbeepacket.h"

namespace QtXBee {
namespace WPAN {

class TXStatusResponse : public XBeePacket
{
    Q_OBJECT
public:
    enum Status {
        Unknown     = -1,
        Success     = 0,
        NoACK       = 1,
        CCAFailure  = 2,
        Purged      = 3
    };

    explicit        TXStatusResponse        (QObject *parent = 0);
    virtual         ~TXStatusResponse       ();

    // Reimplemented from XBeePacket
    virtual void    clear                   ();
    virtual QString toString                ();

    void            setStatus               (const Status status);
    Status          status                  () const;

    static QString  statusToString          (const Status status);

protected:
    virtual bool    parseApiSpecificData    (const QByteArray &data);

private:
    Status          m_status;
};

}} // END namepsace

#endif // TXSTATUSRESPONSE_H
