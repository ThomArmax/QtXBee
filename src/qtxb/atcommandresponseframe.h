#ifndef ATCOMMANDRESPONSEFRAME_H
#define ATCOMMANDRESPONSEFRAME_H

#include "digimeshframeresponse.h"
#include "atcommandframe.h"
#include <QByteArray>

/**
 * @brief In response to an ATCommandFrame message, the module will send an ATCommandResponseFrame message.
 *
 * Some commands will send back multiple frames (for example, the ND (Node Discover) command).
 * @sa ATCommandFrame
 */
class ATCommandResponseFrame : public DigiMeshFrameResponse
{
    Q_OBJECT
public:
    explicit ATCommandResponseFrame(QObject *parent = 0);
    ATCommandResponseFrame(const QByteArray &packet, QObject * parent = 0);

    void setATCommand(ATCommandFrame::ATCommand at);
    void setATCommand(const QByteArray & at);
    virtual bool setPacket(const QByteArray &packet);

    ATCommandFrame::ATCommand atCommand() const;
    QString toString();

private:
    ATCommandFrame::ATCommand m_atCommand;
};

#endif // ATCOMMANDRESPONSEFRAME_H
