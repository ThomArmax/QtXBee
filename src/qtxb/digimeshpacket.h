#ifndef DIGIMESHPACKET_H
#define DIGIMESHPACKET_H

#include <QByteArray>
#include <QObject>

class DigiMeshPacket : public QObject
{
    Q_OBJECT
public:
    enum APIFrameType {
        Undefined                           = 0x00,
        ATCommandFrame                      = 0x08,
        ATCommandQueueFrame                 = 0x09,
        TXRequestFrame                      = 0x10,
        TXRequestExplicitFrame              = 0x11,
        RemoteCommandRequestFrame           = 0x17,
        ATCommandResponseFrame              = 0x88,
        ModemStatusFrame                    = 0x8A,
        TransmitStatusFrame                 = 0x8B,
        RXIndicatorFrame                    = 0x90,
        RXIndicatorExplicitFrame            = 0x91,
        NodeIdentificationIndicatorFrame    = 0x95,
        RemoteCommandResponseFrame          = 0x97
    };

    explicit DigiMeshPacket(QObject *parent = 0);

    void setStartDelimiter(unsigned sd);
    void setLength(unsigned l);
    void setFrameType(APIFrameType type);
    void setFrameId(unsigned id);
    void setChecksum(unsigned cs);

    QByteArray packet() const;
    unsigned startDelimiter() const;
    u_int16_t length() const;
    APIFrameType frameType() const;
    unsigned frameId() const;
    unsigned checksum() const;

    virtual void assemblePacket();
    virtual QString toString();
    static QString frameTypeToString(const APIFrameType type);

protected:
    void createChecksum(QByteArray array);

protected:
    QByteArray m_packet;
    unsigned m_startDelimiter;
    u_int16_t m_length;
    APIFrameType m_frameType;
    unsigned m_frameId;
    unsigned m_checksum;
};

#endif // DIGIMESHPACKET_H
