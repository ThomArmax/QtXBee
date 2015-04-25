#include <QCoreApplication>
#include <XBee>

using namespace QtXBee;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    XBee xb("/dev/ttyUSB0");

    if(!xb.open()) {
        // Handle error
    }

    // Your code here

    return 0;
}
