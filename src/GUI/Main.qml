import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15
import Qt5Compat.GraphicalEffects
import QtCore

import org.QBluePrint.GUI 1.0
import org.QBluePrint.Boxes 1.0

/*
 * Copyright (c) 2025 Alireza Jafari (https://github.com/arjafari93)
 *
 * This software is provided "as is", without warranty of any kind.
 * You may use, modify, and distribute this software, but you MUST keep
 * this copyright notice and credit the original author.
 *
 * Licensed under the BSD 3-Clause License
 */

ApplicationWindow  {
    id: appMainWindowID
    visible: true
    width:  Math.min( Screen.width * 0.95 , fontMetricsID.height * 120 )
    height: Math.min( Screen.height * 0.9 , fontMetricsID.height * 65  )
    minimumWidth:    Math.min( Screen.height * 0.6 , fontMetricsID.height * 60  )
    minimumHeight:   Math.min( Screen.width * 0.6  , fontMetricsID.height * 35 )
    x:Screen.width * 0.025
    y:Screen.height * 0.025
    title: "QBluePrint V" +  Qt.application.version
    flags: Qt.FramelessWindowHint  | Qt.Window

    Material.theme: BPBoxManager.darkThemeEnabled ?  Material.Dark : Material.Light
    Material.background: BPBoxManager.darkThemeEnabled  ?  "#171C22" : "#D5D5D5"
    Material.accent: BPBoxManager.darkThemeEnabled ?  "#522B76"  : "#3A1255"

    property alias fontMetricsID: fontMetricsID
    FontMetrics{
        id:fontMetricsID
        font.family: Qt.application.font.family
        font.pointSize: cBPStatic.defaultFontPointSize()
    }

    CBPStatic{
        id: cBPStatic
    }

    property alias removeThumbnailCompRectID: boxRemoverAreaID.removeThumbnailCompRectID
    BoxRemoverArea{
        id: boxRemoverAreaID
    }

    Repeater{
        id: bpPageRepeaterID
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: bottomStatusBarInMainPageID.top
        anchors.top: topManuBarInMainPageID.bottom
        model: BPBoxManager.listOfBluePrintPages
        delegate: BluePrintPageDelegate{
            id: bpMainPageDelegateID
            anchors.fill: bpPageRepeaterID
            visible: opacity > 0.05
            opacity: BPBoxManager.activePageIndex == index
            Behavior on opacity {
                NumberAnimation{}
            }
        }
    }

    BottomStatusBar{
        id:bottomStatusBarInMainPageID
        z:999
    }

    TopMenuBar{
        id: topManuBarInMainPageID
        z:999
    }

    LeftDrawerListOfBoxes{
        id:leftDrawerInappMainWindowID
        dragMargin:  1
        z:100
    }

    BluePrintPagesSelector{
        id: pageSelectorID
        z:100
        anchors.left: openCloseDrawerSignID.left
        anchors.right: openCloseDrawerSignID.right
        anchors.top: openCloseDrawerSignID.bottom
        anchors.topMargin: fontMetricsID.height * 0.25
        anchors.bottom: bottomStatusBarInMainPageID.top
    }

    Rectangle {
        id: openCloseDrawerSignID
        color: "#d0000000"
        width: openCLoseDrawerSignTextID.height * 1.25
        height: width
        anchors.top: topManuBarInMainPageID.bottom
        anchors.left: parent.left
        anchors.leftMargin: leftDrawerInappMainWindowID.position * leftDrawerInappMainWindowID.width
        Text {
            id: openCLoseDrawerSignTextID
            text:leftDrawerInappMainWindowID.position == 1 ? "<" :  ">"
            anchors.centerIn: parent
            font.pointSize: fontMetricsID.font.pointSize + 6
            color: "white"
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                cursorShape = Qt.PointingHandCursor;
                openCLoseDrawerSignTextID.font.bold = true
                openCloseDrawerSignID.color = "#d0202020"
            }
            onExited: {
                openCLoseDrawerSignTextID.font.bold = false
                openCloseDrawerSignID.color = "#d0000000"
            }
            onClicked: {
                if(leftDrawerInappMainWindowID.position == 1  )
                    leftDrawerInappMainWindowID.close();
                else
                    leftDrawerInappMainWindowID.open();
            }
        }
    }

    // Function to apply opacity to the color
    function applyOpacityToColor(color, opacity) {
        return Qt.rgba(color.r, color.g, color.b, opacity);
    }

    function defineGUIDeleage ( guiType ){
        switch(guiType){
        case CBPStatic.E_SimpleBluePrint :
            return "qrc:/org/QBluePrint/GUI/QML/BluePrintBoxes/SingleBoxInstance/SingleBoxInstance.qml"
        case CBPStatic.E_OutputSinkWithString :
            return "qrc:/org/QBluePrint/GUI/QML/BluePrintBoxes/SinkOutputString/SinkOutputString.qml"
        case CBPStatic.E_InputSpinBoxWithTimer :
            return "qrc:/org/QBluePrint/GUI/QML/BluePrintBoxes/SpinBoxTimerInputSourceBox/SpinBoxTimerInputSourceBox.qml"
        case CBPStatic.E_BigTextOperator :
            return "qrc:/org/QBluePrint/GUI/QML/BluePrintBoxes/OperatorWithBigText/OperatorWithBigText.qml"
        case CBPStatic.E_BigPictureOperator :
            return "qrc:/org/QBluePrint/GUI/QML/BluePrintBoxes/BigPictureOperator/BigPictureOperator.qml"
        case CBPStatic.E_InputNetworkServer :
            return "qrc:/org/QBluePrint/GUI/QML/BluePrintBoxes/NetworkBoxes/TCPServerInputBox.qml"
        case CBPStatic.E_TypeConvrtrOperator :
            return "qrc:/org/QBluePrint/GUI/QML/BluePrintBoxes/TypeConvertorOperatorBox/TypeConvertorOperatorBox.qml"
        case CBPStatic.E_OutputSinkNetworkClient :
            return "qrc:/org/QBluePrint/GUI/QML/BluePrintBoxes/NetworkBoxes/TCPClientOutputBox.qml"
        case CBPStatic.E_ChartBoxLineSeries:
            return "qrc:/org/QBluePrint/GUI/QML/BluePrintBoxes/ChartBoxes/LineSeriesChartBox.qml"
        case CBPStatic.E_InputButtonSource:
            return "qrc:/org/QBluePrint/GUI/QML/BluePrintBoxes/ButtonSourceBox/ButtonSourceBox.qml"
        case CBPStatic.E_StopWatch:
            return "qrc:/org/QBluePrint/GUI/QML/BluePrintBoxes/StopWatchBox/StopWatchBox.qml"
        case CBPStatic.E_ScriptRunner:
            return "qrc:/org/QBluePrint/GUI/QML/BluePrintBoxes/ScriptRunnerBox/ScriptRunnerBox.qml"
        }
        console.log("GUI Type Doesnt exist ", guiType );
        return "QML/BluePrintBoxes/BigPictureOperator/BigPictureOperator.qml"
    }

    Settings {
        id: settingsID
        property bool terminalGlowEnable: BPBoxManager.terminalGlowEnable
        property bool darkThemeEnabled: BPBoxManager.darkThemeEnabled
    }

    Component.onCompleted: {
        BPBoxManager.terminalGlowEnable = settingsID.terminalGlowEnable
        BPBoxManager.darkThemeEnabled = settingsID.darkThemeEnabled
    }

}
