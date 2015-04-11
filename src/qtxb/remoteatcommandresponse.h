#ifndef REMOTECOMMANDRESPONSE_H
#define REMOTECOMMANDRESPONSE_H

#include "atcommandresponse.h"

#include <QObject>
#include <QByteArray>

namespace QtXBee {

/**
 * @brief The RemoteCommandResponse represent the response to a RemoteCommandRequest.
 *
 * If a module receives a remote command response RF data frame in response to a RemoteCommandRequest,
 * the module will send a RemoteCommandResponse message out the UART.
 * Some commands may send back multiple frames--for example, Node Discover (ND) command.
 *
 * @sa RemoteCommandRequest
 */
class RemoteATCommandResponse : public ATCommandResponse
{
    Q_OBJECT
public:
    explicit RemoteATCommandResponse(QObject *parent = 0);
    RemoteATCommandResponse(const QByteArray & packet, QObject *parent = 0);

    // Reimplement from ATCommandResponse
    virtual QString toString();
    virtual void clear();

    // Setters
    void setSourceAddress64(const quint64 addr);
    void setSourceAddress16(const quint32 addr);

    // Getters
    quint64 sourceAddress64() const;
    quint16 sourceAddress16() const;

private:
    virtual bool parseApiSpecificData(const QByteArray &data);

private:
    quint64 m_sourceAddress64;
    quint16 m_sourceAddress16;
};

} // END namepsace

#endif // REMOTECOMMANDRESPONSE_H
