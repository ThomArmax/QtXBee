#ifndef BYTEUTILS_H
#define BYTEUTILS_H

#include <QByteArray>

namespace QtXBee {

class ByteUtils
{
public:
    static QByteArray uintToByteArray(quint8 number);
    static QByteArray uintToByteArray(quint16 i);
    static QByteArray uintToByteArray(quint32 i);
    static QByteArray uintToByteArray(quint64 i);
};

} // END namespace

#endif // BYTEUTILS_H
