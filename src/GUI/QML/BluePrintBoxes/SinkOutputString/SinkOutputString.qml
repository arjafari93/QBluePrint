import QtQuick 2.15
import QtQuick.Controls 2.15

import org.QBluePrint.GUI 1.0
import org.QBluePrint.Boxes 1.0

SingleBoxInstance{
    id:timerSpinBoxMainBoxID

    Image {
        id: name
        source: "qrc:/Images/copy.png"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: height * 0.5
        anchors.topMargin: boxHeaderRectID.height + anchors.rightMargin
        width: height
        height: fontMetricsID.height * 1.5
        opacity:copyTextMouseID.containsMouse ? 1.0 : 0.5
        MouseArea{
            id: copyTextMouseID
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                cBPStatic.copyTextToClipboard(stringToBeDisplayed);
            }
        }
    }

    Label{
        id: stringLabelSinkID
        text: "Output:  " + stringToBeDisplayed
        anchors.horizontalCenter: parent.horizontalCenter
        y: (timerSpinBoxMainBoxID.height - boxHeaderRectID.height) * 0.5
        color: "white"
        font.pointSize: fontMetricsID.font.pointSize
        width: parent.width * 0.8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: fontMetricsID.height * 0.25
        height: parent.height * 0.8
        wrapMode: Text.WrapAnywhere
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment:  Text.AlignVCenter
    }

}















