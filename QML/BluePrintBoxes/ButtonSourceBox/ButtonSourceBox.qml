import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import "../SingleTerminalInstance"
import "../SingleBoxInstance"
import "../../Style"

SingleBoxInstance{
    id:bigPictureOperatorMainBoxID
    radius: 30
    boxHeaderRectID.visible: false

    Rectangle{
        anchors.fill: parent
        z:-1
        color: "#e0000000"
        radius: bigPictureOperatorMainBoxID.radius
    }

    gradient: Gradient {
        orientation: Gradient.Vertical
        GradientStop { position: 0.0; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.40 ) }
        GradientStop { position: 0.5; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.15 ) }
        GradientStop { position: 1.0; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.40 ) }
    }

    ShadowedRectangle {
        id: connectBtnRectID
        anchors.centerIn: parent
        width: fontMetricsID.height * 7
        height: fontMetricsID.height * 3
        mainBackgroundRectID.radius: height * 0.2
        property color btnColorVal: "#5E686D"
        mainBackgroundShaddowID.color: connectionBtnMouseID.containsPress ? "#60ffffff" : "transparent"
        mainBackgroundRectID.border.color: connectionBtnMouseID.containsMouse ? "#80ffffff" : "transparent"
        mainBackgroundRectID.gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0.0; color:   connectBtnRectID.btnColorVal }
            GradientStop { position: 0.5; color: appMainWindowID.applyOpacityToColor(connectBtnRectID.btnColorVal , 0.1) }
            GradientStop { position: 1.0; color: connectBtnRectID.btnColorVal }
        }
        MouseArea{
            id: connectionBtnMouseID
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                pBoxInstance.evaluateOperation();
            }
        }

        Label{
            id: tapsendLableID
            anchors.centerIn: parent
            color: "white"
            text: "Tap To Send"
            font.bold: connectionBtnMouseID.containsMouse
        }
    }


}









