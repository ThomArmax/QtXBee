#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace QtXBee {
class XBee;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onOpenSerialPortButtonClicked();
    void onSendCommandButtonClicked();
    void onRawDataReceived(const QByteArray & data);

private:
    void log(const QString & log);

private:
    Ui::MainWindow *ui;
    QtXBee::XBee  * xbee;
};

#endif // MAINWINDOW_H
