#ifndef ATCOMMANDQUEUEPARAM_H
#define ATCOMMANDQUEUEPARAM_H

#include "atcommand.h"
#include <QByteArray>

/**
 * @brief The ATCommandQueueParam class allows module parameters to be queried or set.
 *
 * In contrast to the ATCommand API type, new parameter values are queued and not applied
 * until either the ATCommand (0x08) API type or the AC (Apply Changes) command is issued.
 * Register queries (reading parameter values) are returned immediately.
 */
class ATCommandQueueParam : public ATCommand
{
    Q_OBJECT
public:
    explicit ATCommandQueueParam(QObject *parent);
};

#endif // ATCOMMANDQUEUEPARAM_H
