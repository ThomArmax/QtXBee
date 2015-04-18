#ifndef REMOTEATCOMMANDREQUEST_H
#define REMOTEATCOMMANDREQUEST_H

#include "atcommand.h"

namespace QtXBee {

/**
 * @brief The RemoteATCommandRequest class is used to query or set module parameters on a remote device.
 *
 * For parameter changes on the remote device to take effect, changes must be applied,
 * either by setting the apply changes options bit, or by sending an AC command to the remote.
 */
class RemoteATCommandRequest : public ATCommand
{
    Q_OBJECT
public:
    /**
     * @brief The RemoteCommandOption enum defines the remote command options
     */
    enum RemoteCommandOption {
        DisableRetriesAndRouteRepair    = 0x01, /**< Disable retries and route repair */
        ApplyChanges                    = 0x02, /**< Apply changes */
        EnabledAPSEncryption            = 0x20, /**< Enable APS encryption (if EE=1) */
        UseExtendedTXTimeout            = 0x40  /**< Use the extended transmision timeout */
    };
    Q_DECLARE_FLAGS(RemoteCommandOptions, RemoteCommandOption)

    explicit                RemoteATCommandRequest  (QObject *parent = 0);

    // Reimplemented from ATCommand
    virtual void            assemblePacket          ();
    virtual void            clear                   ();
    virtual QString         toString                ();

    // Setters
    void                    setDestinationAddress64 (const quint64 dest);
    void                    setDestinationAddress16 (const quint32 dest);
    void                    setCommandOptions       (const RemoteCommandOptions options);

    // Getters
    quint64                 destinationAddress      () const;
    quint16                 networkAddress          () const;
    RemoteCommandOptions    commandOptions          () const;

protected:
    quint64                 m_destinationAddress64;
    quint16                 m_destinationAddress16;
    RemoteCommandOptions    m_options;
};

} // END namepsace

#endif // REMOTEATCOMMANDREQUEST_H
