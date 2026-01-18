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

Popup {
    id: pupUpCompID
    required property var boxToBeRemoved
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
        id:popUpMsgHeaderLabelID
        anchors.horizontalCenter:  parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: fontMetricsID.height * 2
        font.pointSize: fontMetricsID.font.pointSize + 4
        font.bold: true
        text: "Removeing BluePrint Box"
    }

    Label{
        id:popUpMsgContentLabelID
        anchors.right: parent.right
        anchors.rightMargin: fontMetricsID.height * 4
        anchors.left: parent.left
        anchors.leftMargin: fontMetricsID.height * 4
        anchors.top: popUpMsgHeaderLabelID.bottom
        anchors.topMargin: fontMetricsID.height * 2
        font.pointSize: fontMetricsID.font.pointSize
        wrapMode: Text.WordWrap
        horizontalAlignment: Label.AlignHCenter
        text: "This Action Will Remove Selected Box And Associated Connections\n Do You Confirm?"
    }

    Rectangle{
        id: seperatorRectID
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: popUpMsgHeaderLabelID.anchors.topMargin
        anchors.rightMargin:  popUpMsgHeaderLabelID.anchors.topMargin
        anchors.bottom: okButtonPopUpWrapperRectID.top
        anchors.bottomMargin:  fontMetricsID.height
        height: 1
        color: "#90ffffff"
    }

    Rectangle{
        id:okButtonPopUpWrapperRectID
        anchors.bottom: parent.bottom
        anchors.bottomMargin: fontMetricsID.height * 2
        anchors.right: parent.right
        anchors.rightMargin: fontMetricsID.height * 2
        width: parent.width * 0.25
        height: fontMetricsID.height * 2
        radius: height * 0.25
        border.color: "#C70039"
        border.width: 1
        color: "#B20E0D"
        Component.onCompleted: {
            okButtonPopUpWrapperRectID.forceActiveFocus()
        }

        Keys.onPressed: (event)=> {
            if (event.key == Qt.Key_Enter || event.key == Qt.Key_Return ) {
                event.accepted = true;
                var junk;
                removeBtnMouseAreaID.clicked(junk);
            }else  if (event.key == Qt.Key_Escape ) {
                event.accepted = true;
                var junk;
                cancelButtonMouseID.clicked(junk);
            }
        }
        Text {
            id: okBtnTextID
            text: qsTr("Remove")
            anchors.centerIn: parent
            font.pointSize: fontMetricsID.font.pointSize
            color: "white"
            // font.bold: true
        }

        MouseArea{
            id:removeBtnMouseAreaID
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            onEntered: {
                cursorShape = Qt.PointingHandCursor
                okButtonPopUpWrapperRectID.border.color = "#C70039"
                okButtonPopUpWrapperRectID.color = "#D80032"
            }
            onExited: {
                okButtonPopUpWrapperRectID.border.color = "transparent"
                okButtonPopUpWrapperRectID.color = "#B20E0D"
            }
            onClicked:{
                var currentPageInstance = bpPageRepeaterID.itemAt(BPBoxManager.activePageIndex);
                 currentPageInstance.pBluePrintPage.removeBPBoxFromListModel( boxToBeRemoved );
                pupUpCompID.close();
            }
        }
    }

    Rectangle{
        id:cancelButtonPopUpWrapperRectID
        anchors.bottom: okButtonPopUpWrapperRectID.bottom
        anchors.right: okButtonPopUpWrapperRectID.left
        anchors.rightMargin: fontMetricsID.height
        width: parent.width * 0.25
        height: fontMetricsID.height * 2
        radius: height * 0.25
        color: "#404142"

        Text {
            id: cancelBtnTextID
            text: qsTr("Cancel")
            anchors.centerIn: parent
            font.pointSize: fontMetricsID.font.pointSize
            color: "white"
            // font.bold: true
        }
        MouseArea{
            id:cancelButtonMouseID
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            onEntered: {
                cursorShape = Qt.PointingHandCursor
                cancelButtonPopUpWrapperRectID.color = "#535455"
            }
            onExited: {
                cancelButtonPopUpWrapperRectID.color = "#404142"
            }
            onClicked:{
               pupUpCompID.close();
            }
        }
    }

}
