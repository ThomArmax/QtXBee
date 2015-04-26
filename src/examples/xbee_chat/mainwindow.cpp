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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <XBee>
#include "wpan/txrequest16.h"
#include "wpan/txrequest64.h"
#include "wpan/rxresponse16.h"
#include "wpan/rxresponse64.h"
#include "wpan/txstatusresponse.h"

#include <QSerialPort>
#include <QtWidgets/QScrollBar>
#include <QMessageBox>

using namespace QtXBee;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sendButton->setEnabled(false);  // Disables the "Send" button
    ui->data->setEnabled(false);        // Disable the "data" line edit

    xbee = new XBee(this);              // Instanciate the XBee object

    // Connect to the XBee to catch the transmit statuses
    connect(xbee, SIGNAL(receivedTransmitStatus(Wpan::TxStatusResponse*)),
            this, SLOT(onReceivedTransmitStatus(Wpan::TxStatusResponse*)));

    // Connects to the XBee to catch the received packets
    connect(xbee, SIGNAL(receivedRxResponse16(Wpan::RxResponse16*)),
            this, SLOT(onReceivedRxResponse16(Wpan::RxResponse16*)));

    // Connects to the XBee to catch the received packets
    connect(xbee, SIGNAL(receivedRxResponse64(Wpan::RxResponse64*)),
            this, SLOT(onReceivedRxResponse64(Wpan::RxResponse64*)));

    // Connects the "Open" button
    connect(ui->openButton, SIGNAL(clicked()),
            this, SLOT(onOpenSerialPortButtonClicked()));

    // Connects the "Open" button
    connect(ui->sendButton, SIGNAL(clicked()),
            this, SLOT(onSendCommandButtonClicked()));

    // Gets the available serial ports on the system and adds them the combobox
    // in order the user can choose one
    foreach(QSerialPortInfo port, QSerialPortInfo::availablePorts())
    {
        ui->serialCombo->addItem(port.portName(), port.systemLocation());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Called when the user clicks on the "Open" button
void MainWindow::onOpenSerialPortButtonClicked()
{
    bool success = false;
    QString serialPort = ui->serialCombo->currentData().toString();
    success = xbee->setSerialPort(serialPort);

    if(success) {
        success = xbee->open();
    }

    ui->sendButton->setEnabled(success);
    ui->data->setEnabled(success);

    log(success ?
            QString("Serial port %1 opened").arg(serialPort) :
            QString("Failed to open serial port %1").arg(serialPort));
}

// Called when the user clicks on the "Send" button
void MainWindow::onSendCommandButtonClicked()
{
    bool ok = false;
    quint64 addr = ui->addr->text().toULongLong(&ok, 16);

    // If failed to get address from the address line edit
    // we show a popup
    if(!ok) {
        QMessageBox * mess = new QMessageBox(this);
        mess->setText("Error : Failed to get destination address");
        connect(mess, SIGNAL(accepted()), mess, SLOT(deleteLater()));
        connect(mess, SIGNAL(rejected()), mess, SLOT(deleteLater()));
        mess->show();
        return;
    }
    // 64 bits address
    if(addr > 0xFFFF) {
        Wpan::TxRequest64 req;
        req.setDestinationAddress(addr);
        req.setData(ui->data->text().toLatin1());
        xbee->sendAsync(&req);
    }
    // 16 bits address
    else {
        log(ui->data->text().prepend(">> "));
        Wpan::TxRequest16 req;
        req.setDestinationAddress(addr);
        req.setData(ui->data->text().toLatin1());
        req.setFrameId(20);
        xbee->sendAsync(&req);
    }
    ui->data->clear();
}

// Log informations in the "console" text area
void MainWindow::log(const QString &log)
{
    QString text = ui->console->toPlainText();
    text.append(log).append("\n");
    ui->console->setPlainText(text);
    ui->console->verticalScrollBar()->setValue(ui->console->verticalScrollBar()->maximum());
}

// Called when a transmit status is received
void MainWindow::onReceivedTransmitStatus(Wpan::TxStatusResponse * status)
{
    if(status->status() != Wpan::TxStatusResponse::Success) {
        QMessageBox * mess = new QMessageBox(this);
        mess->setText("Error : Transmit failed with status " +
                      TxStatusResponse::statusToString(status->status()));
        connect(mess, SIGNAL(accepted()), mess, SLOT(deleteLater()));
        connect(mess, SIGNAL(rejected()), mess, SLOT(deleteLater()));
        mess->show();
    }
}

// Called when a response is received
void MainWindow::onReceivedRxResponse16(Wpan::RxResponse16 * r)
{
    log(r->data().prepend("<< "));
}

// Called when a response is received
void MainWindow::onReceivedRxResponse64(Wpan::RxResponse64 * r)
{
    log(r->data().prepend("<< "));
}
