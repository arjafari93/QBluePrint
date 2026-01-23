import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects

import org.QBluePrint.GUI 1.0

SingleBoxInstance{
    id:bigPictureOperatorMainBoxID
    radius: 30
    boxHeaderRectID.visible: false

    Image {
        id: bigPictureOperatorImageID
        source: blueBox_HeaderIcon
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: fontMetricsID.height
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
        color: "#f0000000"
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
        GradientStop { position: 0.0; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.40 ) }
        GradientStop { position: 0.5; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.15 ) }
        GradientStop { position: 1.0; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.40 ) }
    }

    ComboBox{
        id: targetTypeComboID
        model: cBPStatic.getListOfSupportedTypes()
        currentIndex: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: bigPictureOperatorImageID.bottom
        anchors.topMargin: fontMetricsID.height * 0.5
        onCurrentIndexChanged: selectedOutputType = cBPStatic.getListOfSupportedTypes()[currentIndex]
        Component.onCompleted: {
            for(var iter=0 ; iter < cBPStatic.getListOfSupportedTypes().length ; iter++){
                if(cBPStatic.getListOfSupportedTypes()[iter] == selectedOutputType ){
                    targetTypeComboID.currentIndex = iter ;
                    return ;
                }
            }
        }
    }

}









