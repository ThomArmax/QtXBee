#ifndef MODEMSTATUSFRAME_H
#define MODEMSTATUSFRAME_H

#include "digimeshframe.h"
#include <QByteArray>

/**
 * @brief The ModemStatus class represent the XBee module status.
 *
 * RF module status messages are sent from the module in response to specific conditions.
 */
class ModemStatusFrame : public DigiMeshFrame
{
    Q_OBJECT
public:
    explicit ModemStatusFrame(QObject *parent);
    ModemStatusFrame(const QByteArray & data, QObject * parent = 0);

    bool setData(const QByteArray & data);
    void setStatus(unsigned s);
    unsigned status() const;

private:
    unsigned m_status;
};

#endif // MODEMSTATUSFRAME_H
