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

QByteArray XBeeResponse::data() const
{
    return m_data;
}

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

void XBeeResponse::setCommandStatus(const CommandStatus status)
{
    m_status = status;
}

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
