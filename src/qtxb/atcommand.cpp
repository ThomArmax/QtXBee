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

#include "atcommand.h"

#include <QDebug>

namespace QtXBee {

/**
 * @brief ATCommand's constructor
 * @param parent
 */
ATCommand::ATCommand(QObject *parent) :
    XBeePacket(parent)
{
    setFrameType(XBeePacket::ATCommandId);
    setFrameId(0x01);
}

/**
 * @brief Sets the AT Command
 * @param command
 */
void ATCommand::setCommand(const ATCommandType command)
{
    m_command = command;
}

/**
 * @brief Sets the AT Command from the given QByteArray
 * @param command
 */
void ATCommand::setCommand(const QByteArray &command)
{
    m_command = atCommandFromByteArray(command);
}

/**
 * @brief Sets command's parameter
 * @param param
 */
void ATCommand::setParameter(const QByteArray &param)
{
    m_parameter.clear();
    m_parameter.append(param);
}

/**
 * @brief Returns the AT Command
 * @return the AT Command
 */
ATCommand::ATCommandType ATCommand::command() const
{
    return m_command;
}

/**
 * @brief Returns the command's parameter
 * @return the command's parameter
 */
QByteArray ATCommand::parameter() const
{
    return m_parameter;
}

void ATCommand::assemblePacket()
{
    m_packet.clear();
    m_packet.append(frameType());
    m_packet.append(frameId());
    m_packet.append(atCommandToByteArray(command()));
    m_packet.append(parameter());
    setLength(m_packet.size());
    createChecksum(m_packet);
    m_packet.append(checksum());
    m_packet.insert(0, startDelimiter());
    m_packet.insert(1, (length()>>8)&0xFF);
    m_packet.insert(2, length()&0xFF);
}

QString ATCommand::toString()
{
    QString str;
    str.append(QString("Raw packet      : 0x%1\n").arg(QString(packet().toHex())));
    str.append(QString("Frame id        : %1 (0x%2)\n").arg(frameId(), 0, 16).arg(frameId(), 0, 16));
    str.append(QString("Frame type      : %1 (0x%2)\n").arg(frameTypeToString(frameType())).arg(QString::number(frameType(), 16)));
    str.append(QString("Start delimiter : 0x%1\n").arg(QString::number(startDelimiter(), 16)));
    str.append(QString("Length          : %1 bytes\n").arg(length()));
    str.append(QString("Checksum        : %1\n").arg(checksum()));
    str.append(QString("AT command      : %1 (0x%2)\n").arg(atCommandToString(m_command)).arg(QString::number(m_command, 16)));

    return str;
}

void ATCommand::clear()
{
    XBeePacket::clear();
    m_command = ATUndefined;
    m_parameter.clear();
    setFrameType(XBeePacket::ATCommandId);
    setFrameId(0x01);
}

/**
 * @brief Returns the given ATCommand::ATCommand into QString
 * @param command the ATCommand to be converted into QString
 * @return the given ATCommand into QString
 */
QString ATCommand::atCommandToString(const ATCommandType command)
{
    QString at(atCommandToByteArray(command));
    return at;
}

/**
 * @brief Returns the given ATCommand::ATCommand into QByteArray
 * @param command the ATCommand to be converted into QByteArray
 * @return the given ATCommand into QByteArray
 */
QByteArray ATCommand::atCommandToByteArray(const ATCommandType command)
{
    QByteArray at;
    at.append((command>>8)&0xFF);
    at.append(command&0xFF);
    return at;
}

/**
 * @brief Returns the ATCommand::ATCommand corresponding to the given QByteArray
 * @param command
 * @return the ATCommand::ATCommand corresponding to the given QByteArray.
 */
ATCommand::ATCommandType ATCommand::atCommandFromByteArray(const QByteArray &command)
{
    ATCommand::ATCommandType at;
    at = (ATCommand::ATCommandType) ( ( (command.at(0)&0xFF)<<8) + command.at(1) );

    return at;
}

} // END namepsace
