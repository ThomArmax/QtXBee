#include <QCoreApplication>
#include <XBee>

using namespace QtXBee;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    XBee xb;

    xb.setSerialPort("/dev/ttyUSB0");
    xb.setSerialPortConfiguration(QSerialPort::Baud9600,
                                  QSerialPort::Data8,
                                  QSerialPort::NoParity,
                                  QSerialPort::OneStop,
                                  QSerialPort::NoFlowControl);

    if(!xb.open()) {
        // Handle error
    }

    // Your code here

    return 0;
}
