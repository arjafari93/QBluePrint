import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.15

Item{
    id: removeThumbnailItemID
    property alias removeThumbnailCompRectID: removeThumbnailCompRectID
    z:10
    anchors.top:topManuBarInMainPageID.bottom
    anchors.left: parent.left
    anchors.right: parent.right
    height: removeThumbnailCompRectID.height
    clip: true
    Rectangle{
        id: removeThumbnailCompRectID
        z:10
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        opacity: 0
        visible: opacity > 0.01
        Behavior on opacity {
            NumberAnimation{}
        }

        anchors.topMargin: -height * 0.5
        height: fontMetricsID.height * 10
        color: "transparent"
        property bool removeAreaIntersection: false
        property real transparentPos: removeAreaIntersection ? 0.25 : 0.1
        Behavior on transparentPos{
            NumberAnimation{duration: 300; easing.type: Easing.OutBack}
        }

        RadialGradient {
                anchors.fill: parent
                anchors.leftMargin: parent.width * 0.25
                anchors.rightMargin:  parent.width * 0.25
                anchors.bottomMargin:   removeThumbnailCompRectID.removeAreaIntersection ?  0 : fontMetricsID.height * 2
                Behavior on anchors.bottomMargin{
                    NumberAnimation{duration: 300; easing.type: Easing.OutBack}
                }

                gradient: Gradient {
                    GradientStop { position: removeThumbnailCompRectID.transparentPos; color: "#C70039" }
                    GradientStop { position: 0.5; color: "transparent" }
                }
            }

        Image {
            id: trashIconID
            z:10
            source: "qrc:/Images/trash.png"
            anchors.top: parent.verticalCenter
            anchors.topMargin: height * 0.75
            anchors.horizontalCenter: parent.horizontalCenter
            width: fontMetricsID.height * 1.5
            height: width
            scale: removeThumbnailCompRectID.removeAreaIntersection  ? 1.5 : 1
            Behavior on scale{
                NumberAnimation{}
            }
        }
    }

}


