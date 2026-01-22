import QtQuick 2.15
import Qt.labs.platform 1.1
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15
import QtQuick.Dialogs

import Qt5Compat.GraphicalEffects
import QtQuick.Templates 2.12 as TempQuick

import "../Style"
import org.QBluePrint.Boxes 1.0

Popup {
    id: pupUpCompID
    required property int indexOfPage
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
        text: "Save Current BluePrint Before Exit"
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
        text: "You Are About To Leave Current BluePrint, Do You Want To Save Current BluePrint? "
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
        border.width: 1
        color: "#404142"
        Component.onCompleted: {
            okButtonPopUpWrapperRectID.forceActiveFocus()
        }

        Keys.onPressed: (event)=> {
            if (event.key == Qt.Key_Enter || event.key == Qt.Key_Return ) {
                event.accepted = true;
                var junk;
                okeBtnMouseAreaID.clicked(junk);
            }else  if (event.key == Qt.Key_Escape ) {
                event.accepted = true;
                var junk;
                cancelButtonMouseID.clicked(junk);
            }
        }
        Text {
            id: okBtnTextID
            text: qsTr("Save")
            anchors.centerIn: parent
            font.pointSize: fontMetricsID.font.pointSize
            color: "white"
            // font.bold: true
        }

        MouseArea{
            id:okeBtnMouseAreaID
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            onEntered: {
                cursorShape = Qt.PointingHandCursor
                okButtonPopUpWrapperRectID.color = "#535455"
            }
            onExited: {
                okButtonPopUpWrapperRectID.color = "#404142"
            }
            onClicked:{
                var junk ;
                var currentPageInstance = bpPageRepeaterID.itemAt(BPBoxManager.activePageIndex);
                if(currentPageInstance.pBluePrintPage.currentBluePrintFilePath == ""){
                    saveAsDialog.open();
                    return ;
                }
                if( currentPageInstance.pBluePrintPage.saveBluePrintInfo(currentPageInstance.pBluePrintPage.currentBluePrintFilePath) )
                    BPBoxManager.showStatusBarMessage("BluePrint Updated Successfully" , 5000)
                else
                    BPBoxManager.showStatusBarMessage("Failed To Update Saved File" , 5000)
                Qt.callLater(function() { // can cause crashes if called sync
                    BPBoxManager.removeBluePrintPage(pupUpCompID.indexOfPage);
                });
                pupUpCompID.close();
            }
        }
    }
    FileDialog {
        id: saveAsDialog
        title: "Save As"
        selectExisting: false  // Ensures a new file is selected
        nameFilters: ["QBluePrint Files (*.qbp)"]
        onAccepted: {
            var currentPageInstance = bpPageRepeaterID.itemAt(BPBoxManager.activePageIndex);
            if( currentPageInstance.pBluePrintPage.saveBluePrintInfo(fileUrl.toString().replace("file:///", "")) )
                BPBoxManager.showStatusBarMessage("BluePrint Info Saved to " + currentPageInstance.pBluePrintPage.currentBluePrintFilePath , 5000)
            else
                BPBoxManager.showStatusBarMessage("Failed To Save File" , 5000);
            Qt.callLater(function() { // can cause crashes if called sync
                BPBoxManager.removeBluePrintPage(pupUpCompID.indexOfPage);
            });
            pupUpCompID.close();
        }
    }

    Rectangle{
        id: stayButtonPopUpWrapperRectID
        anchors.bottom: okButtonPopUpWrapperRectID.bottom
        anchors.right: okButtonPopUpWrapperRectID.left
        anchors.rightMargin: fontMetricsID.height
        width: parent.width * 0.25
        height: fontMetricsID.height * 2
        radius: height * 0.25
        color: "#404142"

        Text {
            id: stayBtnTextID
            text: qsTr("Stay")
            anchors.centerIn: parent
            font.pointSize: fontMetricsID.font.pointSize
            color: "white"
            // font.bold: true
        }
        MouseArea{
            id: stayButtonMouseID
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            onEntered: {
                cursorShape = Qt.PointingHandCursor
                stayButtonPopUpWrapperRectID.color = "#535455"
            }
            onExited: {
                stayButtonPopUpWrapperRectID.color = "#404142"
            }
            onClicked:{
                pupUpCompID.close();
            }
        }
    }

    Rectangle{
        id:cancelButtonPopUpWrapperRectID
        anchors.bottom: okButtonPopUpWrapperRectID.bottom
        anchors.right: stayButtonPopUpWrapperRectID.left
        anchors.rightMargin: okButtonPopUpWrapperRectID.anchors.rightMargin

        width: parent.width * 0.25
        height: fontMetricsID.height * 2
        radius: height * 0.25
        color: "#B20E0D"

        Text {
            id: cancelBtnTextID
            text: qsTr("Close")
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
                cancelButtonPopUpWrapperRectID.color = "#D80032"
            }
            onExited: {
                cancelButtonPopUpWrapperRectID.color = "#B20E0D"
            }
            onClicked:{
                var currentPageInstance = bpPageRepeaterID.itemAt(BPBoxManager.activePageIndex);
                currentPageInstance.pBluePrintPage.clearCurrentBluePrintSession();
                Qt.callLater(function() { // can cause crashes if called sync
                    BPBoxManager.removeBluePrintPage(pupUpCompID.indexOfPage);
                });
                pupUpCompID.close();
            }
        }
    }

}
