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
    xbee->serialPort()->write(data);
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
