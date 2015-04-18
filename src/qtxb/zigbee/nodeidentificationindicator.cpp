#include "nodeidentificationindicator.h"

namespace QtXBee {
namespace ZigBee {

ZBIONodeIdentificationResponse::ZBIONodeIdentificationResponse(QObject *parent) :
    XBeeResponse(parent),
    m_senderAddr64          (0),
    m_senderAddr16          (0),
    m_receiveOptions        (0),
    m_remoteAddr16          (0),
    m_remoteAddr64          (0),
    m_nodeIdentifier        (QString()),
    m_remoteParent16        (0),
    m_deviceType            (0),
    m_sourceEvent           (0),
    m_digiProfileId         (0),
    m_digiManufacturerId    (0)
{
    setFrameType(XBeePacket::ZBIONodeIdentificationId);
}

bool ZBIONodeIdentificationResponse::setPacket(const QByteArray &packet)
Q_DECL_OVERRIDE
{
    qDebug() << Q_FUNC_INFO << QString(packet.toHex());
    qDebug() << Q_FUNC_INFO << "packet size" << packet.size();
    bool bRet  = false;
    int count = 0;
    int pow = 0;
    int packetSize = packet.size();
    int niOffset =  0;
    // Reset all data
    m_packet.clear();
    m_senderAddr64          = 0;
    m_senderAddr16          = 0;
    m_receiveOptions        = 0;
    m_remoteAddr16          = 0;
    m_remoteAddr64          = 0;
    m_nodeIdentifier        = "";
    m_remoteParent16        = 0;
    m_deviceType            = 0;
    m_sourceEvent           = 0;
    m_digiProfileId         = 0;
    m_digiManufacturerId    = 0;

    m_packet = packet;

    if(packetSize < 33) {
        qWarning() << Q_FUNC_INFO << "Warning : bad packet size (got"
                   << QString("got %1, expecter %2)").arg(packet.size()).arg(33);
        goto exit;
    }

    qDebug() << Q_FUNC_INFO << "start delimiter" << QString("0x%1").arg(QString::number(packet.at(0), 16));
    setStartDelimiter(packet.at(0));
    setLength(packet.at(2) + (packet.at(1)<<8));
    if(packetSize == packet.at(2)+4) {
        int ft = packet.at(3)&0xFF;
        // Check the frame type
        if(ft != frameType()) {
            qWarning() << Q_FUNC_INFO << "Warning : bad frame type"
                       << qPrintable(QString("(got 0x%1, 0x%2 expected)").arg(ft,0, 16).arg(frameType(), 0, 16));
            //goto exit;
        }
        count = 4;

        // Get specific raw data
        while(count < packetSize-1) {
            m_data.append(packet.at(count));
            count++;
        }

        // Get Sender 64 Bits Address
        count = 11;
        pow = 0;
        while(count > 3) {
            m_senderAddr64 += QString(packet.at(count)).toInt() << pow*8;
            count--;
            pow++;
        }

        // Get Sender 16 Bits Address
        count = 13;
        pow = 0;
        while(count > 11) {
            m_senderAddr16 += QString(packet.at(count)).toInt()<< pow*8;
            count--;
            pow++;
        }
        m_receiveOptions = packet.at(14);

        // Get Remote 16 Bits Address
        count = 16;
        pow = 0;
        while(count > 14) {
            m_senderAddr16 += QString(packet.at(count)).toInt() << pow*8;
            count--;
            pow++;
        }

        // Get Remote 64 Bits Address
        count = 24;
        pow = 0;
        while(count > 16) {
            m_senderAddr64 += QString(packet.at(count)).toInt() << pow*8;
            count--;
            pow++;
        }

        // Get Node Identifier
        count = 25;
        qDebug() << Q_FUNC_INFO << "packet[25]=" << packet.at(count);
        while(packet.at(count) != 0x00) {
            qDebug() << Q_FUNC_INFO << packet.at(count);
            m_nodeIdentifier.append(packet.at(count));

            count ++;
        }
        niOffset = 25 + m_nodeIdentifier.size();

        // Get Remote Parent 16 Bits Address
        count = niOffset+2;
        pow = 0;
        while(count > niOffset) {
            m_remoteParent16 += QString(packet.at(count)).toInt() << pow*8;
            count--;
            pow++;
        }

        // Get Device Type
        m_deviceType = packet.at(niOffset+3);

        // Get Source Event
        m_sourceEvent = packet.at(niOffset+4);

        // Get Digi Profile ID
        count = niOffset+6;
        pow = 0;
        while(count > niOffset+4) {
            m_digiProfileId += QString(packet.at(count)).toInt() << pow*8;
            count--;
            pow++;
        }

        // Get Digi Manufacturer ID
        count = niOffset + 8;
        pow = 0;
        while(count > niOffset+6) {
            m_digiManufacturerId += QString(packet.at(count)).toInt() << pow*8;
            count--;
            pow++;
        }

        // Get Checksum
        setChecksum(packet.at(packetSize-1));
    }

exit:
    return bRet;
}

QString ZBIONodeIdentificationResponse::toString() {
    QString str;
    str.append(QString("Raw packet                   : 0x%1\n").arg(QString(packet().toHex())));
    str.append(QString("Start delimiter              : 0x%1\n").arg(QString::number(startDelimiter(), 16)));
    str.append(QString("Frame type                   : %1 (0x%2)\n").arg(frameTypeToString(frameType())).arg(QString::number(frameType(), 16)));
    str.append(QString("Length                       : %1 bytes\n").arg(length()));
    if(!m_data.isEmpty())
    str.append(QString("Data                         : 0x%1\n").arg(QString(m_data.toHex())));
    else
    str.append(QString("Data                         : No data\n"));
    str.append(QString("Sender Address 64bits        : 0x%1\n").arg(m_senderAddr64, 0, 16));
    str.append(QString("Sender Address 16bits        : 0x%1\n").arg(m_senderAddr16, 0, 16));
    str.append(QString("Receive Options              : 0x%1\n").arg(m_receiveOptions, 0, 16));
    str.append(QString("Remote Address 16bits        : 0x%1\n").arg(m_remoteAddr16, 0, 16));
    str.append(QString("Remote Address 64bits        : 0x%1\n").arg(m_remoteAddr64, 0, 16));
    str.append(QString("Node Identifier              : %1\n").arg(m_nodeIdentifier));
    str.append(QString("Remote Parent Address 16bits : 0x%1\n").arg(m_remoteParent16, 0, 16));
    str.append(QString("Device Type                  : 0x%1\n").arg(m_deviceType, 0, 16));
    str.append(QString("Source Event                 : 0x%1\n").arg(m_sourceEvent, 0, 16));
    str.append(QString("Digi Profile ID              : 0x%1\n").arg(m_digiProfileId, 0, 16));
    str.append(QString("Digi Manufacturer ID         : 0x%1\n").arg(m_digiManufacturerId, 0, 16));
    str.append(QString("Checksum                     : %1\n").arg(checksum()));

    return str;
}

} } // END namepsace
