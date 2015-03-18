#ifndef ATCOMMANDREMOTE_H
#define ATCOMMANDREMOTE_H

#include "atcommand.h"
#include <QByteArray>

class ATCommandRemote : public ATCommand
{
    Q_OBJECT
public:
    explicit ATCommandRemote(QObject *parent);

private:
    QByteArray m_remoteCommandOptions;
};

#endif // ATCOMMANDREMOTE_H
