import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import "../SingleTerminalInstance"
import "../SingleBoxInstance"

SingleBoxInstance{
    id:opBigTextMainBoxID
    radius: 30
    boxHeaderRectID.visible: false
    Label{
        id: stringLabelSinkID
        text: operatorSymbol
        anchors.centerIn: parent
        font.pointSize: 35
        font.bold: true
        visible: false
        color: "white"
    }
    DropShadow{
        id: bitTextDropShaddowID
        anchors.fill: stringLabelSinkID
        horizontalOffset: 5
        verticalOffset: 5
        radius: 10.0
        samples: 10
        color: "#f0000000"
        source: stringLabelSinkID
    }

    Rectangle{
        anchors.fill: parent
        z:-1
        color: "#e0000000"
        radius: opBigTextMainBoxID.radius
    }

    gradient: Gradient {
        orientation: Gradient.Vertical
        GradientStop { position: 0.0; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.3 ) }
        GradientStop { position: 0.5; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.1 ) }
        GradientStop { position: 1.0; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.3 ) }
    }
}















