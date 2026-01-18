import QtQuick 2.15
import Qt5Compat.GraphicalEffects
import QtQuick.Controls.Material 2.15

Item {
    id:shaddowRectWrapperItemID

    property alias mainBackgroundRectID: mainBackgroundRectID
    property alias mainBackgroundShaddowID: mainBackgroundShaddowID

    Rectangle{
        id:mainBackgroundRectID
        anchors.fill: parent
        color: Material.background //  "#22272E"
        border.color: BPBoxManager.darkThemeEnabled ? "#3E474E" : "#EBF0FF"
        radius: fontMetricsID.height
        visible: false
    }

    DropShadow {
        id:mainBackgroundShaddowID
        anchors.fill: mainBackgroundRectID
        horizontalOffset: 1
        verticalOffset: 1
        radius: 10
        samples: 12
        color:  Material.accent
        source: mainBackgroundRectID
    }
}
