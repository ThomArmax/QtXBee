#ifndef REMOTEATCOMMANDREQUESTFRAME_H
#define REMOTEATCOMMANDREQUESTFRAME_H

#include "digimeshframe.h"
#include "atcommandframe.h"

namespace QtXBee {

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

    RemoteATCommandRequestFrame(QObject *parent = 0);

    // Reimplemented from DigiMeshFrame
    virtual void assemblePacket();
    virtual void clear();
    virtual QString toString();

    // Setters
    void setDestinationAddress(const quint64 dest);
    void setNetworkAddress(const quint32 network);
    void setCommandOptions(const RemoteCommandOptions options);
    void setATCommand(const ATCommandFrame::ATCommand command);
    void setCommandParameter(const quint8 parameter);

    // Getters
    quint64 destinationAddress() const;
    quint16 networkAddress() const;
    ATCommandFrame::ATCommand atCommand() const;
    quint8 commandParameter();
    RemoteCommandOptions commandOptions() const;

protected:
    quint64 m_destinationAddress;
    quint16 m_networkAddress;
    RemoteCommandOptions m_options;
    ATCommandFrame::ATCommand m_atCommand;
    quint8 m_commandParameter;
};

} // END namepsace

#endif // REMOTEATCOMMANDREQUESTFRAME_H
