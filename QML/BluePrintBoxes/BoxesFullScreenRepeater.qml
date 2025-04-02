import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQuick.Window 2.15
import "SingleBoxInstance"

import org.bluePrintType.BPStatic 1.0

Repeater{
    id:boxesMainRepeaterID
    anchors.fill: parent
    model: pBluePrintPage.listOfBlueBoxes

    delegate: Loader{
        source: appMainWindowID.defineGUIDeleage (blueBox_GUIType)
        asynchronous: true
    }

}
