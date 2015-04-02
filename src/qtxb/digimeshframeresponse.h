#ifndef DIGIMESHFRAMERESPONSE_H
#define DIGIMESHFRAMERESPONSE_H

#include "digimeshframe.h"
#include <QObject>
#include <QDebug>

namespace QtXBee {

/**
 * @brief The DigiMeshFrameResponse class is the base to create API frames respons.
 */
class DigiMeshFrameResponse : public DigiMeshFrame
{
    Q_OBJECT
public:
    /**
     * @brief The CommandStatus enum
     */
    enum CommandStatus {
        Ok                  = 0,
        Error               = 1,
        InvalidCommand      = 2,
        InvalidParameter    = 3,
        TXFailure           = 4
    };

    explicit DigiMeshFrameResponse(QObject *parent = 0);
    ~DigiMeshFrameResponse();

    // Reimplemented from DigiMeshFrame
    virtual void clear();

    virtual QByteArray data() const;

    void setCommandStatus(const CommandStatus status);
    CommandStatus commandStatus() const { return m_status; }

    static QString statusToString(const DigiMeshFrameResponse::CommandStatus status);

protected:
    QByteArray m_data;
    CommandStatus m_status;
};

} // END namepsace

#endif // DIGIMESHFRAMERESPONSE_H
