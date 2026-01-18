import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQuick.Window 2.15

Shape {
    id:shapeID
    x:flowLine_startX
    y:flowLine_startY

    //width:  flowLine_endX - flowLine_startX
    // height: flowLine_endY - flowLine_satrtY
    asynchronous: true
    ShapePath {
        strokeWidth: flowLine_strokeWidth
        strokeColor: flowLine_color
        fillColor: "transparent" // Set the fill color to transparent
        //strokeStyle: ShapePath.DashLine
        //dashPattern: [ 1, 4 ]
        //startX: flowLine_endX; startY:flowLine_endY
        PathCubic {
            id:pathCuebID
            x: flowLine_endX; y: flowLine_endY
            control1X: x/2 ; control1Y: 0
            control2X: x/2 ; control2Y: y
        }
    }
    MouseArea {
        anchors.fill: parent // Make the MouseArea cover the entire shape
        hoverEnabled: true
        // onEntered: {
        //     console.log("entered ")
        // }

        // onClicked: {
        //     console.log("Shape clicked")
        // }
    }
}




