import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQuick.Window 2.15
import "SingleBoxInstance"

import org.bluePrintType.BPStatic 1.0
import org.bluePrintType.OperationBox 1.0

Repeater{
    id:boxesMainRepeaterID
    anchors.fill: parent
    model: pBluePrintPage.listOfBlueBoxes
    delegate: Loader{
        property COperationBox pBoxInstance: modelData

        function checkVisibility(flickCntntX, flickCntntY, scrollViewWidth, scrollViewHeight,  itemScale , boxWidth, boxHeight, BoxPosX, boxPosY ) {
            // Transform item position with scale
            const scaledX = itemScale * BoxPosX
            const scaledY = itemScale * boxPosY
            const scaledW = itemScale * boxWidth
            const scaledH = itemScale * boxHeight

            const visibleLeft = flickCntntX
            const visibleRight = flickCntntX + scrollViewWidth
            const visibleTop = flickCntntY
            const visibleBottom = flickCntntY + scrollViewHeight

            const itemRight = scaledX + scaledW
            const itemBottom = scaledY + scaledH

            const isVisible = (
                                itemRight > visibleLeft &&
                                scaledX < visibleRight &&
                                itemBottom > visibleTop &&
                                scaledY < visibleBottom
                                );
            return isVisible;
        }

        property bool isItemNearVisibleArea : checkVisibility(scrollViewInappMainWindowID.contentItem.contentX,
                                                              scrollViewInappMainWindowID.contentItem.contentY,
                                                              scrollViewInappMainWindowID.width,
                                                              scrollViewInappMainWindowID.height,
                                                              bpPageItemID.scaleFactorOfApp,
                                                              pBoxInstance.blueBox_width,
                                                              pBoxInstance.blueBox_height,
                                                              pBoxInstance.blueBox_xPos,
                                                              pBoxInstance.blueBox_yPos
                                                              );

        source: isItemNearVisibleArea ?  appMainWindowID.defineGUIDeleage (blueBox_GUIType) : ""
        asynchronous: true
    }

}
