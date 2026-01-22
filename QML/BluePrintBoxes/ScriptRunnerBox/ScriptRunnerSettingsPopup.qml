import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Dialogs
import Qt.labs.platform 1.0
import Qt5Compat.GraphicalEffects
import QtQuick.Controls.Material 2.15
import QtQuick.Templates 2.12 as TempQuick

import "../../Style"

import org.QBluePrint.Boxes 1.0

Popup {
    id: pupUpCompID
    required property CBlueScriptBox pBoxInstance

    anchors.centerIn: parent
    width: fontMetricsID.height * 35
    height: fontMetricsID.height * 16
    modal: true
    clip: true
    Material.accent:   Material.Purple

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    TempQuick.Overlay.modal:  Rectangle{
        color: "#E0000000"
    }

    enter: Transition {
        NumberAnimation { properties: "scale"; from: 0.5; to: 1; duration: 500 ; easing.type: Easing.OutBack; }
        NumberAnimation { properties: "opacity"; from: 0.1; to: 1; duration: 500 ;  }
    }

    background: Item{
        ShadowedRectangle{
            anchors.fill: parent
            anchors.margins: fontMetricsID.height * 2
        }
    }

    Component.onCompleted: {
        leftDrawerInappMainWindowID.close();
        pupUpCompID.open();
    }

    onClosed: {
        pupUpCompID.destroy();
    }

    Label{
        id: numInputsLabelID
        text: "Num. Inputs: "
        anchors.bottom:  parent.verticalCenter
        anchors.bottomMargin: fontMetricsID.height * 1.5
        anchors.left: parent.left
        anchors.leftMargin: fontMetricsID.height * 2
    }

    SpinBox{
        id: numInputsSpinID
        Material.theme : Material.Dark
        anchors.left: numInputsLabelID.right
        anchors.leftMargin: numInputsLabelID.anchors.leftMargin
        anchors.verticalCenter: numInputsLabelID.verticalCenter
        width: parent.width * 0.4
        value: pupUpCompID.pBoxInstance.numInputs
        from: 1
        to: 20
        editable: true
        onValueChanged: {
            pupUpCompID.pBoxInstance.numInputs = numInputsSpinID.value ;
        }
    }

    Label{
        id: numOutputsLabelID
        text: "Num. Outputs: "
        anchors.top: parent.verticalCenter
        anchors.topMargin: numInputsLabelID.anchors.bottomMargin
        anchors.left: numInputsLabelID.left
    }

    SpinBox{
        id: numOutputsSpinID
        Material.theme : Material.Dark
        anchors.left: numInputsSpinID.left
        anchors.verticalCenter: numOutputsLabelID.verticalCenter
        width: parent.width * 0.4
        value: pupUpCompID.pBoxInstance.numOutputs
        from: 1
        to: 20
        editable: true
        onValueChanged: {
            pupUpCompID.pBoxInstance.numOutputs = numOutputsSpinID.value ;
        }
    }

}
