#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <XBee>
#include <ATCommand>
#include <ATCommandResponse>

#define SERIAL_PORT "/dev/ttyUSB0"

using namespace QtXBee;

class XbeeCommandsSendTest : public QObject
{
    Q_OBJECT

public:
    XbeeCommandsSendTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testFrameId();
    void testATCommand();

private:
    XBee * m_xbee;
};

XbeeCommandsSendTest::XbeeCommandsSendTest()
{
    m_xbee = NULL;
}

void XbeeCommandsSendTest::initTestCase()
{
    m_xbee = new XBee();
    bool success = false;
    QVERIFY2(m_xbee != NULL, "Failed to instanciante XBee class");

    success = m_xbee->setSerialPort(SERIAL_PORT);
    QVERIFY2(success == true, "Failed to set serial port");

    success = m_xbee->open();
    QVERIFY2(success == true, "Failed to open serial port");
}

void XbeeCommandsSendTest::cleanupTestCase()
{
    m_xbee->close();
    delete m_xbee;
}

void XbeeCommandsSendTest::testFrameId()
{
    ATCommand at;
    ATCommandResponse * rep = NULL;

    at.setCommand(ATCommand::ATMY);

    // Auto frame id
    for(int i=1; i<=512; i++) {
        rep = m_xbee->sendATCommandSync(&at);
        QVERIFY2(rep != NULL, "No response to AT command");

        QVERIFY2(at.frameId() == rep->frameId(),
                 QString("Mistmatching frame id for iteration %1, the request and the response have a different frame id (expected %2, got %3").
                 arg(i).
                 arg(at.frameId()).
                 arg(rep->frameId()).
                 toStdString().c_str());
        delete rep;
    }

    // Manual frame id
    for(int i=1; i<=512; i++) {
        quint8 frameId = 12;
        at.setFrameId(frameId);
        rep = m_xbee->sendATCommandSync(&at);
        QVERIFY2(rep != NULL, "No response to AT command");

        QVERIFY2(at.frameId() == frameId,
                 QString("Mistmatching frame id for iteration %1, the request's frame id changed after calling send (expected %2, got %3").
                 arg(i).
                 arg(frameId).
                 arg(at.frameId()).
                 toStdString().c_str());

        QVERIFY2(at.frameId() == rep->frameId(),
                 QString("Mistmatching frame id for iteration %1, the request and the response have a different frame id (expected %2, got %3").
                 arg(i).
                 arg(at.frameId()).
                 arg(rep->frameId()).
                 toStdString().c_str());
        delete rep;
    }
}

void XbeeCommandsSendTest::testATCommand()
{
    ATCommand at;
    ATCommandResponse * rep = NULL;
    QByteArray param("Test");
    int count = 20;

    at.setCommand(ATCommand::ATNI);
    at.setParameter(param);
    at.assemblePacket();

    QVERIFY2(at.command() == ATCommand::ATNI, "Mismatching AT command");
    QVERIFY2(at.parameter() == param, "Mismatching AT command parameter");

    for(int i=1; i<=count; i++) {
        // Set NI
        rep = m_xbee->sendATCommandSync(&at);
        QVERIFY2(rep != NULL, "No response to AT command");

        QVERIFY2(at.command() == rep->atCommand(),
                 QString("Mistmatching AT command for iteration %1/%2 (expected %3, got %4").
                 arg(i).
                 arg(count).
                 arg(at.command()).
                 arg(rep->atCommand()).
                 toStdString().c_str());

        QVERIFY2(rep->status() == ATCommandResponse::Ok, "AT command failed");
        delete rep;

        // Get NI
        rep = m_xbee->sendATCommandSync("NI");
        QVERIFY2(rep != NULL, "No response to AT command");

        QVERIFY2(at.command() == rep->atCommand(),
                 QString("Mistmatching AT command for iteration %1/%2 (expected %3, got %4").
                 arg(i).
                 arg(count).
                 arg(at.command()).
                 arg(rep->atCommand()).
                 toStdString().c_str());

        QVERIFY2(rep->status() == ATCommandResponse::Ok, "AT command failed");
        QVERIFY2(rep->data() == param, QString("Mistmatching datafor iteration %1/%2 (expected %3, got %4").
                 arg(i).
                 arg(count).
                 arg(QString(param)).
                 arg(QString(rep->data())).
                 toStdString().c_str());
        delete rep;
    }

    // Send invalid AT command
    at.setCommand(ATCommand::ATUndefined);
    rep = m_xbee->sendATCommandSync(&at);

    QVERIFY2(rep != NULL, "No response to AT command");
    QVERIFY2(rep->status() == ATCommandResponse::InvalidCommand,
             QString("Bad command status (expected %1, got %2)").
             arg(ATCommandResponse::InvalidCommand).
             arg(rep->status()).
             toStdString().c_str());

    delete rep;

    // Send invalid AT command parameter
    at.setCommand(ATCommand::ATMY);
    at.setParameter("invalid_param");
    rep = m_xbee->sendATCommandSync(&at);

    QVERIFY2(rep != NULL, "No response to AT command");

    QVERIFY2(rep->status() == ATCommandResponse::InvalidParameter,
             QString("Bad command status (expected %1, got %2").
             arg(ATCommandResponse::InvalidParameter).
             arg(rep->status()).
             toStdString().c_str()
             );
}

QTEST_MAIN(XbeeCommandsSendTest)

#include "tst_xbeecommandssendtest.moc"
