#ifndef ATCOMMANDFRAME_H
#define ATCOMMANDFRAME_H

#include "digimeshframe.h"
#include <QByteArray>

/**
 * @brief The ATCommandFrame class is used to query or set module parameters on the local device.
 *
 * This API command applies changes after executing the command.
 * (Changes made to module parameters take effect once changes are applied.)
 *
 * @sa ATCommandResponseFrame
 */
class ATCommandFrame : public DigiMeshFrame
{
    Q_OBJECT
public:
    enum ATCommand {
        Command_Undefined = 0, /**< Undefined AT Command. Invalid value */
        // Addressing
        Command_DH = 0x4448,
        Command_DL = 0x444C,
        Command_MY = 0x4D59,
        Command_MP = 0x4D50,
        Command_NC = 0x4E43,
        Command_SH = 0x5348,
        Command_SL = 0x534C,
        Command_NI = 0x4E49,
        Command_SE = 0x5345,
        Command_DE = 0x4445,
        Command_CI = 0x4349,
        Command_TO = 0x544F,
        Command_NP = 0x4E50,
        Command_DD = 0x4444,
        Command_CR = 0x4352,
        // Networking
        Command_CH = 0x4348,
        Command_DA = 0x4441,
        Command_ID = 0x4944,
        Command_OP = 0x4F50,
        Command_NH = 0x4E48,
        Command_BH = 0x4248,
        Command_OI = 0x4F49,
        Command_NT = 0x4E54,
        Command_NO = 0x4E4F,
        Command_SC = 0x5343,
        Command_SD = 0x5344,
        Command_ZS = 0x5A53,
        Command_NJ = 0x4E4A,
        Command_JV = 0x4A56,
        Command_NW = 0x4E57,
        Command_JN = 0x4A4E,
        Command_AR = 0x4152,
        // Security
        Command_EE = 0x4545,
        Command_EO = 0x454F,
        Command_NK = 0x4E4B,
        Command_KY = 0x4B59,
        // RF Interfacing
        Command_PL = 0x504C,
        Command_PM = 0x504D,
        Command_DB = 0x4442,
        Command_PP = 0x5050,
        // Serial Interfacing (I/O)
        Command_AP = 0x4150,
        Command_AO = 0x414F,
        Command_BD = 0x4244,
        Command_NB = 0x4E42,
        Command_SB = 0x5342,
        Command_RO = 0x524F,
        Command_D7 = 0x4437,
        Command_D6 = 0x4436,
        // I/O Command_s
        Command_IR = 0x4952,
        Command_IC = 0x4943,
        Command_P0 = 0x5030,
        Command_P1 = 0x5031,
        Command_P2 = 0x5032,
        Command_P3 = 0x5033,
        Command_D0 = 0x4430,
        Command_D1 = 0x4431,
        Command_D2 = 0x4432,
        Command_D3 = 0x4433,
        Command_D4 = 0x4434,
        Command_D5 = 0x4435,
        Command_D8 = 0x4438,
        Command_LT = 0x4C54,
        Command_PR = 0x5052,
        Command_RP = 0x5250,
        Command_V  = 0x2556,
        Command_VP = 0x562B,
        Command_TP = 0x5450,
        Command_VR = 0x5652,
        Command_HV = 0x4856,
        Command_AI = 0x4149,
        // AT Command_ Options
        Command_CT = 0x4354,
        Command_CN = 0x434E,
        Command_GT = 0x4754,
        Command_CC = 0x4343,
        // Sleep Command_s
        Command_SM = 0x534D,
        Command_SN = 0x534E,
        Command_SP = 0x5350,
        Command_ST = 0x5354,
        Command_SO = 0x534F,
        Command_WH = 0x5748,
        Command_SI = 0x5349,
        Command_PO = 0x504F,
        // Execution Command_s
        Command_AC = 0x4143,
        Command_WR = 0x5752,
        Command_RE = 0x5245,
        Command_FR = 0x4652,
        Command_NR = 0x4E52,
        Command_CB = 0x4342,
        Command_ND = 0x4E44,
        Command_DN = 0x444E,
        Command_IS = 0x4953,
        Command_1S = 0x3153
    };

    explicit ATCommandFrame(QObject *parent = 0);

    void setCommand(const ATCommand command);
    void setCommand(const QString &command);
    void setParameter(const QByteArray &param);

    QByteArray command() const;
    QByteArray parameter() const;

    void assemblePacket();

    static QString atCommandToString(const ATCommand command);
    static QByteArray atCommandToByteArray(const ATCommand command);
    static ATCommand atCommandFromByteArray(const QByteArray & command);

 private:
    QByteArray m_command;
    QByteArray m_parameter;
};

#endif // ATCOMMANDPACKET_H

