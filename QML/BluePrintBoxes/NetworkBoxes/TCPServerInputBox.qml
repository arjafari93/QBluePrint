import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import "../SingleTerminalInstance"
import "../SingleBoxInstance"

SingleBoxInstance{
    id:timerSpinBoxMainBoxID

    Item{
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: fontMetricsID.height * 5
        height: fontMetricsID.height * 3
        Label{
            id: valueToBeSentIntLabelID
            text: "Port:"
            font.pointSize: fontMetricsID.font.pointSize
            color: "white"
            anchors.left: parent.left
            anchors.leftMargin:  fontMetricsID.height
        }

        SpinBox{
            id: valueToBeSendSpinBox
             Material.theme : Material.Dark
            anchors.left: valueToBeSentIntLabelID.right
            anchors.leftMargin: valueToBeSentIntLabelID.anchors.leftMargin
            anchors.verticalCenter: valueToBeSentIntLabelID.verticalCenter
            width: parent.width * 0.65
            value: serverPortNum
            from: 1
            to: 65535
            editable: true
            onValueChanged: {
                serverPortNum = valueToBeSendSpinBox.value ;
            }
        }
    }

}















