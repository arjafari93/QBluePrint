import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

Item {
    anchors.fill: parent

    property alias closeButtonID: closeButtonID
    property alias maximizeButtonID: maximizeButtonID
    property alias minimizeButtonID: minimizeButtonID

    Rectangle {
        id:closeButtonID
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        width: height * 1.4
        height: parent.height
        color: closeBtnMouseID.containsMouse ? "red" : "transparent"
        MouseArea {
            id:closeBtnMouseID
            hoverEnabled: true
            anchors.fill: parent
            onClicked: Qt.quit()
            onEntered: {
                cursorShape = Qt.PointingHandCursor;
            }
        }
        Image{
            anchors.centerIn: parent
            height: parent.height * 0.4
            width: height
            source: BPBoxManager.darkThemeEnabled ? "qrc:/Images/closeButtonWhite.png" : "qrc:/Images/closeButtonDark.png"
            opacity: closeBtnMouseID.containsMouse ? 1 : 0.5
        }
    }

    Rectangle {
        id:maximizeButtonID
        anchors.right: closeButtonID.left
        anchors.verticalCenter: parent.verticalCenter
        width: height * 1.25
        height: parent.height
        color: maximizeMouseID.containsMouse ?( BPBoxManager.darkThemeEnabled ?  "#15ffffff" : "#20000000" ):  "transparent"
        MouseArea {
            id: maximizeMouseID
            hoverEnabled: true
            anchors.fill: parent
            onClicked: {
                if(appMainWindowID.visibility ==  Window.Maximized)
                    appMainWindowID.visibility =  Window.Windowed
                else
                    appMainWindowID.visibility =  Window.Maximized
            }
            onEntered: {
                cursorShape = Qt.PointingHandCursor;
            }
        }

        Image{
            function findImageSource(mainWinVisiblty , darkThemeEnabled){
                if(mainWinVisiblty ==  Window.Maximized)
                    return (BPBoxManager.darkThemeEnabled ? "qrc:/Images/maximizedDoubleWhite.png" :  "qrc:/Images/maximizedDoubleDark.png");
                return (BPBoxManager.darkThemeEnabled ? "qrc:/Images/maximizedSingleWhite.png":  "qrc:/Images/maximizedSingleDark.png");
            }

            anchors.centerIn: parent
            height: parent.height * 0.5
            width: height
            source: findImageSource( appMainWindowID.visibility, BPBoxManager.darkThemeEnabled )
            opacity: maximizeMouseID.containsMouse ? 1 : 0.5
        }
    }

    Rectangle {
        id:minimizeButtonID
        anchors.right: maximizeButtonID.left
        anchors.verticalCenter: parent.verticalCenter
        width: height * 1.25
        height: parent.height
        color:  minimizeMouseID.containsMouse ? ( BPBoxManager.darkThemeEnabled ?  "#15ffffff" : "#20000000" )  :  "transparent"
        MouseArea {
            id: minimizeMouseID
            hoverEnabled: true
            anchors.fill: parent
            onClicked: {
                appMainWindowID.visibility = Window.Minimized
            }
            onEntered: {
                cursorShape = Qt.PointingHandCursor;
            }
        }
        Rectangle{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height * 0.3
            height: parent.height * 0.1
            width: parent.width * 0.5
            radius: height * 0.25
            color: BPBoxManager.darkThemeEnabled ? "white" : "black"
            opacity: minimizeMouseID.containsMouse ? 1 : 0.5
        }
    }

    Rectangle {
        id:themeSelectorRectID
        anchors.right: minimizeButtonID.left
        anchors.rightMargin: height * 0.5
        anchors.verticalCenter: parent.verticalCenter
        width: height * 1.25
        height: parent.height
        color:  themeSelectionMouseID.containsMouse ? ( BPBoxManager.darkThemeEnabled ?  "#15ffffff" : "#20000000" )  :  "transparent"
        MouseArea {
            id: themeSelectionMouseID
            hoverEnabled: true
            anchors.fill: parent
            onClicked: {
                 BPBoxManager.darkThemeEnabled = !BPBoxManager.darkThemeEnabled;
            }
            onEntered: {
                cursorShape = Qt.PointingHandCursor;
            }
        }

        Image {
            id: themeSelectorImageID
            source: BPBoxManager.darkThemeEnabled ? "qrc:/Images/sunWhite.png" : "qrc:/Images/moonDark.png"
            anchors.centerIn: parent
            height: parent.height * 0.7
            width: height
            opacity: themeSelectionMouseID.containsMouse ? 1.0 : 0.5
        }
    }

}
