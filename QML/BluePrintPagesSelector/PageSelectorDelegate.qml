import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import org.bluePrintType.BluePrintPage 1.0

Rectangle {
    id: selectorDlgtRectID
    color: BPBoxManager.activePageIndex == index ?
               Material.backgroundColor :  (BPBoxManager.darkThemeEnabled ?
                                                Qt.lighter(Qt.lighter(Material.backgroundColor )) :  "#999999" )

    border.color: slctrMouseID.containsMouse ?    (BPBoxManager.darkThemeEnabled ? "#60ffffff" : "#60000000")  :
                                               (BPBoxManager.darkThemeEnabled ? "#30ffffff" : "#30000000")
    property CBluePrintPage pBluePrintPage: modelData
    height:  Math.min( (pageNameLabelID.text.length + 2 ) * fontMetricsID.height  , fontMetricsID.height * 10 )
    ToolTip{
        id: fullPathTipID
        text: pBluePrintPage.currentBluePrintFilePath
        visible: pBluePrintPage.currentBluePrintFilePath != "" && slctrMouseID.containsMouse
        timeout: 30000
    }

    Label{
        id: pageNameLabelID
        text:   pBluePrintPage.currentBluePrintFilePath == "" ? "New" : cBPStatic.getFileNameFromPath( pBluePrintPage.currentBluePrintFilePath)
        anchors.centerIn: parent
        wrapMode: Text.NoWrap  // Prevents wrapping
        elide: Text.ElideRight  // Ensures that overflowing text gets "..."
        width: parent.height  // Swap width and height due to rotation
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        clip: true  // Clip excess text
        opacity:  BPBoxManager.activePageIndex == index ? 1.0 : (slctrMouseID.containsMouse ? 1.0 : 0.6)
        transform: Rotation {
            angle: -90
            origin.x: pageNameLabelID.width / 2
            origin.y: pageNameLabelID.height / 2
        }
    }

    MouseArea{
        id: slctrMouseID
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            if (mouse.button === Qt.RightButton){
                slctrBtnMenuID.open();
                return ;
            }
                BPBoxManager.activePageIndex = index
        }
    }

    Image {
        id: hideIconID
        source: "qrc:/Images/hideIcon.png"
        width: parent.width * 0.5
        height: width
        anchors.top: parent.top
        x: (selectorDlgtRectID.width - hideIconID.width + leftMarkerRectID.width) * 0.5
        z:100
        visible: !selectorDlgtRectID.pBluePrintPage.showPageContentEnable
    }
    Rectangle{
        id: leftMarkerRectID
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 5
        color: selectorDlgtRectID.pBluePrintPage.showPageContentEnable ?  Material.accent : "#bb0000"
        visible: BPBoxManager.activePageIndex == index
    }

    Menu {
        id: slctrBtnMenuID
        font.pointSize: 8
        MenuItem{
            text: selectorDlgtRectID.pBluePrintPage.showPageContentEnable ? "Hide Content" : "show Content"
            onTriggered: {
                selectorDlgtRectID.pBluePrintPage.showPageContentEnable = !selectorDlgtRectID.pBluePrintPage.showPageContentEnable;
            }
        }
        MenuItem{
            text: "Close Page"
            onTriggered: {
                if( selectorDlgtRectID.pBluePrintPage.listOfBlueBoxes.length > 0 || selectorDlgtRectID.pBluePrintPage.currentBluePrintFilePath != ""  ){
                    // there are some boxes in the main page, make sure user wants to exit
                    var exitConfirmComp = Qt.createComponent("qrc:/QML/BluePrintPagesSelector/ExitConfirmationPopup.qml");
                    var removeObj = exitConfirmComp.createObject(appMainWindowID , {"indexOfPage":index} );
                    return ;
                }
                // if we are here it means the page is empty
                Qt.callLater(function() { // can cause crashes if called sync
                    BPBoxManager.removeBluePrintPage(index);
                });
            }
        }
    }

}
