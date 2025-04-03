import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import "../SingleTerminalInstance"
import "../SingleBoxInstance"
import "../../Style"
SingleBoxInstance{
    id:stopWatchManBoxID
    radius: 30
    boxHeaderRectID.visible: false
    property var elapsedTimeObj: formatTime(modelData.elapsedTime)

    function formatTime(usVal) {
        let totalSeconds = Math.floor(usVal / 1000000);
        let minutes = Math.floor(totalSeconds / 60);
        let seconds = totalSeconds % 60;
        let milliseconds = Math.floor((usVal % 1000000) / 1000);
        let microseconds = usVal % 1000; // Remaining microseconds

        return {
            minutes: minutes.toString().padStart(2, '0'),
            seconds: seconds.toString().padStart(2, '0'),
            milliseconds: milliseconds.toString().padStart(3, '0'),
            microseconds: microseconds.toString().padStart(3, '0')
        };
    }

    Label{
        id: elapsedMinutesID
        anchors.right: seperatorLableID.left
        anchors.rightMargin: fontMetricsID.height * 0.25
        anchors.verticalCenter:  elapsedSecondsID.verticalCenter
        color: "white"
        text: stopWatchManBoxID.elapsedTimeObj.minutes
        font.pointSize:  fontMetricsID.font.pointSize + 8
    }
    Label{
        id: seperatorLableID
        anchors.right: elapsedSecondsID.left
        anchors.rightMargin: fontMetricsID.height * 0.25
        anchors.verticalCenter:  elapsedSecondsID.verticalCenter
        color: "white"
        text: ":"
        font.pointSize:  elapsedMinutesID.font.pointSize
    }
    Label{
        id: elapsedSecondsID
        anchors.centerIn: parent
        color: "white"
        text:  stopWatchManBoxID.elapsedTimeObj.seconds
        font.pointSize:  elapsedMinutesID.font.pointSize
    }
    Label{
        id: elapsedMSecondsID
        anchors.left: elapsedSecondsID.right
        anchors.leftMargin: fontMetricsID.height * 0.25
        anchors.bottom:  elapsedSecondsID.bottom
        color: "white"
        text:  stopWatchManBoxID.elapsedTimeObj.milliseconds
        font.pointSize:  elapsedMinutesID.font.pointSize - 4
    }
    Label{
        id: elapsedUSecondsID
        anchors.left: elapsedMSecondsID.right
        anchors.leftMargin: fontMetricsID.height * 0.25
        anchors.bottom:  elapsedSecondsID.bottom
        color: "white"
        text:  stopWatchManBoxID.elapsedTimeObj.microseconds
        font.pointSize:  elapsedMinutesID.font.pointSize - 7
    }
    Rectangle{
        anchors.fill: parent
        z:-1
        color: "#e0000000"
        radius: stopWatchManBoxID.radius
    }

    gradient: Gradient {
        orientation: Gradient.Vertical
        GradientStop { position: 0.0; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.4 ) }
        GradientStop { position: 0.5; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.15 ) }
        GradientStop { position: 1.0; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.4 ) }
    }

}









