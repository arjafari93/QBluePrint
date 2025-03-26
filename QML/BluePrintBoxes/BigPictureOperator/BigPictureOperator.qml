import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import "../SingleTerminalInstance"
import "../SingleBoxInstance"

SingleBoxInstance{
    id:bigPictureOperatorMainBoxID
    radius: 30
    boxHeaderRectID.visible: false

    Image {
        id: bigPictureOperatorImageID
        source: blueBox_HeaderIcon
        anchors.centerIn: parent
        height: fontMetricsID.height * 5
        width: height
        visible: false
        antialiasing: true
    }


    DropShadow{
        id: bitTextDropShaddowID
        anchors.fill: bigPictureOperatorImageID
        horizontalOffset: 5
        verticalOffset: 5
        radius: 10.0
        samples: 10
        color: "#000000"
        source: bigPictureOperatorImageID
    }

    Rectangle{
        anchors.fill: parent
        z:-1
        color: "#e0000000"
        radius: bigPictureOperatorMainBoxID.radius
    }

    gradient: Gradient {
        orientation: Gradient.Vertical
        GradientStop { position: 0.0; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.4 ) }
        GradientStop { position: 0.5; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.15 ) }
        GradientStop { position: 1.0; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.4 ) }
    }
}









