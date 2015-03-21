#ifndef ATCOMMAND_H
#define ATCOMMAND_H

#include "digimeshpacket.h"
#include <QByteArray>

/**
 * @brief The ATCommand class is used to query or set module parameters on the local device.
 *
 * This API command applies changes after executing the command.
 * (Changes made to module parameters take effect once changes are applied.)
 *
 * @sa ATCommandResponse
 */
class ATCommand : public DigiMeshPacket
{
    Q_OBJECT
public:
    enum ATCommandType {
        Command_Undefined = 0,
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

    explicit ATCommand(QObject *parent = 0);

    void setCommand(const ATCommandType command);
    void setCommand(const QString &command);
    void setParameter(const QByteArray &array);

    QByteArray command() const;
    QByteArray parameter() const;

    void assemblePacket();

    static QString atCommandToString(const ATCommandType command);
    static QByteArray atCommandToByteArray(const ATCommandType command);
    static ATCommandType atCommandFromByteArray(const QByteArray & command);

 private:
    QByteArray m_command;
    QByteArray m_parameter;
};

#endif // ATCOMMANDPACKET_H
