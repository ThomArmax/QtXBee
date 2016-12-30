import QtQuick 2.4
import QtQuick.Window 2.2

import "qchartjs"
import "qchartjs/QChart.js" as Charts
import "monitor.js" as Monitor

Window {
    visible : true
    width   : 800
    height  : 480

    Rectangle {
        anchors.fill: parent
        color       : "darkgrey"
    }

    Column {
        anchors.fill    : parent
        spacing         : 20
        anchors.margins : 20
        Text {
            id                  : title
            width               : parent.width
            text                : "Current temperature : " + parseFloat(monitor.currentTemperature).toFixed(1) + "°C"
            color               : "#336699"
            font.pointSize      : 25
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
            chartOptions            : chartOpt
        }
    }

    property var chartOpt: {
        'scaleOverride' : true,
        'scaleSteps' : 1,
        'scaleStepWidth' : 2 * (parseInt(monitor.maxTemperature) - parseInt(monitor.minTemperature) ) + 5,
        'scaleStartValue' : parseInt(monitor.minTemperature) - 5
    }

    Connections {
        target                  : monitor
        onTemperatureReceived   : {
            Monitor.appendData(parseFloat(temperature).toFixed(1));
            tempChart.requestPaint();
        }
        onMinTemperatureChanged : {
            tempChart.chartOptions = chartOpt;
            tempChart.chart = null;
            tempChart.update();
        }
        onMaxTemperatureChanged: {
            tempChart.chartOptions = chartOpt;
            tempChart.chart = null;
            tempChart.update();
        }
    }
}
