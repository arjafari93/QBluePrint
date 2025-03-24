import QtQuick 2.15
import QtQuick.Controls 2.15
import "../SingleTerminalInstance"
import "../SingleBoxInstance"

SingleBoxInstance{
    id:timerSpinBoxMainBoxID

    Label{
        id: stringLabelSinkID
        text: "Output:  " + stringToBeDisplayed
        anchors.horizontalCenter: parent.horizontalCenter
        y: (timerSpinBoxMainBoxID.height - boxHeaderRectID.height) * 0.5
        color: "white"
        font.pointSize: fontMetricsID.font.pointSize
    }



}















