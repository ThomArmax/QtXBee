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

#ifndef ATCOMMAND_H
#define ATCOMMAND_H

#include "XBeePacket"
#include <QByteArray>

namespace QtXBee {

/**
 * @brief The ATCommand class is used to query or set module parameters on the local device.
 *
 * This API command applies changes after executing the command.
 * (Changes made to module parameters take effect once changes are applied.)
 *
 * API identifier value: 0x08
 *
 * @sa ATCommandResponse
 */
class ATCommand : public XBeePacket
{
    Q_OBJECT
public:
    enum ATCommandType {
        ATUndefined = 0, /**< Undefined AT Command. Invalid value */
        // Serial
        ATWR = 0x5752,
        ATRE = 0x5245,
        ATFR = 0x4652,
        // Addressing
        ATDH = 0x4448,
        ATDL = 0x444C,
        ATMY = 0x4D59,
        ATMP = 0x4D50,
        ATNC = 0x4E43,
        ATSH = 0x5348,
        ATSL = 0x534C,
        ATNI = 0x4E49,
        ATSE = 0x5345,
        ATDE = 0x4445,
        ATCI = 0x4349,
        ATTO = 0x544F,
        ATNP = 0x4E50,
        ATDD = 0x4444,
        ATCR = 0x4352,
        // Networking
        ATCH = 0x4348,
        ATDA = 0x4441,
        ATID = 0x4944,
        ATFP = 0x4650,
        ATAS = 0x4153,
        ATED = 0x4544,
        ATOP = 0x4F50,
        ATRR = 0x5252,
        ATRN = 0x524E,
        ATMM = 0x4D4D,
        ATCE = 0x4345,
        ATNH = 0x4E48,
        ATBH = 0x4248,
        ATOI = 0x4F49,
        ATNT = 0x4E54,
        ATNO = 0x4E4F,
        ATSC = 0x5343,
        ATSD = 0x5344,
        ATZS = 0x5A53,
        ATNJ = 0x4E4A,
        ATJV = 0x4A56,
        ATNW = 0x4E57,
        ATJN = 0x4A4E,
        ATAR = 0x4152,
        ATA1 = 0x4131,
        ATA2 = 0x4132,
        // Security
        ATEE = 0x4545,
        ATEO = 0x454F,
        ATNK = 0x4E4B,
        ATKY = 0x4B59,
        // RF Interfacing
        ATPL = 0x504C,
        ATCA = 0x4341,
        ATPM = 0x504D,
        ATDB = 0x4442,
        ATPP = 0x5050,
        // Serial Interfacing (I/O)
        ATAP = 0x4150,
        ATAO = 0x414F,
        ATBD = 0x4244,
        ATNB = 0x4E42,
        ATSB = 0x5342,
        ATRO = 0x524F,
        ATD7 = 0x4437,
        ATD6 = 0x4436,
        // I/O ATs
        ATIR = 0x4952,
        ATIC = 0x4943,
        ATP0 = 0x5030,
        ATP1 = 0x5031,
        ATP2 = 0x5032,
        ATP3 = 0x5033,
        ATD0 = 0x4430,
        ATD1 = 0x4431,
        ATD2 = 0x4432,
        ATD3 = 0x4433,
        ATD4 = 0x4434,
        ATD5 = 0x4435,
        ATD6 = 0x4436,
        ATD7 = 0x4437,
        ATD8 = 0x4438,
        ATLT = 0x4C54,
        ATPR = 0x5052,
        ATRP = 0x5250,
        ATV  = 0x2556,
        ATVP = 0x562B,
        ATTP = 0x5450,
        ATVR = 0x5652,
        ATHV = 0x4856,
        ATAI = 0x4149,
        // AT AT Options
        ATCT = 0x4354,
        ATCN = 0x434E,
        ATGT = 0x4754,
        ATCC = 0x4343,
        // Sleep ATs
        ATSM = 0x534D,
        ATSN = 0x534E,
        ATSP = 0x5350,
        ATDP = 0x4450,
        ATST = 0x5354,
        ATSO = 0x534F,
        ATWH = 0x5748,
        ATSI = 0x5349,
        ATPO = 0x504F,
        // Execution ATs
        ATAC = 0x4143,
        ATNR = 0x4E52,
        ATCB = 0x4342,
        ATND = 0x4E44,
        ATDN = 0x444E,
        ATIS = 0x4953,
        AT1S = 0x3153
    };

    explicit                ATCommand               (QObject *parent = 0);

    // Reimplemented from XBeePacket
    virtual QString         toString                ();
    virtual void            assemblePacket          ();
    virtual void            clear                   ();

    void                    setCommand              (const ATCommandType command);
    void                    setCommand              (const QByteArray &command);
    void                    setParameter            (const QByteArray &param);

    ATCommandType           command                 () const;
    QByteArray              parameter               () const;

    static QString          atCommandToString       (const ATCommandType command);
    static QByteArray       atCommandToByteArray    (const ATCommandType command);
    static ATCommandType    atCommandFromByteArray  (const QByteArray & command);

 private:
    ATCommandType           m_command;
    QByteArray              m_parameter;
};

} // END namespace

#endif // ATCOMMAND_H
