#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "xbee.h"

namespace Ui {
class MainWindow;
}

using namespace QtXBee;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onOpenSerialPortButtonClicked();
    void onSendCommandButtonClicked();
    void onReceivedTransmitStatus(WPAN::TXStatusResponse*);
    void onReceivedRxResponse16(WPAN::RxResponse16*);
    void onReceivedRxResponse64(WPAN::RxResponse64*);

private:
    void log(const QString & log);

private:
    Ui::MainWindow *ui;
    XBee * xbee;
};

#endif // MAINWINDOW_H
