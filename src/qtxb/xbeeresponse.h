#ifndef XBEERESPONSE_H
#define XBEERESPONSE_H

#include "xbeepacket.h"
#include <QObject>
#include <QDebug>

namespace QtXBee {

/**
 * @brief The XBeeResponse class is the base to create API frames responses.
 */
class XBeeResponse : public XBeePacket
{
    Q_OBJECT
public:
    /**
     * @brief The CommandStatus enum
     */
    enum CommandStatus {
        Ok                  = 0,
        Error               = 1,
        InvalidCommand      = 2,
        InvalidParameter    = 3,
        TXFailure           = 4
    };

    explicit        XBeeResponse    (QObject *parent = 0);
                    ~XBeeResponse   ();

    // Reimplemented from XBeePacket
    virtual void    clear           ();

    void            setData         (const QByteArray & data);
    void            setCommandStatus(const CommandStatus status);

    QByteArray      data            () const;
    CommandStatus   commandStatus   () const { return m_status; }

    static QString  statusToString  (const XBeeResponse::CommandStatus status);

protected:
    QByteArray      m_data;
    CommandStatus   m_status;
};

} // END namepsace

#endif // XBEERESPONSE_H
