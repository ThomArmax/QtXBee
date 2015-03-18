#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xbeeparamitem.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtArmax-1.0/datamodels/listmodel.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    xbee(NULL)
{
    xbee = new XBee(this);
    paramsModel = new Armax::Datamodels::ListModel(new XBeeParamItem, this);

    paramsModel->appendRow(new XBeeParamItem("PanID", QVariant(), paramsModel));

    ui->setupUi(this);
    QHeaderView * header = new QHeaderView(Qt::Horizontal, ui->tableView);
    header->setModel(paramsModel);
    ui->tableView->setHorizontalHeader(header);
    ui->tableView->setModel(paramsModel);
    connect(ui->openSerialButton, SIGNAL(clicked()), this, SLOT(openSelectedSerialPort()));

    foreach(QSerialPortInfo port, QSerialPortInfo::availablePorts())
    {
        ui->serialPortSelection->addItem(port.portName(), port.systemLocation());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openSelectedSerialPort()
{
    xbee->setSerialPort(ui->serialPortSelection->currentData().toString());
}
