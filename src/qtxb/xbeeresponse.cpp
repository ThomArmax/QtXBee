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

#include "XBeeResponse"

namespace QtXBee {

/**
 * @brief XBeeResponse's constructor
 * @param parent
 */
XBeeResponse::XBeeResponse(QObject *parent) :
    XBeePacket(parent)
{

}

/**
 * @brief XBeeResponse's destructor
 */
XBeeResponse::~XBeeResponse()
{

}

/**
 * @brief Returns the response's data
 * @return the response's data
 */
QByteArray XBeeResponse::data() const
{
    return m_data;
}

/**
 * @brief Sets the response's data
 * @param data
 */
void XBeeResponse::setData(const QByteArray &data)
{
    m_data.clear();
    m_data = data;
}

void XBeeResponse::clear()
{
    XBeePacket::clear();
    m_data.clear();
}

} // END namepsace
