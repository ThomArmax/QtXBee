#ifndef REMOTECOMMANDREQUEST_H
#define REMOTECOMMANDREQUEST_H

#include <QObject>

/**
 * @brief The RemoteCommandRequest class is used to query or set module parameters on a remote device.
 *
 * For parameter changes on the remote device to take effect, changes must be applied,
 * either by setting the apply changes options bit, or by sending an AC command to the remote.
 */
class RemoteCommandRequest : public QObject
{
    Q_OBJECT
public:
    explicit RemoteCommandRequest(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // REMOTECOMMANDREQUEST_H
