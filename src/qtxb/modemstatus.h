#ifndef MODEMSTATUS_H
#define MODEMSTATUS_H

#include "xbeepacket.h"
#include <QByteArray>

namespace QtXBee {

/**
 * @brief The ModemStatus class represent the XBee module status.
 *
 * RF module status messages are sent from the module in response to specific conditions.
 */
class ModemStatus : public XBeePacket
{
    Q_OBJECT
public:
    explicit    ModemStatus     (QObject *parent);
                ModemStatus     (const QByteArray & data, QObject * parent = 0);

    bool        setData         (const QByteArray & data);
    void        setStatus       (unsigned s);

    unsigned    status          () const;

private:
    unsigned m_status;
};

} // END namepsace

#endif // MODEMSTATUS_H
