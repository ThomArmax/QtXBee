#ifndef ATCOMMANDRESPONSE_H
#define ATCOMMANDRESPONSE_H

#include "digimeshpacketresponse.h"
#include "atcommand.h"
#include <QByteArray>

class ATCommandResponse : public DigiMeshPacketResponse
{
    Q_OBJECT
public:
    explicit ATCommandResponse(QObject *parent);
    ATCommandResponse(const QByteArray &packet, QObject * parent = 0);

    void setATCommand(ATCommand::ATCommandType at);
    void setATCommand(const QByteArray & at);
    void setCommandStatus(unsigned cs);
    bool setPacket(const QByteArray &packet);

    ATCommand::ATCommandType atCommand() const;
    unsigned commandStatus() const;
    QString toString();

private:
    ATCommand::ATCommandType m_atCommand;
    unsigned m_commandStatus;
};

#endif // ATCOMMANDRESPONSE_H
