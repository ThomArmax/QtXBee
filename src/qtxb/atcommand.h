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
        ATOP = 0x4F50,
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
        // Security
        ATEE = 0x4545,
        ATEO = 0x454F,
        ATNK = 0x4E4B,
        ATKY = 0x4B59,
        // RF Interfacing
        ATPL = 0x504C,
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
        ATST = 0x5354,
        ATSO = 0x534F,
        ATWH = 0x5748,
        ATSI = 0x5349,
        ATPO = 0x504F,
        // Execution ATs
        ATAC = 0x4143,
        ATWR = 0x5752,
        ATRE = 0x5245,
        ATFR = 0x4652,
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

/**
 * @enum ATCommand::ATCommandType
 * @brief The ATCommand enum defines the AT commands codes
 *
 * @var ATCommand::ATDH
 * <B>Destination Address High</B>.
 * Set/Get the upper 32 bits of the 64-bit destination address.
 * When combined with DL, it defines the 64-bit destination address for data transmission.
 * Special definitions for DH and DL include 0x000000000000FFFF (broadcast) and 0x0000000000000000 (coordinator).
 *
 * Parameter range : 0 - 0xFFFFFFFF<BR>
 * Default : 0
 * @var ATCommand::ATCI
 * <B>Cluster Identifier</B>.
 * Set/read Zigbee application layer cluster ID value.
 * This value will be used as the cluster ID for all data transmissions.
 * CI is only supported in AT firmware.
 * The default value0x11 (Transparent data cluster ID).
 *
 * Parameter range : 0 - 0xFFFF<BR>
 * Default : 0x11
 *
 * @var ATCommand::ATDL
 * <B>Destination Address Low</B>. Set/Get the lower 32 bits of the 64-bit destination address.
 * When combined with DH, it defines the 64-bit destination address for data transmissions.
 * Special definitions for DH and DL include 0x000000000000FFFF (broadcast) and 0x0000000000000000 (coordinator).
 *
 * Parameter range : 0 - 0xFFFFFFFF<BR>
 * Default : 0xFFFF(Coordinator), 0 (Router/End Device)
 *
 * @var ATCommand::ATMY
 * <B>16-bit Network Address</B>.
 * Read the 16-bit network address of the module. A value of 0xFFFE means the module has not joined a ZigBee network.
 *
 * Parameter range : 0 - 0xFFFE [read-only]<BR>
 * Default : 0xFFFE
 *
 * @var ATCommand::ATMP
 * <B>16-bit Parent Network Address</B>.
 * Read the 16-bit network address of the module's parent. A value of 0xFFFE means the module does not have a parent.
 *
 * Parameter range : 0 - 0xFFFE [read-only]<BR>
 * Default : 0xFFFE
 *
 * @var ATCommand::ATNC
 * <B>Number of Remaining Children</B>. Read the number of end device children that can join the device.
 * If NC returns 0, then the device cannot allow any more end device children to join.
 *
 * Parameter range : 0 - MAX_CHILDREN (maximum varies)<BR>
 * Default : read-only
 *
 * @var ATCommand::ATSH
 * <B>Serial Number High</B>. Read the high 32 bits of the module's unique 64-bit address.
 *
 * Parameter range : 0 - 0xFFFFFFFF [read-only]<BR>
 * Default : factory-set
 *
 * @var ATCommand::ATSL
 * <B>Serial Number Low</B>. Read the low 32 bits of the module's unique 64-bit address.
 *
 * Parameter range : 0 - 0xFFFFFFFF [read-only]<BR>
 * Default : factory-set
 *
 * @var ATCommand::ATNI
 * <B>Node Identifier</B>. Set/read a string identifier.
 * The register only accepts printable ASCII data.
 * In AT Command Mode, a string cannot start with a space. A carriage return ends the command.
 * A command will automatically end when maximum bytes for the string have been entered.
 * This string is returned as part of the ND (Node Discover) command.
 * This identifier is also used with the DN (Destination Node) command.
 * In AT command mode, an ASCII comma (0x2C) cannot be used in the NI string
 *
 * Parameter range : 20-Byte printable ASCII string<BR>
 * Default : ASCII space character (0x20)
 *
 * @var ATCommand::ATSE
 * <B>Source Endpoint</B>.
 * Set/read the ZigBee application layer source endpoint value. This value will be used as the source endpoint for all data transmissions.
 * SE is only supported in AT firmware. The default value 0xE8 (Data endpoint) is the Digi data endpoint
 *
 * Parameter range : 0 - 0xFF<BR>
 * Default : 0xE8
 *
 * @var ATCommand::ATDE
 * <B>Destination Endpoint</B>.
 * Set/read Zigbee application layer destination ID value. This value will be used as the destination endpoint all data transmissions.
 * DE is only supported in AT firmware.The default value (0xE8) is the Digi data endpoint.
 *
 * Parameter range : 0 - 0xFF<BR>
 * Default : 0xE8
 *
 * @var ATCommand::ATTO
 *
 * @var ATCommand::ATNP
 * <B>Maximum RF Payload Bytes</B>.
 * This value returns the maximum number of RF payload bytes that can be sent in a unicast transmission.
 * If APS encryption is used (API transmit option bit enabled), the maximum payload size is reduced by 9 bytes.
 * If source routing is used (AR < 0xFF), the maximum payload size is reduced further.
 * @note NP returns a hexadecimal value. (e.g. if NP returns 0x54, this is equivalent to 84 bytes)
 *
 * @var ATCommand::ATDD
 * <B>Device Type Identifier</B>.
 * Stores a device type value.
 * This value can be used to differentiate different XBee-based devices.
 * Digi reserves the range 0 - 0xFFFFFF.
 * For example, Digi currently uses the following DD values to identify various ZigBee products :
 * <UL>
 * <LI>0x30001 - ConnectPort X8 Gateway</LI>
 * <LI>0x30002 - ConnectPort X4 Gateway</LI>
 * <LI>0x30003 - ConnectPort X2 Gateway</LI>
 * <LI>0x30005 - RS-232 Adapter</LI>
 * <LI>0x30006 - RS-485 Adapter</LI>
 * <LI>0x30007 - XBee Sensor Adapter</LI>
 * <LI>0x30008 - Wall Router</LI>
 * <LI>0x3000A - Digital I/O Adapter</LI>
 * <LI>0x3000B - Analog I/O Adapter</LI>
 * <LI>0x3000C - XStick</LI>
 * <LI>0x3000F - Smart Plug</LI>
 * <LI>0x30011 - XBee Large Display</LI>
 * <LI>0x30012 - XBee Small Display</LI>
 * </UL>
 * <BR>
 * Parameter range : 0 - 0xFFFFFFFF<BR>
 * Default : 0x30000
 *
 * @var ATCommand::ATCR
 *
 * @var ATCommand::ATCH
 * <B>Operating Channel</B>.
 * Read the channel number used for transmitting and receiving between RF modules.
 * Uses 802.15.4 channel numbers.
 * A value of 0 means the device has not joined a PAN and is not operating on any channel.
 *
 * Parameter range :
 * <UL>
 * <LI>XBee 0, 0x0B - 0x1A (Channels 11-26)</LI>
 * <LI>XBee-PRO (S2) 0, 0x0B - 0x18 (Channels 11-24)</LI>
 * <LI>XBee-PRO (S2B) 0, 0x0B - 0x19 (Channels 11-25)</LI>
 * </UL>
 * Default : [read-only]
 * @var ATCommand::ATDA
 * <B>Force Disassociation</B>.
 * End device will immediately disassociate from a Coordinator (if associated) and reattempt to associate.
 *
 * @var ATCommand::ATID
 * <B>Extended PAN ID</B>.
 * Set/read the 64-bit extended PAN ID.
 * If set to 0, the coordinator will select a random extended PAN ID, and the router / end device will join any extended PAN ID.
 * Changes to ID should be written to non-volatile memory using the WR command to preserve the ID setting if a power cycle occurs.
 *
 * Parameter range : 0 - 0xFFFFFFFFFFFFFFFF<BR>
 * Default : 0
 *
 * @var ATCommand::ATOP
 * 0x4F50
 * @var ATCommand::ATNH
 * 0x4E48
 * @var ATCommand::ATBH
 * 0x4248
 * @var ATCommand::ATOI
 * 0x4F49
 * @var ATCommand::ATNT
 * 0x4E54
 * @var ATCommand::ATNO
 * 0x4E4F
 * @var ATCommand::ATSC
 * 0x5343
 * @var ATCommand::ATSD
 * 0x5344
 * @var ATCommand::ATZS
 * 0x5A53
 * @var ATCommand::ATNJ
 * 0x4E4A
 * @var ATCommand::ATJV
 * 0x4A56
 * @var ATCommand::ATNW
 * 0x4E57
 * @var ATCommand::ATJN
 * 0x4A4E
 * @var ATCommand::ATAR
 * 0x4152
 * // Security
 * @var ATCommand::ATEE
 * 0x4545
 * @var ATCommand::ATEO
 * 0x454F
 * @var ATCommand::ATNK
 * 0x4E4B
 * @var ATCommand::ATKY
 * 0x4B59
 * // RF Interfacing
 * @var ATCommand::ATPL
 * 0x504C
 * @var ATCommand::ATPM
 * 0x504D
 * @var ATCommand::ATDB
 * 0x4442
 * @var ATCommand::ATPP
 * 0x5050
 * // Serial Interfacing (I/O)
 * @var ATCommand::ATAP
 * 0x4150
 * @var ATCommand::ATAO
 * 0x414F
 * @var ATCommand::ATBD
 * 0x4244
 * @var ATCommand::ATNB
 * 0x4E42
 * @var ATCommand::ATSB
 * 0x5342
 * @var ATCommand::ATRO
 * 0x524F
 * @var ATCommand::ATD7
 * 0x4437
 * @var ATCommand::ATD6
 * 0x4436
 * // I/O
 * @var ATCommand::ATIR
 * 0x4952
 * @var ATCommand::ATIC
 * 0x4943
 * @var ATCommand::ATP0
 * 0x5030
 * @var ATCommand::ATP1
 * 0x5031
 * @var ATCommand::ATP2
 * 0x5032
 * @var ATCommand::ATP3
 * 0x5033
 * @var ATCommand::ATD0
 * 0x4430
 * @var ATCommand::ATD1
 * 0x4431
 * @var ATCommand::ATD2
 * 0x4432
 * @var ATCommand::ATD3
 * 0x4433
 * @var ATCommand::ATD4
 * 0x4434
 * @var ATCommand::ATD5
 * 0x4435
 * @var ATCommand::ATD8
 * 0x4438
 * @var ATCommand::ATLT
 * 0x4C54
 * @var ATCommand::ATPR
 * 0x5052
 * @var ATCommand::ATRP
 * 0x5250
 * @var ATCommand::ATV
 * 0x2556
 * @var ATCommand::ATVP
 * 0x562B
 * @var ATCommand::ATTP
 * 0x5450
 * @var ATCommand::ATVR
 * 0x5652
 * @var ATCommand::ATHV
 * 0x4856
 * @var ATCommand::ATAI
 * 0x4149
 * // AT @var ATCommand::AT Options
 * @var ATCommand::ATCT
 * 0x4354
 * @var ATCommand::ATCN
 * 0x434E
 * @var ATCommand::ATGT
 * 0x4754
 * @var ATCommand::ATCC
 * 0x4343
 * // Sleep @var ATCommand::ATs
 * @var ATCommand::ATSM
 * 0x534D
 * @var ATCommand::ATSN
 * 0x534E
 * @var ATCommand::ATSP
 * 0x5350
 * @var ATCommand::ATST
 * 0x5354
 * @var ATCommand::ATSO
 * 0x534F
 * @var ATCommand::ATWH
 * 0x5748
 * @var ATCommand::ATSI
 * 0x5349
 * @var ATCommand::ATPO
 * 0x504F
 * // Execution @var ATCommand::ATs
 * @var ATCommand::ATAC
 * 0x4143
 * @var ATCommand::ATWR
 * 0x5752
 * @var ATCommand::ATRE
 * 0x5245
 * @var ATCommand::ATFR
 * 0x4652
 * @var ATCommand::ATNR
 * 0x4E52
 * @var ATCommand::ATCB
 * 0x4342
 * @var ATCommand::ATND
 * 0x4E44
 * @var ATCommand::ATDN
 * 0x444E
 * @var ATCommand::ATIS
 * 0x4953
 * @var ATCommand::AT1S
 * 0x3153
 */

