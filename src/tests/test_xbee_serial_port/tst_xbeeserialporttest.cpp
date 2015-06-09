#include <QString>
#include <QtTest>

#include <XBee>
#include <XBeeResponse>
#include <ATCommand>
#include <ATCommandResponse>

#define SERIAL_PORT "/dev/ttyUSB0"

using namespace QtXBee;

class XBeeSerialPortTest : public QObject
{
    Q_OBJECT

public:
    XBeeSerialPortTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void setSerialPortTestCase();
    void uninitializedSerialPortSendTestCase();
    void closedSerialPortSendTestCase();
    void openedSerialPortSendTestCase();
    void openCloseSerialPortTest();
};

XBeeSerialPortTest::XBeeSerialPortTest()
{
}

void XBeeSerialPortTest::initTestCase()
{
}

void XBeeSerialPortTest::cleanupTestCase()
{
}

void XBeeSerialPortTest::setSerialPortTestCase()
{
    bool result = false;
    XBee xbee;

    // Uninitialized serial port test cases
    result = xbee.applyDefaultSerialPortConfig();
    QVERIFY2(result == false, "applyDefaultSerialPortConfig shoud failed when no serial port has been defined");

    result = xbee.setSerialPortConfiguration(QSerialPort::Baud9600,
                                             QSerialPort::Data8,
                                             QSerialPort::NoParity,
                                             QSerialPort::OneStop,
                                             QSerialPort::NoFlowControl);
    QVERIFY2(result == false, "setSerialPortConfiguration should failed when no serial port has bee defined");

    // Wrong serial port
    result = xbee.setSerialPort("wrong_serial_port");
    QVERIFY2(result == true, "Expected to success even if the serial port if wrong");

    result = xbee.setSerialPortConfiguration(QSerialPort::Baud9600,
                                             QSerialPort::Data8,
                                             QSerialPort::NoParity,
                                             QSerialPort::OneStop,
                                             QSerialPort::NoFlowControl);
    QVERIFY2(result == true, "Expected to success even if the serial port if wrong");

    result = xbee.applyDefaultSerialPortConfig();
    QVERIFY2(result == true, "Expected to success even if the serial port if wrong");

    // Good serial port
    result = xbee.setSerialPort(SERIAL_PORT);
    QVERIFY2(result == true, "Expected to success, Failed to set serial port");
    result = xbee.setSerialPort(SERIAL_PORT);
    QVERIFY2(result == true, "Expected to success, Failed to set serial port");

    result = xbee.applyDefaultSerialPortConfig();
    QVERIFY2(result == true, "Expected to success, Failed to apply default serial port configuration");

    result = xbee.setSerialPortConfiguration(QSerialPort::Baud9600,
                                             QSerialPort::Data8,
                                             QSerialPort::NoParity,
                                             QSerialPort::OneStop,
                                             QSerialPort::NoFlowControl);
    QVERIFY2(result == true, "Expected to success, Failed to set serial port configuration");
}

/**
 * @brief Tries to send data to a XBee module without having initilized the serial port
 * @todo Add async send tests
 */
void XBeeSerialPortTest::uninitializedSerialPortSendTestCase()
{
    XBee xbee;
    ATCommand at;
    ATCommandResponse * atrep = NULL;
    XBeeResponse * rep = NULL;

    at.setCommand(ATCommand::ATMY);

    // Synchronous
    rep = xbee.sendSync(&at);
    QVERIFY2(rep == NULL, "Got a response to the sent packet, while serial port is not defined !");

    atrep = xbee.sendATCommandSync(&at);
    QVERIFY2(atrep == NULL, "Got a response to the sent packet, while serial port is not defined !");

    atrep = xbee.sendATCommandSync("MY");
    QVERIFY2(atrep == NULL, "Got a response to the sent packet, while serial port is not defined !");

    // Asynchronous
}

/**
 * @brief Tries to send data to the Xbee module with a closed serial port.
 * @todo Add async send tests
 */
