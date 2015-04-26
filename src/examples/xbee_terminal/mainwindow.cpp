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
    xbee = new XBee(this);
    xbee->setMode(XBee::CommandMode);

    ui->setupUi(this);
    ui->sendButton->setEnabled(false);
    ui->serialCommand->setEnabled(false);

    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(onOpenSerialPortButtonClicked()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(onSendCommandButtonClicked()));
    connect(xbee, SIGNAL(rawDataReceived(QByteArray)), this, SLOT(onRawDataReceived(QByteArray)));

    foreach(QSerialPortInfo port, QSerialPortInfo::availablePorts())
    {
        ui->serialCombo->addItem(port.portName(), port.systemLocation());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenSerialPortButtonClicked()
{
    bool success = false;
    QString serialPort = ui->serialCombo->currentData().toString();
    success = xbee->setSerialPort(serialPort);

    if(success) {
        success = xbee->open();
    }

    ui->sendButton->setEnabled(success);
    ui->serialCommand->setEnabled(success);

    log(success ? QString("Serial port %1 opened").arg(serialPort) : QString("Failed to open serial port %1").arg(serialPort));
}

void MainWindow::onSendCommandButtonClicked()
{
    QString cmd = ui->serialCommand->text();
    QByteArray data;
    ui->serialCommand->clear();

    data = QByteArray(cmd.toStdString().data());
    log(QString("> ").append(data));

    if(data != "+++") {
        data.append(0x0D);
    }
    xbee->sendCommandAsync(data);
}

void MainWindow::onRawDataReceived(const QByteArray &data)
{
    QByteArray d = data;
    d.remove(data.size()-1, 1);
    //log(QString("Received \"").append(d).append("\""));
    log(QString().append(d));
}

void MainWindow::log(const QString &log)
{
    QString text = ui->console->toPlainText();
    text.append(log).append("\n");
    ui->console->setPlainText(text);
    ui->console->verticalScrollBar()->setValue(ui->console->verticalScrollBar()->maximum());
}
