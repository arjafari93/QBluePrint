import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects
import QtQuick.Controls.Material 2.15

Drawer {
    id: leftSideDrawerID
    height:  appMainWindowID.height
    closePolicy: Drawer.CloseOnEscape
    width: Screen.width * 0.2
    edge: Qt.LeftEdge
    enter: Transition { SmoothedAnimation { velocity: 3 } }
    exit:  Transition { SmoothedAnimation { velocity: 3 } }
    modal: false
    dim: false
    clip: false
    property var dragImageObject: undefined
    interactive: false

    background: Rectangle{
        color: "#e0000000"
    }

    TextArea{
        id: searchTextBoxID
        z:10
        Material.theme: Material.Dark
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: fontMetricsID.height * 0.5
        height: fontMetricsID.height * 3
        font.pointSize:  fontMetricsID.font.pointSize + 2
        selectByMouse: true
        placeholderText: "Search A Box"
        onTextChanged: {
            // Remove any newline characters from the text
            if(text.indexOf("\n") != -1 ){
                text = text.replace(/\n/g, "");
                appMainWindowID.forceActiveFocus();
            }
            if(searchTextBoxID.text.length < 2 ){
                Material.accent = "red" ;
                BPBoxManager.isArchiveSearchActive = false;
            }else{
                Material.accent = Material.Purple
                BPBoxManager.isArchiveSearchActive = true;
                BPBoxManager.boxListSearchBoxTextChanged( text );
            }
        }
        Keys.onPressed: (event)=> {
                            if (event.key === Qt.Key_Escape ) {
                                event.accepted = true;
                                appMainWindowID.forceActiveFocus();
                            }
                        }

        Rectangle{
            anchors.fill: parent
            z:-1
            color: "#171C22"
        }
    }

    ListView{
        id:bpBoxBrowserListViewID
        anchors.top: searchTextBoxID.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        clip: true
        model: BPBoxManager.isArchiveSearchActive ?  BPBoxManager.bpBoxBrowserListProxy : BPBoxManager.bpBoxBrowserList
        delegate: bpBoxBrowserDelegateCompID
        spacing: 2
        interactive: true
        ScrollBar.vertical: ScrollBar {
            id:scrollBarOfListViewID
            anchors.right: parent.right
            policy: ScrollBar.AlwaysOn
        }
        section.property: "blueBox_Catgr"
        section.criteria: ViewSection.FullString
        section.delegate: Rectangle {
            width: bpBoxBrowserListViewID.width - scrollBarOfListViewID.width
            height: fontMetricsID.height * 3
            gradient: Gradient {
                orientation: Gradient.Vertical
                GradientStop { position: 0.0; color:   "#808080" }
                GradientStop { position: 0.5; color:   "black" }
                GradientStop { position: 1.0; color:   "#404040" }
            }
            //color: "black"
            required property string section
            Label {
                text: cBPStatic.getNameOfCategory( parent.section  )
                anchors.centerIn: parent
                font.pointSize: 14
                color: "white"
                //font.bold: true
            }
        }
    }

    Component{
        id: bpBoxBrowserDelegateCompID
        Rectangle{
            id: bpBoxBrowserDelegateMainRectID
            width: bpBoxBrowserListViewID.width - scrollBarOfListViewID.width
            anchors.left: parent ?  parent.left : undefined
            height: fontMetricsID.height * 3
            border.color: "transparent"
            radius: 5
            property real gradPos: pbBoxDelagateMouseAreaID.containsMouse ?  pbBoxDelagateMouseAreaID.mouseX/width : 0.9
            Behavior on gradPos {
                NumberAnimation{}
            }

            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: gradPos - 0.2; color:  "black" }
                GradientStop { position: gradPos - 0.1; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.1 ) }
                GradientStop { position: gradPos; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.7 ) }
                GradientStop { position: 1.0; color:  appMainWindowID.applyOpacityToColor(  blueBox_HeadColor , 0.25 ) }
            }

            Rectangle{
                anchors.fill: parent
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop { position: 0.0; color:  "#30000000" }
                    GradientStop { position: 0.5; color:   "black" }
                    GradientStop { position: 1.0; color:  "#30000000" }
                }
            }

            Label {
                id: bpSymbolTextID
                text: typeof operatorSymbol !== "undefined" ? operatorSymbol : ""
                color: "white"
                font.pointSize: 14
                font.bold: true
                anchors.left: parent.left
                anchors.leftMargin: height * 0.75
                anchors.verticalCenter: parent.verticalCenter
            }
            Image {
                id: boxIcanImageID
                source:  typeof operatorSymbol === "undefined" ? blueBox_HeaderIcon : ""
                height: bpSymbolTextID.height
                width: height
                anchors.left: parent.left
                anchors.leftMargin: height * 0.5
                anchors.verticalCenter: parent.verticalCenter
            }
            Label{
                id: bpBoxNameLabelID
                anchors.verticalCenter: parent.verticalCenter
                anchors.centerIn: parent
                text: blueBox_name
                color: "white"
            }

            Rectangle{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                height: 1
                anchors.leftMargin: fontMetricsID.height
                anchors.rightMargin:  fontMetricsID.height
                color: "#40ffffff"
            }

            MouseArea{
                id: pbBoxDelagateMouseAreaID
                property  bool isMouseAreaPressed : false
                anchors.fill: parent
                hoverEnabled: true
                propagateComposedEvents: true
                onEntered: {
                    cursorShape = Qt.PointingHandCursor
                    bpBoxBrowserDelegateMainRectID.border.color = "#90ffffff"
                }
                onExited: {
                    bpBoxBrowserDelegateMainRectID.border.color = "transparent"
                }
                onPressed:(mouse)=> {
                    removeThumbnailCompRectID.opacity = 1
                    bpBoxBrowserListViewID.interactive = false ;
                    if(leftSideDrawerID.dragImageObject != undefined){
                        leftSideDrawerID.dragImageObject.destroy()
                        console.log("component wasnt destroyed properly");
                    }
                    var currentPageInstance = bpPageRepeaterID.itemAt(BPBoxManager.activePageIndex);
                    if(!currentPageInstance){
                        console.log("onPressed: empty item at repeater detected " , currentPageInstance);
                        return ;
                    }

                    var posInParentCoord = bpBoxBrowserDelegateMainRectID.mapToItem(currentPageInstance.mainWindowWrapperItemID, mouse.x , mouse.y );
                    var pathToComp = appMainWindowID.defineGUIDeleage(blueBox_GUIType);
                    var dragBoxComp = Qt.createComponent(pathToComp);
                    leftSideDrawerID.dragImageObject =
                            dragBoxComp.createObject(currentPageInstance ,
                                                     {
                                                         "x":(posInParentCoord.x - mouse.x*0.5) *  currentPageInstance.scaleFactorOfApp  - currentPageInstance.scrollViewInappMainWindowID.contentItem.contentX ,
                                                         "y":(posInParentCoord.y - mouse.y*0.5 )*  currentPageInstance.scaleFactorOfApp  - currentPageInstance.scrollViewInappMainWindowID.contentItem.contentY ,
                                                         "opacity":0.4,
                                                         "scale":  currentPageInstance.scaleFactorOfApp
                                                     });
                    pbBoxDelagateMouseAreaID.drag.target =  leftSideDrawerID.dragImageObject ;
                }
                onReleased: (mouse)=>{
                    removeThumbnailCompRectID.opacity = 0;
                    bpBoxBrowserListViewID.interactive = true;
                    if(leftSideDrawerID.dragImageObject == undefined){
                        console.log("ERROR: component is not created properly");
                        return ;
                    }

                    var posInTrash = bpBoxBrowserDelegateMainRectID.mapToGlobal( mouse.x, mouse.y);
                    if(posInTrash.y <= (appMainWindowID.y + removeThumbnailCompRectID.height * 0.5) ){
                        leftSideDrawerID.dragImageObject.destroy();
                        leftSideDrawerID.dragImageObject = undefined;
                        return;
                    }


                    var currentPageInstance = bpPageRepeaterID.itemAt(BPBoxManager.activePageIndex);
                    if(!currentPageInstance){
                        console.log("onReleased : empty item at repeater detected " , currentPageInstance);
                        return ;
                    }
                    var posInParentCoord = leftSideDrawerID.dragImageObject.mapToItem(currentPageInstance.mainWindowWrapperItemID, 0 , 0 );
                    // console.log("posInParentCoord is " , posInParentCoord.x , posInParentCoord.y )
                    var res = currentPageInstance.pBluePrintPage.createNewBoxFromGivenType( blueBox_name , posInParentCoord.x , posInParentCoord.y  );
                    leftSideDrawerID.dragImageObject.destroy();
                    leftSideDrawerID.dragImageObject = undefined;
                }

                onPositionChanged: (mouse)=> {
                    var posInParentCoord = bpBoxBrowserDelegateMainRectID.mapToGlobal( mouse.x, mouse.y);
                    if(posInParentCoord.y <= (appMainWindowID.y + removeThumbnailCompRectID.height * 0.5) ){
                        removeThumbnailCompRectID.removeAreaIntersection = true
                    }else{
                        removeThumbnailCompRectID.removeAreaIntersection = false
                    }
                }
            }
        }
    }

}
