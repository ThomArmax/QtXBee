#include "byteutils.h"

namespace QtXBee {

QByteArray ByteUtils::uintToByteArray(quint8 number)
{
    return QByteArray::number(number);
}

QByteArray ByteUtils::uintToByteArray(quint16 number)
{
    QByteArray array;
    int i = 0;
    for(i=1; i>=0; i--) {
        array.append(number >> (i*8)&0xFF);
    }
    return array;
}

QByteArray ByteUtils::uintToByteArray(quint32 number)
{
    QByteArray array;
    int i = 0;
    for(i=3; i>=0; i--) {
        array.append(number >> (i*8)&0xFF);
    }
    return array;
}

QByteArray ByteUtils::uintToByteArray(quint64 number)
{
    QByteArray array;
    int i = 0;
    for(i=7; i>=0; i--) {
        array.append(number >> (i*8)&0xFF);
    }
    return array;
}

} // END namespace
