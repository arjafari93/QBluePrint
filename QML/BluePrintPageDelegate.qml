// BluePrintPage.qml  (Qt 6 compatible - Qt Quick Controls 2)
//
// Notes:
// - QtQuick.Controls 1.x is removed in Qt 6, so the old QCtrl15.ScrollView is replaced.
// - We provide our own Flickable as ScrollView.contentItem so you still have direct access
//   to contentX/contentY and StopAtBounds behavior.

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

// If you use DropShadow / effects elsewhere in this file, use this in Qt 6:
// import QtQuick.Effects

import "BluePrintBoxes"
import "BluePrindLineFlow"
import "LeftDrawerListOfBoxes"
import "BottomStatusBar"
import "TopMenuBar"

import org.bluePrintType.BluePrintPage 1.0

Item {
    id: bpPageItemID

    // Your existing model binding
    property CBluePrintPage pBluePrintPage: modelData

    property real scaleFactorOfApp: bpPageItemID.pBluePrintPage.applicationScaleFactor
    Behavior on scaleFactorOfApp {
        NumberAnimation { duration: 100 }
    }

    // Keep your aliases
    property alias bluePrintBoxesInMainPageID: bluePrintBoxesInMainPageID
    property alias scrollViewInappMainWindowID: scrollViewInappMainWindowID
    property alias mainWindowWrapperItemID: mainWindowWrapperItemID

    // --- Qt 6 replacement for QtQuick.Controls 1.x ScrollView ---
    ScrollView {
        id: scrollViewInappMainWindowID
        anchors.fill: parent
        clip: true

        // Hide scrollbars (similar to your old ScrollBar { visible:false })
        ScrollBar.vertical.visible: false
        ScrollBar.horizontal.visible: false

        // Provide our own Flickable so you keep full control over contentX/Y etc.
        contentItem: Flickable {
            id: mainFlickableID
            boundsBehavior: Flickable.StopAtBounds
            interactive: false
            clip: true

            // Keep sizes in sync with your wrapper item
            contentWidth: mainWindowWrapperItemID.width
            contentHeight: mainWindowWrapperItemID.height

            Item {
                id: mainWindowWrapperItemID
                x: 0
                y: 0

                // Your original logic (removed verticalScrollBar.width since it's hidden now)
                width:  Math.max(scrollViewInappMainWindowID.width,
                                 bpPageItemID.pBluePrintPage.maxBPBoxXpos) * bpPageItemID.scaleFactorOfApp - 5

                height: Math.max(scrollViewInappMainWindowID.height,
                                 bpPageItemID.pBluePrintPage.maxBPBoxYpos) * bpPageItemID.scaleFactorOfApp - 5

                transform: Scale {
                    origin.x: 0
                    origin.y: 0
                    xScale: bpPageItemID.scaleFactorOfApp
                    yScale: bpPageItemID.scaleFactorOfApp
                }

                LineFlowFullScreenRepeater {
                    id: bluePrintLineFlowsInMainPageID
                    model: pBluePrintPage.showPageContentEnable ? pBluePrintPage.listOfFlowConnectionLines : 0
                    z: 5
                }

                BoxesFullScreenRepeater {
                    id: bluePrintBoxesInMainPageID
                    model: pBluePrintPage.showPageContentEnable ? pBluePrintPage.listOfBlueBoxes : 0
                    z: 4
                }

                MouseArea {
                    z: -1
                    anchors.fill: parent
                    onClicked: {
                        // close drawer on click in empty area
                        if (leftDrawerInappMainWindowID && leftDrawerInappMainWindowID.position > 0.9)
                            leftDrawerInappMainWindowID.close()
                    }
                }
            }
        }
    }

    // MouseArea to handle mouse wheel events (ported to the Flickable id)
    MouseArea {
        anchors.fill: scrollViewInappMainWindowID
        hoverEnabled: false
        propagateComposedEvents: true
        acceptedButtons: Qt.NoButton

        onClicked: mouse.accepted = false

        onWheel: (wheel)=> {
            // Ctrl + Wheel => zoom
            if (wheel.modifiers & Qt.ControlModifier) {
                if (wheel.angleDelta.y > 0 && bpPageItemID.pBluePrintPage.applicationScaleFactor < 2.0) {
                    if (bpPageItemID.pBluePrintPage.applicationScaleFactor * 1.1 > 2.0)
                        bpPageItemID.pBluePrintPage.applicationScaleFactor = 2.0
                    else
                        bpPageItemID.pBluePrintPage.applicationScaleFactor *= 1.1
                } else if (wheel.angleDelta.y < 0 && bpPageItemID.pBluePrintPage.applicationScaleFactor > 0.2) {
                    bpPageItemID.pBluePrintPage.applicationScaleFactor *= 0.9
                }
                return
            }

            // Shift + wheel => horizontal scroll
            if (wheel.modifiers & Qt.ShiftModifier) {
                mainFlickableID.contentX -= wheel.angleDelta.y / 120 * 20
            } else {
                // otherwise vertical scroll
                mainFlickableID.contentY -= wheel.angleDelta.y / 120 * 20
            }
        }
    }
}
