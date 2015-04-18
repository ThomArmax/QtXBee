#include "xbeeresponse.h"

namespace QtXBee {

XBeeResponse::XBeeResponse(QObject *parent) :
    XBeePacket(parent),
    m_status(Error)
{

}

XBeeResponse::~XBeeResponse()
{

}

/**
 * @brief Returns the response's data
 * @return the response's data
 */
QByteArray XBeeResponse::data() const
{
    return m_data;
}

/**
 * @brief Sets the response's data
 * @param data
 */
void XBeeResponse::setData(const QByteArray &data)
{
    m_data.clear();
    m_data = data;
}

void XBeeResponse::clear()
{
    XBeePacket::clear();
    m_data.clear();
    m_status = Error;
}

/**
 * @brief Sets the command status
 * @param status
 */
void XBeeResponse::setCommandStatus(const CommandStatus status)
{
    m_status = status;
}

/**
 * @brief Returns the command' status
 * @return the command' status
 */
XBeeResponse::CommandStatus XBeeResponse::commandStatus() const
{
    return m_status;
}

/**
 * @brief Returns the given XBeeResponse::CommandStatus as a human readable string
 * @param status
 * @return the given XBeeResponse::CommandStatus as a human readable string
 */
QString XBeeResponse::statusToString(const XBeeResponse::CommandStatus status)
{
    QString st = "Unknown";
    switch(status) {
    case Ok                 : st = "OK"                 ; break;
    case Error              : st = "Error"              ; break;
    case InvalidCommand     : st = "Invalid Command"    ; break;
    case InvalidParameter   : st = "Invalid Parameter"  ; break;
    case TXFailure          : st = "Tx Failure"         ; break;
    }

    return st;
}

} // END namepsace
