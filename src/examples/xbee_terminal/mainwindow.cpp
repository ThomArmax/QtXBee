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
#include "xbee.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtWidgets/QScrollBar>
#include <QMessageBox>

using namespace QtXBee;

/**
 * @example mainwindow.cpp
 * A description of the example file, causes the example file to show up in
 * Examples
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    xbee = new XBee(this);                  // Instanciate the XBee
    xbee->setMode(XBee::CommandMode);       // Put the XBee in Command mode (needed)

    ui->setupUi(this);
    ui->sendButton->setEnabled(false);      // Disable the send button
    ui->serialCommand->setEnabled(false);   // Disabled the command line edit
                                            // (where the user enter the data to send)

    // Connects the "Open" button
    connect(ui->openButton, SIGNAL(clicked()),
            this, SLOT(onOpenSerialPortButtonClicked()));

    // Connects the "Send" button
    connect(ui->sendButton, SIGNAL(clicked()),
            this, SLOT(onSendCommandButtonClicked()));

    // Connects the XBee to catch the received data from the serial port
    connect(xbee, SIGNAL(rawDataReceived(QByteArray)),
            this, SLOT(onRawDataReceived(QByteArray)));

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

// Called when the user clicks on the "Open" button (to open the serial port)
void MainWindow::onOpenSerialPortButtonClicked()
{
    bool success = false;
    QString serialPort = ui->serialCombo->currentData().toString();
    success = xbee->setSerialPort(serialPort);

    if(success) {
        success = xbee->open();
    }

    // Enables the "Send" button in case the serial port has been successfully opened
    ui->sendButton->setEnabled(success);
    // Enables the command line edit in case the serial port has been successfully opened
    ui->serialCommand->setEnabled(success);

    // Logs the serial port open status
    log(success ?
            QString("Serial port %1 opened").arg(serialPort) :
            QString("Failed to open serial port %1").arg(serialPort)
            );
}

// Called when the user clicks on the "Send" button (to send the data to the XBee module)
void MainWindow::onSendCommandButtonClicked()
{
    // Gets the command entered by the user in the command line edit
    QString cmd = ui->serialCommand->text();
    QByteArray data;
    ui->serialCommand->clear(); // Clears the command line edit

    data = QByteArray(cmd.toStdString().data());
    log(QString("> ").append(data)); // Log the command entered by the used

    // Append the \n (carriage return) character if the entered command is not
    // +++ (which is the command to put the XBee module in command mode)
    if(data != "+++") {
        data.append(0x0D);
    }

    // Sends the data to the XBee module
    xbee->sendCommandAsync(data);
}

// Called when receiving data on the serial port
void MainWindow::onRawDataReceived(const QByteArray &data)
{
    QByteArray d = data;
    d.remove(data.size()-1, 1);
    log(QString().append(d));
}

// Writes informations in the console wigdet
void MainWindow::log(const QString &log)
{
    QString text = ui->console->toPlainText();
    text.append(log).append("\n");
    ui->console->setPlainText(text);
    ui->console->verticalScrollBar()->setValue(ui->console->verticalScrollBar()->maximum());
}
