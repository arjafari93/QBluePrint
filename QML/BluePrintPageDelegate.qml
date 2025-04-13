import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.5 as QCtrl15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.15
import "BluePrintBoxes"
import "BluePrindLineFlow"
import "LeftDrawerListOfBoxes"
import "BottomStatusBar"
import "TopMenuBar"


import org.bluePrintType.BluePrintPage 1.0

Item {
    id: bpPageItemID
    property CBluePrintPage pBluePrintPage: modelData

    property real scaleFactorOfApp: bpPageItemID.pBluePrintPage.applicationScaleFactor
    Behavior on scaleFactorOfApp {
        NumberAnimation{duration: 100 }
    }
    property alias bluePrintBoxesInMainPageID : bluePrintBoxesInMainPageID
    property alias scrollViewInappMainWindowID : scrollViewInappMainWindowID
    property alias mainWindowWrapperItemID : mainWindowWrapperItemID

    QCtrl15.ScrollView{
        id:scrollViewInappMainWindowID
        anchors.fill: parent // dont change this , onPressed of mouse are in leftdrawer is using this to map the positions
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
            width:    Math.max( scrollViewInappMainWindowID.width , bpPageItemID.pBluePrintPage.maxBPBoxXpos ) * bpPageItemID.scaleFactorOfApp - verticalScrollBar.width- 5
            height:   Math.max( scrollViewInappMainWindowID.height , bpPageItemID.pBluePrintPage.maxBPBoxYpos )  * bpPageItemID.scaleFactorOfApp - verticalScrollBar.width - 5

            transform: Scale {
                origin.x: 0;
                origin.y: 0;
                xScale:  bpPageItemID.scaleFactorOfApp ;
                yScale: bpPageItemID.scaleFactorOfApp ;
            }

            LineFlowFullScreenRepeater{
                id: bluePrintLineFlowsInMainPageID
                model: pBluePrintPage.showPageContentEnable ?  pBluePrintPage.listOfFlowConnectionLines : 0
                z: 5
            }


            BoxesFullScreenRepeater{
                id: bluePrintBoxesInMainPageID
                model:  pBluePrintPage.showPageContentEnable ? pBluePrintPage.listOfBlueBoxes : 0
                z:4
            }
            MouseArea{
                z:-1
                anchors.fill: parent
                onClicked: if(leftDrawerInappMainWindowID.position > 0.9)  leftDrawerInappMainWindowID.close() ; // close drawer on click in empty erea
            }
        }

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
                if (wheel.angleDelta.y > 0 && bpPageItemID.pBluePrintPage.applicationScaleFactor < 2.0 ) {
                    if(bpPageItemID.pBluePrintPage.applicationScaleFactor * 1.1 > 2.0 ) // make sure we dont zoom
                        bpPageItemID.pBluePrintPage.applicationScaleFactor = 2.0 ;
                    else
                        bpPageItemID.pBluePrintPage.applicationScaleFactor *= 1.1
                    // Perform actions for scrolling up with Control pressed
                } else if (wheel.angleDelta.y < 0 && bpPageItemID.pBluePrintPage.applicationScaleFactor > 0.2) {
                    bpPageItemID.pBluePrintPage.applicationScaleFactor *= 0.9
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






}
