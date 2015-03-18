#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "xbee.h"

namespace Ui {
class MainWindow;
}

namespace Armax {
namespace Datamodels {
class ListModel;
}
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openSelectedSerialPort();

private:
    Ui::MainWindow *ui;
    XBee * xbee;
    Armax::Datamodels::ListModel *paramsModel;
};

#endif // MAINWINDOW_H
