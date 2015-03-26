#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class XBee;

namespace Ui {
class MainWindow;
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
    XBee  * xbee;
};

#endif // MAINWINDOW_H
