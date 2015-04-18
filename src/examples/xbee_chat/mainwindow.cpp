#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "wpan/txrequest16.h"
#include "wpan/txrequest64.h"
#include "wpan/rxresponse16.h"
#include "wpan/rxresponse64.h"
#include "wpan/txstatusresponse.h"

#include <QSerialPort>
#include <QtWidgets/QScrollBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sendButton->setEnabled(false);
    ui->data->setEnabled(false);

    xbee = new XBee(this);
    xbee->setMode(XBee::API1Mode);

    connect(xbee, SIGNAL(receivedTransmitStatus(WPAN::TXStatusResponse*)), this, SLOT(onReceivedTransmitStatus(WPAN::TXStatusResponse*)));
    connect(xbee, SIGNAL(receivedRxResponse16(WPAN::RxResponse16*)), this, SLOT(onReceivedRxResponse16(WPAN::RxResponse16*)));
    connect(xbee, SIGNAL(receivedRxResponse64(WPAN::RxResponse64*)), this, SLOT(onReceivedRxResponse64(WPAN::RxResponse64*)));

    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(onOpenSerialPortButtonClicked()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(onSendCommandButtonClicked()));

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
    ui->data->setEnabled(success);

    log(success ? QString("Serial port %1 opened").arg(serialPort) : QString("Failed to open serial port %1").arg(serialPort));
}

void MainWindow::onSendCommandButtonClicked()
{
    bool ok = false;
    quint64 addr = ui->addr->text().toULongLong(&ok, 16);
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
        //log(QString("Sending '%1' to %2 (64 bits addressing)").arg(ui->data->text()).arg(addr));
        WPAN::TXRequest64 req;
        req.setDestinationAddress(addr);
        req.setData(ui->data->text().toLatin1());
        xbee->send(&req);
    }
    // 16 bits address
    else {
        //log(QString("Sending '%1' to %2 (16 bits addressing)").arg(ui->data->text()).arg(addr));
        log(ui->data->text().prepend(">> "));
        WPAN::TXRequest16 req;
        req.setDestinationAddress(addr);
        req.setData(ui->data->text().toLatin1());
        req.setFrameId(20);
        xbee->send(&req);
    }
    ui->data->clear();
}

void MainWindow::log(const QString &log)
{
    QString text = ui->console->toPlainText();
    text.append(log).append("\n");
    ui->console->setPlainText(text);
    ui->console->verticalScrollBar()->setValue(ui->console->verticalScrollBar()->maximum());
}

void MainWindow::onReceivedTransmitStatus(WPAN::TXStatusResponse *)
{
    //log(r->toString());
}

void MainWindow::onReceivedRxResponse16(WPAN::RxResponse16 * r)
{
    log(r->data().prepend("<< "));
}

void MainWindow::onReceivedRxResponse64(WPAN::RxResponse64 * r)
{
    log(r->data().prepend("<< "));
}
