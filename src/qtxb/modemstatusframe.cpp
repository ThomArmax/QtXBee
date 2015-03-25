#include "modemstatusframe.h"
#include "digimeshframe.h"
#include <QDebug>

ModemStatusFrame::ModemStatusFrame(QObject *parent) :
    DigiMeshFrame(parent)
{
}

ModemStatusFrame::ModemStatusFrame(const QByteArray &data, QObject *parent) :
    DigiMeshFrame(parent)
{
    setData(data);
}

bool ModemStatusFrame::setData(const QByteArray & data) {
    bool bRet = false;
    m_packet.clear();
    m_packet.append(data);
    setStartDelimiter(data.at(0));
    setLength(data.at(2));

    if(data.size() == data.at(2)+4) {
        setFrameType((APIFrameType)data.at(3));
        setStatus(data.at(4));
        setChecksum(data.at(5));
        bRet = true;
    }
    else {
        qDebug()<< Q_FUNC_INFO << "Invalid Packet !" << m_packet.toHex();
        m_packet.clear();
    }

    return bRet;
}

void ModemStatusFrame::setStatus(unsigned s){
    m_status = s;
}

unsigned ModemStatusFrame::status() const{
    return m_status;
}
