#ifndef REMOTEATCOMMANDREQUESTFRAME_H
#define REMOTEATCOMMANDREQUESTFRAME_H

#include "digimeshframe.h"

/**
 * @brief The RemoteATCommandRequestFrame class is used to query or set module parameters on a remote device.
 *
 * For parameter changes on the remote device to take effect, changes must be applied,
 * either by setting the apply changes options bit, or by sending an AC command to the remote.
 */
class RemoteATCommandRequestFrame : public DigiMeshFrame
{
    Q_OBJECT
public:
    explicit RemoteATCommandRequestFrame(QObject *parent = 0);
};

#endif // REMOTEATCOMMANDREQUESTFRAME_H
