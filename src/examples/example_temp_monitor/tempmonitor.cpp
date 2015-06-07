#include "tempmonitor.h"

#include <XBee>
#include <wpan/TxRequest16>
#include <wpan/RxResponse16>
#include <wpan/TxStatusResponse>
#include <XBeeResponse>

#include <QDebug>
#include <cmath>

typedef union {
    float value;
    u_int8_t bytes[4];
} float_sensor_result;

TempMonitor::TempMonitor(const QString & serialPort, QObject *parent) :
    QObject(parent),
    m_xbee(NULL),
    m_sensorAddr(0xFFFF),
    m_currentTemp(0.0)
{
    bool xbee_success = false;
    m_xbee = new QtXBee::XBee(this);
    xbee_success = m_xbee->setSerialPort(serialPort);
    Q_ASSERT(xbee_success);
    xbee_success = m_xbee->open();
    Q_ASSERT(xbee_success);

    connect(&m_pollingTimer, SIGNAL(timeout()),
            this, SLOT(timerTriggered()));
    connect(m_xbee, SIGNAL(receivedRxResponse16(QtXBee::Wpan::RxResponse16*)),
            this, SLOT(onPacketReceived(QtXBee::Wpan::RxResponse16*)));
}

TempMonitor::~TempMonitor()
{

}

float TempMonitor::currentTemperature() const
{
    return m_currentTemp;
}

void TempMonitor::setTempSensorAddress(const quint16 address)
{
    m_sensorAddr = address;
}

void TempMonitor::start(const uint pollingTime)
{
    m_pollingTimer.start(pollingTime);
}

void TempMonitor::stop()
{
    m_pollingTimer.stop();
}

void TempMonitor::timerTriggered()
{
    QtXBee::Wpan::TxRequest16 req;
    req.setDestinationAddress(m_sensorAddr);
    req.setData("temp");

    m_xbee->sendAsync(&req);
}

void TempMonitor::onPacketReceived(QtXBee::Wpan::RxResponse16 * packet)
{
    QByteArray data;
    float_sensor_result result;
    float temperature;

    data = packet->data();

    if(data.size() == 4) {
        memcpy(&result.bytes, data.data(), 4);

        temperature = result.value;
        qDebug("Temp: %f°C", temperature);

        m_currentTemp = temperature;

        emit temperatureReceived(temperature);
        emit currentTemperatureChanged();
    }
    else {
        qDebug() << "Invalid packet received";
    }
}
