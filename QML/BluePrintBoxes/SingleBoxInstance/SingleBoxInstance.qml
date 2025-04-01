import QtQuick 2.15
import QtQuick.Controls 2.15
import "../SingleTerminalInstance"

import org.bluePrintType.OperationBox 1.0

Rectangle{
    id:boxMainRectID
    property COperationBox pBoxInstance: modelData
    property alias settingBtnImageID: settingBtnImageID
    color:  "#b00F110F"
    x: boxMainRectID.pBoxInstance.blueBox_xPos
    y: boxMainRectID.pBoxInstance.blueBox_yPos
    width: boxMainRectID.pBoxInstance.blueBox_width
    height: boxMainRectID.pBoxInstance.blueBox_height
    radius: 10
    clip: true

    border.color: boxMainRectID.activeFocus ?  boxMainRectID.pBoxInstance.blueBox_HeadColor : applyOpacityToColor(boxMainRectID.pBoxInstance.blueBox_HeadColor , 0.5)
    border.width: boxMainRectID.activeFocus ? 2 : 1
    onXChanged: {
        boxMainRectID.pBoxInstance.blueBox_xPos = x;
    }
    onYChanged: {
        boxMainRectID.pBoxInstance.blueBox_yPos = y;
    }

    Keys.onPressed: {
        if (event.key == Qt.Key_Delete) {
            event.accepted = true;
            var removeBoxComp = Qt.createComponent("qrc:/QML/BluePrintBoxes/SingleBoxInstance/RemoveBoxConfirm.qml");
            var removeObj = removeBoxComp.createObject(appMainWindowID , {"boxToBeRemoved":modelData });
        }
    }

    property alias boxHeaderRectID: boxHeaderRectID
    Rectangle{
        id:boxHeaderRectID
        z:100
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: fontMetricsID.height * 2 // dont change this!!
        radius: boxMainRectID.radius
        border.color: boxMainRectID.pBoxInstance.blueBox_HeadColor
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 0.0; color:   boxMainRectID.pBoxInstance.blueBox_HeadColor }
            GradientStop { position: 1.1; color: "transparent" }
        }
        Rectangle{
            opacity: 0.75
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            height: nameOfBoxLabelID.height * 1.5
            radius: 5
            gradient: Gradient {
                orientation: Gradient.Vertical
                GradientStop { position: 0.0; color:   boxMainRectID.pBoxInstance.blueBox_HeadColor }
                GradientStop { position: 0.5; color:  "#40000000" }
                GradientStop { position: 1.0; color: boxMainRectID.pBoxInstance.blueBox_HeadColor }
            }
        }
        Image {
            id: boxIconImageID
            source: boxMainRectID.pBoxInstance.blueBox_HeaderIcon
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: height * 0.5
            height: parent.height * 0.75
            width: height

        }
        Label{
            id:nameOfBoxLabelID
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: boxIconImageID.right
            anchors.leftMargin: height
            text: boxMainRectID.pBoxInstance.blueBox_name
            font.pointSize: fontMetricsID.font.pointSize
            color: "white"
        }
    }


    ToolTip{
        id:boxToolTipID
        text: boxMainRectID.pBoxInstance.blueBox_name
        timeout: 3000

    }


    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        drag.target: boxMainRectID
        propagateComposedEvents: true
        onPressed: {
            // break the binding
            boxMainRectID.forceActiveFocus();
            boxMainRectID.x = boxMainRectID.pBoxInstance.blueBox_xPos;
            boxMainRectID.y = boxMainRectID.pBoxInstance.blueBox_yPos;
        }
        onReleased: {
            // rebind
            boxMainRectID.x = Qt.binding(function(){return boxMainRectID.pBoxInstance.blueBox_xPos})
            boxMainRectID.y = Qt.binding(function(){return boxMainRectID.pBoxInstance.blueBox_yPos})
        }
        onEntered: {
            boxToolTipID.visible = true
        }
        onExited: {
            boxToolTipID.visible = false
        }
    }




    ListView{
        id: listViewOfInputTerminalsID
        z:10
        interactive: false // if enable and user scrollDown, we stuck in listview and cant draw flow line
        anchors.left: parent.left
        anchors.top: boxHeaderRectID.bottom
        anchors.topMargin: 0 // dont change this
        anchors.bottom: parent.bottom
        width: fontMetricsID.height * 5
        model: boxMainRectID.pBoxInstance.listOfInputTerminals
        clip: false
        delegate: SingleTerminalInstance {
            id: inputKnobsOfTheBoxDelegateID
            isInputTerminal: true
            width: height
            clip: false
        }
    }






    ListView{
        id: listViewOfOutputTerminalsID
        z:10
        interactive: false // if enable and user scrollDown, we stuck in listview and cant draw flow line
        anchors.right: parent.right
        anchors.top: boxHeaderRectID.bottom
        anchors.bottom: parent.bottom
        width: fontMetricsID.height * 5
        model: boxMainRectID.pBoxInstance.listOfOutputTerminals
        clip: false
        delegate: SingleTerminalInstance {
            id: outputKnobsOfTheBoxDelegateID
            isInputTerminal: false
            height: boxHeaderRectID.height
            width: height
            clip: false
        }
    }

    SequentialAnimation{
        loops: Animation.Infinite
        running:  pBoxInstance.blueBox_warningMsg.length
        NumberAnimation { target: warningImageID; property: "opacity"; from: 1.0; to: 0.1; duration: 1000 }
        NumberAnimation { target: warningImageID; property: "opacity"; from: 0.1; to: 1.0; duration: 1000 }
    }
    Image {
        id: warningImageID
        z:100
        source: "qrc:/Images/warningIcon.png"
        anchors.right: settingBtnImageID.left
        anchors.rightMargin: fontMetricsID.height * 0.5
        height: settingBtnImageID.height
        width: height
        anchors.verticalCenter: settingBtnImageID.verticalCenter
        visible: pBoxInstance.blueBox_warningMsg.length
        ToolTip{
            id: jsErrorTipID
            timeout: 30000
            onVisibleChanged: jsErrorTipID.text = pBoxInstance.blueBox_warningMsg
            visible: jsErrorMouseID.containsMouse
        }
        MouseArea{
            id: jsErrorMouseID
            anchors.fill: parent
            hoverEnabled: true
        }
    }

    Image {
        id: settingBtnImageID
        source: "qrc:/Images/settingsIcon.png"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: fontMetricsID.height * 0.25
        anchors.rightMargin: fontMetricsID.height
        height: fontMetricsID.height * 1.5
        width: height
        visible: boxMainRectID.pBoxInstance.blueBox_settingQMLPath != ""
        opacity: settingsImageMouseID.containsMouse ? 1.0 : 0.75
        z:101
        MouseArea {
            id: settingsImageMouseID
            anchors.fill: parent
            hoverEnabled: true
            cursorShape : Qt.PointingHandCursor
            onClicked: {
                var settingsComp = Qt.createComponent(boxMainRectID.pBoxInstance.blueBox_settingQMLPath);
                var settingsObj = settingsComp.createObject(appMainWindowID , {"pBoxInstance" : boxMainRectID.pBoxInstance} );
            }
        }
    }


}
