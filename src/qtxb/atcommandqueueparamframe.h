#ifndef ATCOMMANDQUEUEPARAMFRAME_H
#define ATCOMMANDQUEUEPARAMFRAME_H

#include "atcommandframe.h"
#include <QByteArray>

/**
 * @brief The ATCommandQueueParamFrame class allows module parameters to be queried or set.
 *
 * In contrast to the ATCommandFrame API type, new parameter values are queued and not applied
 * until either the ATCommandFrame (0x08) API type or the AC (Apply Changes) command is issued.
 * Register queries (reading parameter values) are returned immediately.
 */
class ATCommandQueueParamFrame : public ATCommandFrame
{
    Q_OBJECT
public:
    explicit ATCommandQueueParamFrame(QObject *parent);
};

#endif // ATCOMMANDQUEUEPARAMFRAME_H
