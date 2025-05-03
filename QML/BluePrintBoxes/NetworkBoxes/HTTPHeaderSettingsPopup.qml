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
import org.bluePrintType.HTTPRawHeaderFormat 1.0

Popup {
    id: pupUpCompID
    required property COperationBox pBoxInstance

    anchors.centerIn: parent
    width: fontMetricsID.height * 45
    height: fontMetricsID.height * 30
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
        id: keyLabelID
        text: "Raw Header Data"
        anchors.top:  parent.top
        anchors.topMargin:  fontMetricsID.height * 2.5
        anchors.horizontalCenter:  parent.horizontalCenter
        font.pointSize: fontMetricsID.font.pointSize + 2
    }




    ListView{
        id:listOfHeaderkeyValuesID
        anchors.top:keyLabelID.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: addNewRowBtnID.top
        anchors.margins: fontMetricsID.height * 2
        anchors.topMargin: fontMetricsID.height * 1.5
        clip: true
        model: modelData.listOfRawHeaders
        spacing: fontMetricsID.height * 0.25
        ScrollBar.vertical: ScrollBar {
            id:scrollBarOfListViewID
            anchors.right: parent.right
            policy: ScrollBar.AsNeeded
            width: fontMetricsID.height
        }
        delegate: Item{
            id: deleageRectID
            property CHTTPRawHeaderFormat pHeaderInfo: modelData
            width: listOfHeaderkeyValuesID.width * 0.9
            anchors.horizontalCenter: parent.horizontalCenter
            height: fontMetricsID.height * 3
            ToolTip{
                id: textFieldHoverTipID
                text: rawHeaderNameTextID.text
                visible: rawHeaderNameTextID.hovered && rawHeaderNameTextID.text.length > 10
                timeout: 30000
            }
            TextField {
                id: rawHeaderNameTextID
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                width: parent.width * 0.4
                placeholderText: "Header Name"
                selectByMouse: true
                text: deleageRectID.pHeaderInfo.headerName
                onTextChanged:  {
                    deleageRectID.pHeaderInfo.headerName = text
                }
            }
            ToolTip{
                id: textFieldHoverTipID2
                text: rawHeaderValueTextID.text
                visible: rawHeaderValueTextID.hovered && rawHeaderValueTextID.text.length > 10
                timeout: 30000
            }
            TextField {
                id: rawHeaderValueTextID
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: rawHeaderNameTextID.right
                anchors.leftMargin: fontMetricsID.height
                width: rawHeaderNameTextID.width
                placeholderText: "Header Value"
                selectByMouse: true
                text: deleageRectID.pHeaderInfo.headerValue
                onTextChanged:  {
                    deleageRectID.pHeaderInfo.headerValue = text
                }
            }
            Rectangle{
                id: removeRectID
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                height: rawHeaderValueTextID.height * 0.5
                width: height
                color: removeMosueID.containsMouse ? "#E02020"  : "#902020"
                Label{
                    text: "X"
                    font.pointSize: fontMetricsID.font.pointSize + 4
                    color: "white"
                    anchors.centerIn: parent
                }
                MouseArea{
                    id: removeMosueID
                    z:100
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        pupUpCompID.pBoxInstance.removePairFromRawHeaderList(index);
                    }
                }
            }
        }
        Rectangle{
            anchors.fill: parent
            color: BPBoxManager.darkThemeEnabled ?  "#20000000" : "#20ffffff"
            border.color: BPBoxManager.darkThemeEnabled ? "#10ffffff" : "#20000000"
        }
    }


    Rectangle{
        id: addNewRowBtnID
        z:100
        anchors.bottom:  parent.bottom
        anchors.bottomMargin:  fontMetricsID.height * 2
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.5
        height: fontMetricsID.height * 3
        radius: height * 0.2
        property color btnColorVal: btnMouseID.containsPress ?  "#309030" :  "#307030"
        border.color: btnMouseID.containsMouse ? "#80ffffff" : "transparent"
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0.0; color:   addNewRowBtnID.btnColorVal }
            GradientStop { position: 0.5; color: appMainWindowID.applyOpacityToColor(addNewRowBtnID.btnColorVal , 0.4) }
            GradientStop { position: 1.0; color: addNewRowBtnID.btnColorVal }
        }
        MouseArea{
            id: btnMouseID
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                modelData.addNewPairToRawHeaderList();
            }
        }

        Label{
            anchors.centerIn: parent
            color: "white"
            text: "Add New Pair"
        }
        Rectangle{
            anchors.fill: parent
            color: "black"
            z:-1
            radius: addNewRowBtnID.radius
        }
    }



}
