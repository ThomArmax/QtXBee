#ifndef ATCOMMANDRESPONSE_H
#define ATCOMMANDRESPONSE_H

#include "xbeeresponse.h"
#include "atcommand.h"
#include <QByteArray>

namespace QtXBee {

/**
 * @brief In response to an ATCommand message, the module will send an ATCommandResponse message.
 *
 * Some commands will send back multiple frames (for example, the ND (Node Discover) command).
 * @sa ATCommand
 */
class ATCommandResponse : public XBeeResponse
{
    Q_OBJECT
public:
    explicit ATCommandResponse(QObject *parent = 0);
    ATCommandResponse(const QByteArray &packet, QObject * parent = 0);

    void setATCommand(ATCommand::ATCommandType at);
    void setATCommand(const QByteArray & at);

    ATCommand::ATCommandType atCommand() const;
    QString toString();

protected:
    virtual bool parseApiSpecificData(const QByteArray &data);

private:
    ATCommand::ATCommandType m_atCommand;
};

} // END namepsace

#endif // ATCOMMANDRESPONSE_H
