import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.5 as QCtrl15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.15
import "QML/BluePrintPagesSelector"
import "QML/LeftDrawerListOfBoxes"
import "QML/BottomStatusBar"
import "QML/TopMenuBar"
import "QML"

import org.bluePrintType.BPStatic  1.0

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
            return "qrc:/QML/BluePrintBoxes/SingleBoxInstance/SingleBoxInstance.qml"
        case CBPStatic.E_OutputSinkWithString :
            return "qrc:/QML/BluePrintBoxes/SinkOutputString/SinkOutputString.qml"
        case CBPStatic.E_InputSpinBoxWithTimer :
            return "qrc:/QML/BluePrintBoxes/SpinBoxTimerInputSourceBox/SpinBoxTimerInputSourceBox.qml"
        case CBPStatic.E_BigTextOperator :
            return "qrc:/QML/BluePrintBoxes/OperatorWithBigText/OperatorWithBigText.qml"
        case CBPStatic.E_BigPictureOperator :
            return "qrc:/QML/BluePrintBoxes/BigPictureOperator/BigPictureOperator.qml"
        case CBPStatic.E_InputNetworkServer :
            return "qrc:/QML/BluePrintBoxes/NetworkBoxes/TCPServerInputBox.qml"
        case CBPStatic.E_TypeConvrtrOperator :
            return "qrc:/QML/BluePrintBoxes/TypeConvertorOperatorBox/TypeConvertorOperatorBox.qml"
        case CBPStatic.E_OutputSinkNetworkClient :
            return "qrc:/QML/BluePrintBoxes/NetworkBoxes/TCPClientOutputBox.qml"
        case CBPStatic.E_ChartBoxLineSeries:
            return "qrc:/QML/BluePrintBoxes/ChartBoxes/LineSeriesChartBox.qml"
        case CBPStatic.E_InputButtonSource:
            return "qrc:/QML/BluePrintBoxes/ButtonSourceBox/ButtonSourceBox.qml"
        case CBPStatic.E_StopWatch:
            return "qrc:/QML/BluePrintBoxes/StopWatchBox/StopWatchBox.qml"
        case CBPStatic.E_ScriptRunner:
            return "qrc:/QML/BluePrintBoxes/ScriptRunnerBox/ScriptRunnerBox.qml"
        }
        console.log("GUI Type Doesnt exist " ,guiType );
        return "qrc:/QML/BluePrintBoxes/BigPictureOperator/BigPictureOperator.qml"
    }


}
