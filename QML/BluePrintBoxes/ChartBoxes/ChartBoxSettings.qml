import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.0
import QtGraphicalEffects 1.15
import QtQuick.Controls.Material 2.15
import QtQuick.Templates 2.12 as TempQuick

import "../../Style"

import org.bluePrintType.OperationBox 1.0
import org.bluePrintType.LineSeriesChartBox 1.0
import org.bluePrintType.LiveDataXYModel 1.0

Popup {
    id: pupUpCompID
    required property COperationBox pBoxInstance
    property CLiveDataXYModel pChartModel : pBoxInstance.dataListModelInstace

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
        id: setChartMaxLenLableID
        text: "Max Displayed Length: "
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: fontMetricsID.height * 2
    }


    SpinBox{
        id: maxLenSpinBoxID
         Material.theme : Material.Dark
        anchors.left: setChartMaxLenLableID.right
        anchors.leftMargin: setChartMaxLenLableID.anchors.leftMargin
        anchors.verticalCenter: setChartMaxLenLableID.verticalCenter
        width: parent.width * 0.4
        value: pupUpCompID.pChartModel.movingWindowLength
        from: 10
        to: 999999
        editable: true
        onValueChanged: {
            pupUpCompID.pChartModel.movingWindowLength = maxLenSpinBoxID.value ;
        }
    }



}
