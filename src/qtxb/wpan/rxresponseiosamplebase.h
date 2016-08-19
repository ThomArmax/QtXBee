/*
 * Copyright (C) 2015 ThomArmax (Thomas COIN)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * Thomas COIN <esvcorp@gmail.com> 18/04/2015
 */

#ifndef RxRESPONSEIOSAMPLEBASE_H
#define RxRESPONSEIOSAMPLEBASE_H

#include "RxBaseResponse"

#include <QObject>

namespace QtXBee {
namespace Wpan {

/**
 * @todo Implement RxResponseIoSampleBase class
 * @note Not implemented
 */
class RxResponseIoSampleBase : public RxBaseResponse
{
    Q_OBJECT
public:
    enum Pin {
        ADC5 = 16384,
        ADC4 = 8192,
        ADC3 = 4096,
        ADC2 = 2048,
        ADC1 = 1024,
        ADC0 = 512,
        DIO8 = 256,
        DIO7 = 128,
        DIO6 = 64,
        DIO5 = 32,
        DIO4 = 16,
        DIO3 = 8,
        DIO2 = 4,
        DIO1 = 2,
        DIO0 = 1
    };
    Q_DECLARE_FLAGS(ChannelMask, Pin)

    explicit        RxResponseIoSampleBase  (QObject *parent = 0);
    virtual         ~RxResponseIoSampleBase ();

    // Reimplemented from RxBaseResponse
    virtual void    clear                   () Q_DECL_OVERRIDE;
    virtual QString toString                () Q_DECL_OVERRIDE;

    void            setChannelMask          (ChannelMask mask);
    ChannelMask     channelMask             () const;

    void            setSampleCount          (const quint8 count);
    quint8          sampleCount             () const;

protected:
    virtual bool    parseApiSpecificData    (const QByteArray &data) Q_DECL_OVERRIDE;

protected:
    quint8          m_samplesCount;
    ChannelMask     m_channelMask;
};

}} // END namespace

#endif // RxRESPONSEIOSAMPLEBASE_H
