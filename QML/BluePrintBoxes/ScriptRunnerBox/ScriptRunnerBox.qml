import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import "../SingleTerminalInstance"
import "../SingleBoxInstance"

import org.bluePrintType.BlueScriptBox 1.0

SingleBoxInstance{
    id:codeRunnerBoxID
    property CBlueScriptBox pScriptBox:  modelData


    SequentialAnimation{
        loops: Animation.Infinite
        running:  pScriptBox.jsErrorMessage.length
        NumberAnimation { target: warningImageID; property: "opacity"; from: 1.0; to: 0.1; duration: 1000 }
        NumberAnimation { target: warningImageID; property: "opacity"; from: 0.1; to: 1.0; duration: 1000 }
    }
    Image {
        id: warningImageID
        z:100
        source: "qrc:/Images/warningIcon.png"
        anchors.right: settingBtnImageID.left
        anchors.rightMargin: fontMetricsID.height * 0.5
        height: settingBtnImageID.height
        width: height
        anchors.verticalCenter: settingBtnImageID.verticalCenter
        visible: pScriptBox.jsErrorMessage.length
        ToolTip{
            id: jsErrorTipID
            timeout: 30000
            onVisibleChanged: jsErrorTipID.text = pScriptBox.jsErrorMessage
            visible: jsErrorMouseID.containsMouse
        }
        MouseArea{
            id: jsErrorMouseID
            anchors.fill: parent
            hoverEnabled: true
        }
    }


    ScrollView {
        width: parent.width * 0.7
        height: parent.height * 0.75
        anchors.bottom: parent.bottom
        anchors.bottomMargin: fontMetricsID.height
        anchors.horizontalCenter: parent.horizontalCenter
        clip: true

        TextArea {
            id: codeEditorID
            Material.theme: Material.Light
            width: parent.width
            height: implicitHeight
            wrapMode: TextEdit.WordWrap
            text: pScriptBox.scriptFunctionBody
            font.pointSize: fontMetricsID.font.pointSize
            selectByMouse: true
            background: Rectangle {
                color: "#E0ffffff"
            }

            onTextChanged: pScriptBox.scriptFunctionBody = codeEditorID.text
        }
    }



}















