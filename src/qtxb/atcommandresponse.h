#ifndef ATCOMMANDRESPONSE_H
#define ATCOMMANDRESPONSE_H

#include "digimeshpacketresponse.h"
#include "atcommand.h"
#include <QByteArray>

/**
 * @brief In response to an ATCommand message, the module will send an ATCommandResponse message.
 *
 * Some commands will send back multiple frames (for example, the ND (Node Discover) command).
 * @sa ATCommand
 */
class ATCommandResponse : public DigiMeshPacketResponse
{
    Q_OBJECT
public:
    enum Status {
        Ok                  = 0,
        Error               = 1,
        InvalidCommand      = 2,
        InvalidParameter    = 3,
        TXFailure           = 4
    };

    explicit ATCommandResponse(QObject *parent);
    ATCommandResponse(const QByteArray &packet, QObject * parent = 0);

    void setATCommand(ATCommand::ATCommandType at);
    void setATCommand(const QByteArray & at);
    void setCommandStatus(ATCommandResponse::Status cs);
    bool setPacket(const QByteArray &packet);

    ATCommand::ATCommandType atCommand() const;
    unsigned commandStatus() const;
    QString toString();

    static QString statusToString(const ATCommandResponse::Status status);

private:
    ATCommand::ATCommandType m_atCommand;
    ATCommandResponse::Status m_commandStatus;
};

#endif // ATCOMMANDRESPONSE_H
