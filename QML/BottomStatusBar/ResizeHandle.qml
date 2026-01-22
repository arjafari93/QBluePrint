import QtQuick 2.15
import QtQuick.Window 2.15
import org.QBluePrint.Boxes 1.0
Item {

    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    width: height
    Image {
        id: resizeHandleImageID
        source: BPBoxManager.darkThemeEnabled ?  "qrc:/Images/resizeHandleWhite.png" :  "qrc:/Images/resizeHandleDark.png"
        opacity: 0.5
        Behavior on opacity {
            NumberAnimation{}
        }

        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: parent.height * 0.6
        width: height

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.SizeFDiagCursor
            property bool isResizeEnabled: false
            onPressed: {
                isResizeEnabled = true
            }
            onReleased: {
                isResizeEnabled = false
            }

            onEntered: {
                resizeHandleImageID.opacity = 1
            }
            onExited: {
                resizeHandleImageID.opacity = 0.5
            }
            onPositionChanged: {
                if(isResizeEnabled){
                    var globalPos = resizeHandleImageID.mapToGlobal(mouseX , mouseY);
                    if(appMainWindowID.visibility !=  Window.Windowed)
                        appMainWindowID.visibility =  Window.Windowed
                    if(appMainWindowID.minimumWidth < globalPos.x -  appMainWindowID.x)
                        appMainWindowID.width = globalPos.x -  appMainWindowID.x ;
                    if(appMainWindowID.minimumHeight < globalPos.y -  appMainWindowID.y)
                        appMainWindowID.height = globalPos.y -  appMainWindowID.y ;
                }
            }
        }
    }

}
