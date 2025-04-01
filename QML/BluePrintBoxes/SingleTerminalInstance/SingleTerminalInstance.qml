import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import org.bluePrintType.BPStatic 1.0
import org.bluePrintType.IOTerminal 1.0

Item{
    id: terminalMainItemID
    property bool isInputTerminal : true
    property CIOTerminal pTerminalInstance: modelData
    height: fontMetricsID.height * 2 // dont change this
    anchors.left: isInputTerminal ?  parent.left : undefined
    anchors.right: isInputTerminal ?  undefined : parent.right
    anchors.rightMargin:  pTerminalInstance.emissionEnabled ? 0 : 3




    Component.onCompleted: {
        // Schedule a function to be called in the next iteration of the event loop
        // we are doing this bcz  boxHeaderRectID.height doesnt have value at this moment and its zero
        //        Qt.callLater(function() {
        //            // Perform actions in the next iteration of the main loop
        //            terminalXPos = 0 ;
        //            terminalYPos = (terminalMainItemID.height * index ) +  boxHeaderRectID.height + listViewOfInputTerminalsID.anchors.topMargin ;
        //            terminalSize = terminalImageWrapperItemID.height ;
        //        });
    }

    Item {
        id: terminalImageWrapperItemID
        anchors.left: isInputTerminal ?  parent.left : undefined
        anchors.right: isInputTerminal ?  undefined : parent.right
        anchors.leftMargin: isInputTerminal ?  height * 0.1 : 0
        anchors.rightMargin:  isInputTerminal ? 0 : height * 0.1
        anchors.verticalCenter: parent.verticalCenter
        height: fontMetricsID.height * 2 * 0.65
        width: height
        Image {
            id: terminalImageID
            antialiasing: true
            mipmap: true
            smooth: true
            source: Object.keys(listOfConnectedLines).length > 0  ?  "qrc:/Images/terminalFull.png" :  "qrc:/Images/terminalEmpty.png"
            anchors.fill: parent
            // visible: littleMouseAreaID.containsMouse == false
            layer.enabled: true
            layer.effect: ShaderEffect {
                property variant source: ShaderEffectSource { sourceItem: terminalImageID; hideSource: true }
                property color customColor: pTerminalInstance.terminalColor
                fragmentShader: "
                            varying highp vec2 qt_TexCoord0;
                            uniform sampler2D source;
                            uniform lowp vec4 customColor; // Custom color uniform
                            void main() {
                                // Get the original color of the pixel
                                lowp vec4 color = texture2D(source, qt_TexCoord0);
                                if(color.r + color.g + color.b < 0.2 ){
                                    gl_FragColor = color ;
                                    return ;
                                }
                                gl_FragColor = customColor;
                            }
                        "
            }
        }
    }

    Rectangle{
        id: emissionDisabledRectID
        anchors.left: terminalImageWrapperItemID.right
        anchors.verticalCenter: terminalImageWrapperItemID.verticalCenter
        height: terminalImageWrapperItemID.height
        width: 4
        color: "red"
        visible: !pTerminalInstance.emissionEnabled
    }



    Glow {
        id: terminalGlowID
        property bool isPassingValue: false
        anchors.fill: terminalImageWrapperItemID
        radius: 5
        samples: 5
        color: pTerminalInstance.terminalColor
        Timer{
            id: turnOfPassingValEffectTimerID
            running: false
            interval: 250
            onTriggered: terminalGlowID.isPassingValue = false
        }

        Connections{
            target: pTerminalInstance
            function onNodeIsPassingNewValue(){
                terminalGlowID.isPassingValue = true;
                turnOfPassingValEffectTimerID.restart();
            }
        }

        source: terminalImageWrapperItemID
        opacity:  littleMouseAreaID.containsMouse == true || isTerminalHovered == true || isPassingValue == true ? 0.7 : 0
        Behavior on opacity {
            NumberAnimation{}
        }
        visible: opacity > 0.01
    }


    Label{
        id:nameOfTerminalLabelID
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: isInputTerminal ?  terminalImageWrapperItemID.right : undefined
        anchors.right:  isInputTerminal ?   undefined : terminalImageWrapperItemID.left
        anchors.leftMargin: isInputTerminal ? height * 0.5 : 0
        anchors.rightMargin: isInputTerminal ?  0 : height * 0.5
        text: terminalName
        font.bold:  littleMouseAreaID.containsMouse == true || isTerminalHovered == true
        font.pointSize: fontMetricsID.font.pointSize
        color: "white"
    }

    ToolTip{
        id:terminalToolTipID
        onVisibleChanged: {
            terminalToolTipID.text =  cBPStatic.getNameOfTypeAsString(pTerminalInstance) + " " + pTerminalInstance.getTerminalCurrentData()
        }
        text: cBPStatic.getNameOfTypeAsString(pTerminalInstance)
        timeout: 30000
    }

    MouseArea {
        id:littleMouseAreaID
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        propagateComposedEvents: true
        onEntered: {
            cursorShape = Qt.PointingHandCursor
            terminalToolTipID.visible = true
        }
        onExited: {
            terminalToolTipID.visible = false
        }

        onPressed: {
            boxMainRectID.forceActiveFocus();

            if (mouse.button === Qt.RightButton) {

                for(var iter = terminalConnectedLinesMenusID.count ; iter > 0 ; iter-- ){ // lets clear old menu
                    terminalConnectedLinesMenusID.removeItem( terminalConnectedLinesMenusID.itemAt(0) );
                }
                if(Object.keys(listOfConnectedLines).length != 0 ){
                    // Create a Category Title (Non-clickable MenuItem)
                    var categoryTitle = Qt.createQmlObject(`
                                                           import QtQuick 2.15
                                                           import QtQuick.Controls 2.15
                                                           MenuItem {
                                                           text: "Remove A Connection"
                                                           enabled: false
                                                           font.bold: true
                                                           }
                                                           `, terminalConnectedLinesMenusID);
                    terminalConnectedLinesMenusID.addItem(categoryTitle);


                    for(var iter = 0 ; iter < Object.keys(listOfConnectedLines).length ; iter++ ){
                        var menuComp = Qt.createComponent("qrc:/QML/BluePrintBoxes/SingleTerminalInstance/TerminalMenus.qml");
                        var menuObject = menuComp.createObject(terminalMainItemID , {"text":  "Flow Line " + iter , "indexOfMenuItem" : iter });
                        terminalConnectedLinesMenusID.addItem(menuObject);
                    }

                    // Add Separator
                    var separator = Qt.createQmlObject(`
                                                       import QtQuick 2.15
                                                       import QtQuick.Controls 2.15
                                                       MenuSeparator { }
                                                       `, terminalConnectedLinesMenusID);
                    terminalConnectedLinesMenusID.addItem(separator);
                }
                // Create another Category Title
                var categoryTitle2 = Qt.createQmlObject(`
                                                        import QtQuick 2.15
                                                        import QtQuick.Controls 2.15
                                                        MenuItem {
                                                        text: "Edit Terminal"
                                                        enabled: false
                                                        font.bold: true
                                                        }
                                                        `, terminalConnectedLinesMenusID);
                terminalConnectedLinesMenusID.addItem(categoryTitle2);

                // Add items for category 2
                var menuObject = changeDataMenuCompID.createObject(terminalMainItemID, {
                                                           "text": "Change Data"
                                                       });
                // change emission menu

                var emissionCntrlComp = Qt.createQmlObject(`
                                                        import QtQuick 2.15
                                                        import QtQuick.Controls 2.15
                                                        MenuItem {
                                                        text: (pTerminalInstance.emissionEnabled ?  "Disable" : "Enable" ) + " Emission"
                                                        onTriggered: pTerminalInstance.emissionEnabled = ! pTerminalInstance.emissionEnabled ;
                                                        }
                                                        `, terminalConnectedLinesMenusID);
                terminalConnectedLinesMenusID.addItem(emissionCntrlComp);
                terminalConnectedLinesMenusID.addItem(menuObject);



                terminalConnectedLinesMenusID.open();
                return ;
            }

            if( isInputTerminal == true )
                return ;
            BPBoxManager.isLineFlowDrawActive = true;
            BPBoxManager.lineFlowStartedFromConnectionPoint(  pTerminalInstance   );
        }

        onReleased: {
            if(BPBoxManager.isLineFlowDrawActive == false ) // this is possible for example when user has clicked on an input
                return ;
            BPBoxManager.isLineFlowDrawActive = false ;
            var posInParentCoord = boxesMainRepeaterID.mapFromItem( terminalMainItemID , mouse.x, mouse.y);
            // console.log( mouse.x , mouseX , posInParentCoord.x , posInParentCoord.y );
            BPBoxManager.lineFlowReleased(    posInParentCoord.x , posInParentCoord.y  );
        }

        onPositionChanged: {
            if( BPBoxManager.isLineFlowDrawActive == false )
                return ;
            var posInParentCoord = boxesMainRepeaterID.mapFromItem( terminalMainItemID , mouse.x, mouse.y);
            // console.log( mouse.x , mouseX , posInParentCoord.x , posInParentCoord.y );
            BPBoxManager.lineFlowPosChagnedFromConnectionPoint(  mouseX - terminalMainItemID.width ,  mouseY - terminalMainItemID.height * 0.5 ,  posInParentCoord.x , posInParentCoord.y  );
        }
    }



    Menu {
        id: terminalConnectedLinesMenusID
        x: isInputTerminal ? 0 : -width
        font.pointSize: 8
    }


       Component {
           id: changeDataMenuCompID
           MenuItem {
               id: changeDataMenuID
               MouseArea{
                   anchors.fill: parent
                   hoverEnabled: true
                   propagateComposedEvents: true
                   onClicked: {
                       var menuComp = Qt.createComponent("qrc:/QML/BluePrintBoxes/SingleTerminalInstance/ChangeTerminalDataPopUp.qml");
                       var menuObject = menuComp.createObject(appMainWindowID , {"pTerminalInstance": pTerminalInstance });
                       terminalConnectedLinesMenusID.close()
                   }
               }
           }
       }



}










