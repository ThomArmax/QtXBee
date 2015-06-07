var MonitorData = {
    labels: [/*"Temperature (°C)"*/],
    datasets: [
        {
            fillColor: "rgba(220,220,220,0.5)",
            strokeColor: "rgba(220,220,220,1)",
            pointColor: "rgba(220,220,220,1)",
            pointStrokeColor: "#ffffff",
            data: []
        }
    ]
}

var MaxElements = 20;

function appendData(data) {
    if(MonitorData.datasets[0].data.length >= MaxElements) {
        MonitorData.datasets[0].data.splice(0, 1);
        MonitorData.labels.splice(0, 1);
    }
    MonitorData.datasets[0].data.push(data);
    MonitorData.labels.push(Qt.formatDateTime(new Date(), "hh:mm:ss"));
}
