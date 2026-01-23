import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15

Label {
    id: statusBarLabelID
    property alias messageTimeOut: destructorTimerID.interval
    Timer{
        id:destructorTimerID
        interval: 2500
        repeat: false
        running: true
        onTriggered: {
            statusBarLabelID.destroy()
        }
    }
    color: "white"
    text: "Invalid Text"
    anchors.verticalCenter: parent.verticalCenter
    font.pointSize: fontMetricsID.font.pointSize
}
