import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.5 as QCtrl15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.15
import "QML/BluePrintBoxes"
import "QML/BluePrindLineFlow"
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

    property alias bluePrintBoxesInMainPageID : bluePrintBoxesInMainPageID
    property real scaleFactorOfApp: BPBoxManager.applicationScaleFactor
    Behavior on scaleFactorOfApp {
        NumberAnimation{duration: 100 }
    }


    CBPStatic{
        id: cBPStatic
    }


    property alias removeThumbnailCompRectID: boxRemoverAreaID.removeThumbnailCompRectID
    BoxRemoverArea{
        id: boxRemoverAreaID
    }


    QCtrl15.ScrollView{
        id:scrollViewInappMainWindowID
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: bottomStatusBarInMainPageID.top
        anchors.top: topManuBarInMainPageID.bottom
        clip: true
        flickableItem.boundsBehavior: Flickable.StopAtBounds
        flickableItem.interactive: false
        ScrollBar {
            id: verticalScrollBar
            orientation: Qt.Vertical
            anchors.right: parent.right
            visible: false
        }
        Item{
            id:mainWindowWrapperItemID
            x:0
            y:0
            width:    Math.max( scrollViewInappMainWindowID.width , BPBoxManager.maxBPBoxXpos ) * appMainWindowID.scaleFactorOfApp - verticalScrollBar.width- 5
            height:   Math.max( scrollViewInappMainWindowID.height , BPBoxManager.maxBPBoxYpos )  * appMainWindowID.scaleFactorOfApp - verticalScrollBar.width - 5

            transform: Scale {
                origin.x: 0;
                origin.y: 0;
                xScale:  appMainWindowID.scaleFactorOfApp ;
                yScale: appMainWindowID.scaleFactorOfApp ;
            }

            LineFlowFullScreenRepeater{
                id: bluePrintLineFlowsInMainPageID
                z: 5
            }


            BoxesFullScreenRepeater{
                id: bluePrintBoxesInMainPageID
                z:4
            }
            MouseArea{
                z:-1
                anchors.fill: parent
                onClicked: if(leftDrawerInappMainWindowID.position > 0.9)  leftDrawerInappMainWindowID.close() ; // close drawer on click in empty erea
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



    // MouseArea to handle mouse wheel events
    MouseArea {
        anchors.fill: scrollViewInappMainWindowID
        hoverEnabled: false
        propagateComposedEvents: true
        // Set acceptedButtons to Qt.NoButton to allow click events to propagate
        acceptedButtons: Qt.NoButton

        onClicked: {
            mouse.accepted = false
        }

        // Handle wheel events
        onWheel: {
            // Check if the Control key is pressed
            if (wheel.modifiers & Qt.ControlModifier) {
                // Control button + wheel event handling
                if (wheel.angleDelta.y > 0 && BPBoxManager.applicationScaleFactor < 2.0 ) {
                    if(BPBoxManager.applicationScaleFactor * 1.1 > 2.0 ) // make sure we dont zoom
                        BPBoxManager.applicationScaleFactor = 2.0 ;
                    else
                        BPBoxManager.applicationScaleFactor *= 1.1
                    // Perform actions for scrolling up with Control pressed
                } else if (wheel.angleDelta.y < 0 && BPBoxManager.applicationScaleFactor > 0.2) {
                    BPBoxManager.applicationScaleFactor *= 0.9
                    // Perform actions for scrolling down with Control pressed
                }
                return;
            }

            // If shift key is pressed, scroll horizontally
            if (wheel.modifiers & Qt.ShiftModifier) {
                scrollViewInappMainWindowID.flickableItem.contentX -= wheel.angleDelta.y / 120 * 20;
//                if(scrollViewInappMainWindowID.flickableItem.contentX < 0 )
//                    scrollViewInappMainWindowID.flickableItem.contentX = 0 ;
//                if(scrollViewInappMainWindowID.flickableItem.contentX > mainWindowWrapperItemID.width - appMainWindowID.width )
//                    scrollViewInappMainWindowID.flickableItem.contentX = mainWindowWrapperItemID.width - appMainWindowID.width ;
            }
            // Otherwise, scroll vertically
            else {
                scrollViewInappMainWindowID.flickableItem.contentY -= wheel.angleDelta.y / 120 * 20;
//                if(scrollViewInappMainWindowID.flickableItem.contentY < 0 )
//                    scrollViewInappMainWindowID.flickableItem.contentY = 0 ;
//                if(scrollViewInappMainWindowID.flickableItem.contentY > mainWindowWrapperItemID.height - appMainWindowID.height )
//                    scrollViewInappMainWindowID.flickableItem.contentY = mainWindowWrapperItemID.height  - appMainWindowID.height ;
            }
        }
    }




    LeftDrawerListOfBoxes{
        id:leftDrawerInappMainWindowID
        dragMargin:  1
        z:100
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






}