void XBeeSerialPortTest::closedSerialPortSendTestCase()
{
    XBee xbee;
    ATCommand at;
    ATCommandResponse * atrep = NULL;
    XBeeResponse * rep = NULL;
    bool success = false;

    success = xbee.setSerialPort(SERIAL_PORT);
    QVERIFY2(success == true, "Failed to set serial port");

    at.setCommand(ATCommand::ATMY);

    // Synchronous
    rep = xbee.sendSync(&at);
    QVERIFY2(rep == NULL, "Got a response to the sent packet, while serial port is not defined !");

    atrep = xbee.sendATCommandSync(&at);
    QVERIFY2(atrep == NULL, "Got a response to the sent packet, while serial port is not defined !");

    atrep = xbee.sendATCommandSync("MY");
    QVERIFY2(atrep == NULL, "Got a response to the sent packet, while serial port is not defined !");

    // Asynchronous
}

/**
 * @brief Tests the XBee' send methods when the serial port is fully configured and opened
 */
void XBeeSerialPortTest::openedSerialPortSendTestCase()
{
    XBee xbee;
    ATCommand at;
    ATCommandResponse * atrep = NULL;
    XBeeResponse * rep = NULL;
    bool success = false;

    success = xbee.setSerialPort(SERIAL_PORT);
    QVERIFY2(success == true, "Failed to set serial port");

    success = xbee.open();
    QVERIFY2(success == true, "Failed to open serial port");

    at.setCommand(ATCommand::ATMY);

    // Synchronous
    rep = xbee.sendSync(&at);
    QVERIFY2(rep != NULL, "No response received !");
    delete rep;
    rep = NULL;

    atrep = xbee.sendATCommandSync(&at);
    QVERIFY2(atrep != NULL, "No response received !");
    delete atrep;
    atrep = NULL;

    atrep = xbee.sendATCommandSync("MY");
    QVERIFY2(atrep != NULL, "No response received !");
    delete atrep;
    atrep = NULL;

    // Asynchronous
}

void XBeeSerialPortTest::openCloseSerialPortTest()
{
    XBee xbee;
    ATCommand at;
    ATCommandResponse * atrep = NULL;
    XBeeResponse * rep = NULL;
    bool success = false;

    success = xbee.setSerialPort(SERIAL_PORT);
    QVERIFY2(success == true, "Failed to set serial port");

    success = xbee.open();
    QVERIFY2(success == true, "Failed to open serial port");

    at.setCommand(ATCommand::ATMY);

    //-------------> Opened serial port
    // Synchronous
    rep = xbee.sendSync(&at);
    QVERIFY2(rep != NULL, "No response received !");

    atrep = xbee.sendATCommandSync(&at);
    QVERIFY2(atrep != NULL, "No response received !");

    atrep = xbee.sendATCommandSync("MY");
    QVERIFY2(atrep != NULL, "No response received !");

    // Asynchronous

    success = xbee.close();
    QVERIFY2(success == true, "Failed to close serial port");

    //-------------> Closed serial port
    // Synchronous
    rep = xbee.sendSync(&at);
    QVERIFY2(rep == NULL, "Got a response to the sent packet, while serial port is not defined !");
    delete rep;
    rep = NULL;

    atrep = xbee.sendATCommandSync(&at);
    QVERIFY2(atrep == NULL, "Got a response to the sent packet, while serial port is not defined !");
    delete atrep;
    atrep = NULL;

    atrep = xbee.sendATCommandSync("MY");
    QVERIFY2(atrep == NULL, "Got a response to the sent packet, while serial port is not defined !");
    delete atrep;
    atrep = NULL;

    // Asynchronous


    success = xbee.open();
    QVERIFY2(success == true, "Failed to open serial port");

    //-------------> Opened serial port
    // Synchronous
    rep = xbee.sendSync(&at);
    QVERIFY2(rep != NULL, "No response received !");

    atrep = xbee.sendATCommandSync(&at);
    QVERIFY2(atrep != NULL, "No response received !");

    atrep = xbee.sendATCommandSync("MY");
    QVERIFY2(atrep != NULL, "No response received !");

    // Asynchronous


}

QTEST_MAIN(XBeeSerialPortTest)

#include "tst_xbeeserialporttest.moc"