/**
 * @enum ATCommandFrame::ATCommand
 * @brief The ATCommand enum defines the AT commands codes
 *
 * @var ATCommandFrame::Command_DH
 * <B>Destination Address High</B>.
 * Set/Get the upper 32 bits of the 64-bit destination address.
 * When combined with DL, it defines the 64-bit destination address for data transmission.
 * Special definitions for DH and DL include 0x000000000000FFFF (broadcast) and 0x0000000000000000 (coordinator).
 *
 * Parameter range : 0 - 0xFFFFFFFF<BR>
 * Default : 0
 * @var ATCommandFrame::Command_CI
 * <B>Cluster Identifier</B>.
 * Set/read Zigbee application layer cluster ID value.
 * This value will be used as the cluster ID for all data transmissions.
 * CI is only supported in AT firmware.
 * The default value0x11 (Transparent data cluster ID).
 *
 * Parameter range : 0 - 0xFFFF<BR>
 * Default : 0x11
 *
 * @var ATCommandFrame::Command_DL
 * <B>Destination Address Low</B>. Set/Get the lower 32 bits of the 64-bit destination address.
 * When combined with DH, it defines the 64-bit destination address for data transmissions.
 * Special definitions for DH and DL include 0x000000000000FFFF (broadcast) and 0x0000000000000000 (coordinator).
 *
 * Parameter range : 0 - 0xFFFFFFFF<BR>
 * Default : 0xFFFF(Coordinator), 0 (Router/End Device)
 *
 * @var ATCommandFrame::Command_MY
 * <B>16-bit Network Address</B>.
 * Read the 16-bit network address of the module. A value of 0xFFFE means the module has not joined a ZigBee network.
 *
 * Parameter range : 0 - 0xFFFE [read-only]<BR>
 * Default : 0xFFFE
 *
 * @var ATCommandFrame::Command_MP
 * <B>16-bit Parent Network Address</B>.
 * Read the 16-bit network address of the module's parent. A value of 0xFFFE means the module does not have a parent.
 *
 * Parameter range : 0 - 0xFFFE [read-only]<BR>
 * Default : 0xFFFE
 *
 * @var ATCommandFrame::Command_NC
 * <B>Number of Remaining Children</B>. Read the number of end device children that can join the device.
 * If NC returns 0, then the device cannot allow any more end device children to join.
 *
 * Parameter range : 0 - MAX_CHILDREN (maximum varies)<BR>
 * Default : read-only
 *
 * @var ATCommandFrame::Command_SH
 * <B>Serial Number High</B>. Read the high 32 bits of the module's unique 64-bit address.
 *
 * Parameter range : 0 - 0xFFFFFFFF [read-only]<BR>
 * Default : factory-set
 *
 * @var ATCommandFrame::Command_SL
 * <B>Serial Number Low</B>. Read the low 32 bits of the module's unique 64-bit address.
 *
 * Parameter range : 0 - 0xFFFFFFFF [read-only]<BR>
 * Default : factory-set
 *
 * @var ATCommandFrame::Command_NI
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
 * @var ATCommandFrame::Command_SE
 * <B>Source Endpoint</B>.
 * Set/read the ZigBee application layer source endpoint value. This value will be used as the source endpoint for all data transmissions.
 * SE is only supported in AT firmware. The default value 0xE8 (Data endpoint) is the Digi data endpoint
 *
 * Parameter range : 0 - 0xFF<BR>
 * Default : 0xE8
 *
 * @var ATCommandFrame::Command_DE
 * <B>Destination Endpoint</B>.
 * Set/read Zigbee application layer destination ID value. This value will be used as the destination endpoint all data transmissions.
 * DE is only supported in AT firmware.The default value (0xE8) is the Digi data endpoint.
 *
 * Parameter range : 0 - 0xFF<BR>
 * Default : 0xE8
 *
 * @var ATCommandFrame::Command_TO
 *
 * @var ATCommandFrame::Command_NP
 * <B>Maximum RF Payload Bytes</B>.
 * This value returns the maximum number of RF payload bytes that can be sent in a unicast transmission.
 * If APS encryption is used (API transmit option bit enabled), the maximum payload size is reduced by 9 bytes.
 * If source routing is used (AR < 0xFF), the maximum payload size is reduced further.
 * @note NP returns a hexadecimal value. (e.g. if NP returns 0x54, this is equivalent to 84 bytes)
 *
 * @var ATCommandFrame::Command_DD
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
 * @var ATCommandFrame::Command_CR
 *
 * @var ATCommandFrame::Command_CH
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
 * @var ATCommandFrame::Command_DA
 * <B>Force Disassociation</B>.
 * End device will immediately disassociate from a Coordinator (if associated) and reattempt to associate.
 *
 * @var ATCommandFrame::Command_ID
 * <B>Extended PAN ID</B>.
 * Set/read the 64-bit extended PAN ID.
 * If set to 0, the coordinator will select a random extended PAN ID, and the router / end device will join any extended PAN ID.
 * Changes to ID should be written to non-volatile memory using the WR command to preserve the ID setting if a power cycle occurs.
 *
 * Parameter range : 0 - 0xFFFFFFFFFFFFFFFF<BR>
 * Default : 0
 *
 * @var ATCommandFrame::Command_OP = 0x4F50,
 * @var ATCommandFrame::Command_NH = 0x4E48,
 * @var ATCommandFrame::Command_BH = 0x4248,
 * @var ATCommandFrame::Command_OI = 0x4F49,
 * @var ATCommandFrame::Command_NT = 0x4E54,
 * @var ATCommandFrame::Command_NO = 0x4E4F,
 * @var ATCommandFrame::Command_SC = 0x5343,
 * @var ATCommandFrame::Command_SD = 0x5344,
 * @var ATCommandFrame::Command_ZS = 0x5A53,
 * @var ATCommandFrame::Command_NJ = 0x4E4A,
 * @var ATCommandFrame::Command_JV = 0x4A56,
 * @var ATCommandFrame::Command_NW = 0x4E57,
 * @var ATCommandFrame::Command_JN = 0x4A4E,
 * @var ATCommandFrame::Command_AR = 0x4152,
 * // Security
 * @var ATCommandFrame::Command_EE = 0x4545,
 * @var ATCommandFrame::Command_EO = 0x454F,
 * @var ATCommandFrame::Command_NK = 0x4E4B,
 * @var ATCommandFrame::Command_KY = 0x4B59,
 * // RF Interfacing
 * @var ATCommandFrame::Command_PL = 0x504C,
 * @var ATCommandFrame::Command_PM = 0x504D,
 * @var ATCommandFrame::Command_DB = 0x4442,
 * @var ATCommandFrame::Command_PP = 0x5050,
 * // Serial Interfacing (I/O)
 * @var ATCommandFrame::Command_AP = 0x4150,
 * @var ATCommandFrame::Command_AO = 0x414F,
 * @var ATCommandFrame::Command_BD = 0x4244,
 * @var ATCommandFrame::Command_NB = 0x4E42,
 * @var ATCommandFrame::Command_SB = 0x5342,
 * @var ATCommandFrame::Command_RO = 0x524F,
 * @var ATCommandFrame::Command_D7 = 0x4437,
 * @var ATCommandFrame::Command_D6 = 0x4436,
 * // I/O @var ATCommandFrame::Command_s
 * @var ATCommandFrame::Command_IR = 0x4952,
 * @var ATCommandFrame::Command_IC = 0x4943,
 * @var ATCommandFrame::Command_P0 = 0x5030,
 * @var ATCommandFrame::Command_P1 = 0x5031,
 * @var ATCommandFrame::Command_P2 = 0x5032,
 * @var ATCommandFrame::Command_P3 = 0x5033,
 * @var ATCommandFrame::Command_D0 = 0x4430,
 * @var ATCommandFrame::Command_D1 = 0x4431,
 * @var ATCommandFrame::Command_D2 = 0x4432,
 * @var ATCommandFrame::Command_D3 = 0x4433,
 * @var ATCommandFrame::Command_D4 = 0x4434,
 * @var ATCommandFrame::Command_D5 = 0x4435,
 * @var ATCommandFrame::Command_D8 = 0x4438,
 * @var ATCommandFrame::Command_LT = 0x4C54,
 * @var ATCommandFrame::Command_PR = 0x5052,
 * @var ATCommandFrame::Command_RP = 0x5250,
 * @var ATCommandFrame::Command_V  = 0x2556,
 * @var ATCommandFrame::Command_VP = 0x562B,
 * @var ATCommandFrame::Command_TP = 0x5450,
 * @var ATCommandFrame::Command_VR = 0x5652,
 * @var ATCommandFrame::Command_HV = 0x4856,
 * @var ATCommandFrame::Command_AI = 0x4149,
 * // AT @var ATCommandFrame::Command_ Options
 * @var ATCommandFrame::Command_CT = 0x4354,
 * @var ATCommandFrame::Command_CN = 0x434E,
 * @var ATCommandFrame::Command_GT = 0x4754,
 * @var ATCommandFrame::Command_CC = 0x4343,
 * // Sleep @var ATCommandFrame::Command_s
 * @var ATCommandFrame::Command_SM = 0x534D,
 * @var ATCommandFrame::Command_SN = 0x534E,
 * @var ATCommandFrame::Command_SP = 0x5350,
 * @var ATCommandFrame::Command_ST = 0x5354,
 * @var ATCommandFrame::Command_SO = 0x534F,
 * @var ATCommandFrame::Command_WH = 0x5748,
 * @var ATCommandFrame::Command_SI = 0x5349,
 * @var ATCommandFrame::Command_PO = 0x504F,
 * // Execution @var ATCommandFrame::Command_s
 * @var ATCommandFrame::Command_AC = 0x4143,
 * @var ATCommandFrame::Command_WR = 0x5752,
 * @var ATCommandFrame::Command_RE = 0x5245,
 * @var ATCommandFrame::Command_FR = 0x4652,
 * @var ATCommandFrame::Command_NR = 0x4E52,
 * @var ATCommandFrame::Command_CB = 0x4342,
 * @var ATCommandFrame::Command_ND = 0x4E44,
 * @var ATCommandFrame::Command_DN = 0x444E,
 * @var ATCommandFrame::Command_IS = 0x4953,
 * @var ATCommandFrame::Command_1S = 0x3153
 */
