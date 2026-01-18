import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import "../Style"

ShadowedRectangle {
    id: pageSelectorItemID
    mainBackgroundRectID.radius: 0
    Rectangle{
        id: createNewPageRectID
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: width
        color:  addMouseID.containsMouse ? Qt.lighter(Material.accent) : Material.accent
        border.color:   addMouseID.containsMouse ? "#20ffffff" : "transparent"
        Label{
            text: "+"
            font.pointSize: fontMetricsID.font.pointSize + 4
            font.bold: addMouseID.containsMouse
            color: "white"
            anchors.centerIn: parent
            opacity: addMouseID.containsMouse ? 1.0 : 0.6
        }
        MouseArea{
            id: addMouseID
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                BPBoxManager.addNewBluePrintPage();
            }
        }
    }

    ListView{
        id: listOfPagesListviewID
        anchors.fill: parent
        clip: true
        anchors.topMargin: createNewPageRectID.height + fontMetricsID.height * 0.5
        model: BPBoxManager.listOfBluePrintPages
        delegate: PageSelectorDelegate{
            id: selectorDlgtID
            anchors.horizontalCenter: parent.horizontalCenter
            width: listOfPagesListviewID.width - 2
        }
    }

}
