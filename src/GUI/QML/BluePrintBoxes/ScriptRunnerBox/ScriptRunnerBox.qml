import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import org.QBluePrint.GUI 1.0

import org.QBluePrint.Boxes 1.0

SingleBoxInstance{
    id:codeRunnerBoxID
    property CBlueScriptBox pScriptBox:  modelData

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















