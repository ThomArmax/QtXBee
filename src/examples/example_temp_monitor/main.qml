import QtQuick 2.4
import QtQuick.Window 2.2

import "qchartjs"
import "qchartjs/QChart.js" as Charts
import "monitor.js" as Monitor

Window {
    visible : true
    width   : 800
    height  : 480
    Column {
        anchors.fill    : parent
        spacing         : 20
        anchors.margins : 20
        Text {
            id                  : title
            width               : parent.width
            text                : "Current temperature : " + parseFloat(monitor.currentTemperature).toFixed(1) + "°C"
            color               : "#DCDCDC"
            horizontalAlignment : Text.AlignHCenter
        }

        QChart {
            id                      : tempChart
            width                   : parent.width
            height                  : parent.height - title.height - parent.spacing
            chartAnimated           : true
            chartAnimationEasing    : Easing.InOutElastic
            chartAnimationDuration  : 2000
            chartData               : Monitor.MonitorData
            chartType               : Charts.ChartType.LINE
        }
    }

    Connections {
        target                  : monitor
        onTemperatureReceived   : {
            Monitor.appendData(parseFloat(temperature).toFixed(1));
            tempChart.requestPaint();
        }
    }
}
