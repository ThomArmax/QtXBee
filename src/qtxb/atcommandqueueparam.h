#ifndef ATCOMMANDQUEUEPARAM_H
#define ATCOMMANDQUEUEPARAM_H

#include "atcommand.h"
#include <QByteArray>

class ATCommandQueueParam : public ATCommand
{
    Q_OBJECT
public:
    explicit ATCommandQueueParam(QObject *parent);
};

#endif // ATCOMMANDQUEUEPARAM_H
