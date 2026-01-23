import QtQuick 2.15
import Qt.labs.platform 1.1
import QtQuick.Controls
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15
import QtQuick.Dialogs

import Qt5Compat.GraphicalEffects
import QtQuick.Templates 2.12 as TempQuick

import org.QBluePrint.GUI 1.0
import org.QBluePrint.Boxes 1.0

ShadowedRectangle {
    id:mainMenuBarWrapperRectID
    mainBackgroundRectID.radius: 0
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right
    height: fontMetricsID.height * 2

    MenuBar{
        id:mainMenuBarID
        anchors.fill: parent
        anchors.topMargin: - fontMetricsID.height * 0.5
        font.pointSize: fontMetricsID.font.pointSize
        height: fontMetricsID.height * 2.15
        clip: true

        Menu {
            font.pointSize: mainMenuBarID.font.pointSize
            title: "File"
            Material.background: BPBoxManager.darkThemeEnabled ?  "#272D34" : "#E9E9E9"
            MenuItem {
                text: "New Blue Print"
                action: Action {
                    shortcut: "Ctrl+N"
                    onTriggered: {
                        BPBoxManager.addNewBluePrintPage();
                    }
                }
            }
            FileDialog {
                id: openFileDialog
                title: "Open QBlueprint File"
                // selectMultiple: false  // Ensure only one file is selected
                nameFilters: ["QBlueprint Files (*.qbp)"]
                onAccepted: {
                    var currentPageInstance = bpPageRepeaterID.itemAt(BPBoxManager.activePageIndex);
                    if( BPBoxManager.loadBluePrintInfoIntoPage(currentPageInstance.pBluePrintPage, selectedFile.toString().replace("file:///", "")))
                        BPBoxManager.showStatusBarMessage("QBluePrint Loaded Successfully From " + currentPageInstance.pBluePrintPage.currentBluePrintFilePath , 5000)
                    else
                        BPBoxManager.showStatusBarMessage("Failed To Load QBluePrint File" , 5000)
                }
            }
            MenuItem{
                text: "Open BluePrint File"
                action:  Action {
                    shortcut: "Ctrl+O"
                    onTriggered: openFileDialog.open()
                }
            }
            MenuItem{
                text:  "Save"
                action:  Action {
                    id: saveActionID
                    shortcut: "Ctrl+S"
                    onTriggered: {
                        var currentPageInstance = bpPageRepeaterID.itemAt(BPBoxManager.activePageIndex);
                        if(currentPageInstance.pBluePrintPage.currentBluePrintFilePath == ""){
                            saveAsDialog.open();
                            return ;
                        }
                        if( currentPageInstance.pBluePrintPage.saveBluePrintInfo(currentPageInstance.pBluePrintPage.currentBluePrintFilePath) )
                            BPBoxManager.showStatusBarMessage("BluePrint Updated Successfully" , 5000)
                        else
                            BPBoxManager.showStatusBarMessage("Failed To Update Saved File" , 5000)
                    }
                }
            }
            FileDialog {
                id: saveAsDialog
                title: "Save As"
                fileMode: FileDialog.SaveFile
                //selectExisting: false  // Ensures a new file is selected
                nameFilters: ["QBluePrint Files (*.qbp)"]
                onAccepted: {
                    var currentPageInstance = bpPageRepeaterID.itemAt(BPBoxManager.activePageIndex);
                    if( currentPageInstance.pBluePrintPage.saveBluePrintInfo(selectedFile.toString().replace("file:///", "")) )
                        BPBoxManager.showStatusBarMessage("BluePrint Info Saved to " + currentPageInstance.pBluePrintPage.currentBluePrintFilePath , 5000)
                    else
                        BPBoxManager.showStatusBarMessage("Failed To Save File" , 5000)
                }
            }
            MenuItem{
                text:  "Save As"
                action:  Action {
                    shortcut: "Ctrl+Shift+S"
                    onTriggered: {
                        saveAsDialog.open();
                    }
                }
            }

            MenuItem {
                text: "Quit"
                onTriggered: {
                    Qt.quit();
                }
            }
        }
        Menu {
            title: "Edit"
            Material.background: BPBoxManager.darkThemeEnabled ?  "#272D34" : "#E9E9E9"
            font.pointSize: mainMenuBarID.font.pointSize
            MenuItem {
                text: "Clean The Workspace"
                onTriggered: {
                    var currentPageInstance = bpPageRepeaterID.itemAt(BPBoxManager.activePageIndex);
                    currentPageInstance.pBluePrintPage.clearCurrentBluePrintSession();
                }
            }
            Menu {
                title: "Preferences"
                font.pointSize: mainMenuBarID.font.pointSize
                MenuItem {
                    text: (BPBoxManager.terminalGlowEnable ?  "Disable " : "Enable ") + "Termnial Glow"
                    onTriggered: {
                        BPBoxManager.terminalGlowEnable = !BPBoxManager.terminalGlowEnable ;
                    }
                }
            }
        }
        Menu {
            title: "Help"
            Material.background: BPBoxManager.darkThemeEnabled ?  "#272D34" : "#E9E9E9"

            font.pointSize: mainMenuBarID.font.pointSize
            MenuItem {
                text: "About Software"
                onTriggered: {
                    var tempComp = Qt.createComponent("qrc:/org/QBluePrint/GUI/QML/SoftwareInfo/SoftwareInfoPopup.qml");
                    var tempObj = tempComp.createObject(appMainWindowID);
                }
            }
        }
    }

    Label{
        id:applicaitonNameLabelID
        anchors.centerIn: parent
        text: appMainWindowID.title
        font.pointSize: fontMetricsID.font.pointSize + 1
    }

    ApplicationIconImage{
        id:appIconImageID
    }

    WindowControlButtons{
        id:winControlBtnsID
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        property int startX: 0
        property int startY: 0
        z:-1
        cursorShape : Qt.SizeAllCursor

        onPressed: (mouse)=>{
                       startX = mouse.x
                       startY = mouse.y
                   }
        onPositionChanged:(mouse)=> {
                              if(appMainWindowID.visibility ==  Window.Maximized )
                              appMainWindowID.visibility =  Window.Windowed
                              appMainWindowID.setX(appMainWindowID.x+mouse.x - startX)
                              appMainWindowID.setY(appMainWindowID.y+mouse.y - startY)
                          }
        onDoubleClicked: {
            if(appMainWindowID.visibility ==  Window.Maximized)
                appMainWindowID.visibility =  Window.Windowed
            else
                appMainWindowID.visibility =  Window.Maximized
        }
    }
}

