import QtQuick 2.15

Image {
    id: appIconImageID
    z:10
    source: "qrc:/Images/AppICon.png"
    smooth: true
    mipmap: true
    antialiasing: true
    height:   appIconImageID.parent.height * 1.5
    width: height

    anchors.top: parent.top
    anchors.topMargin: appImageMouseID.containsMouse ? fontMetricsID.height*0.8 : 0
    Behavior on anchors.topMargin {
        NumberAnimation{}
    }

    anchors.right: applicaitonNameLabelID.left
    anchors.rightMargin: height * 0.75

    transform: Scale {
        origin.x: appIconImageID.width * 0.5
        origin.y: appIconImageID.height*0.5
        xScale: appImageMouseID.containsMouse ? 1.7 : 1
        yScale: appImageMouseID.containsMouse ? 1.7 : 1
        Behavior on xScale{
            NumberAnimation{}
        }
        Behavior on yScale{
            NumberAnimation{}
        }
    }

    MouseArea{
        id:appImageMouseID
        anchors.fill: parent
        hoverEnabled: true
        cursorShape : Qt.PointingHandCursor
        onClicked: {
            var tempComp = Qt.createComponent("qrc:/QML/SoftwareInfo/SoftwareInfoPopup.qml");
            var tempObj = tempComp.createObject(appMainWindowID);
        }
    }
}
