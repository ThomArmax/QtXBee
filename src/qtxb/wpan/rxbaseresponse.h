#ifndef RXBASERESPONSE_H
#define RXBASERESPONSE_H

#include "../xbeeresponse.h"

#include <QObject>

namespace QtXBee {
namespace WPAN {

/**
 * @brief The RXBaseResponse class
 * @todo Handle options
 */
class RxBaseResponse : public XBeeResponse
{
    Q_OBJECT
public:
    explicit RxBaseResponse(QObject *parent = 0);
    virtual ~RxBaseResponse();

    // Reimplemented from XBeePacket
    virtual void clear();
    virtual bool setPacket(const QByteArray & packet);
    virtual QString toString();

    void setRSSI(const qint8 rssi);
    qint8 rssi() const;

    void setOptions(const quint8 options);
    quint8 options() const;

protected:
    qint8 m_rssi;
    quint8 m_options;

};

}} // END namespace

#endif // RXBASERESPONSE_H
