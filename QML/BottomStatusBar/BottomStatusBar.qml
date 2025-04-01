import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15

import "../Style"

ShadowedRectangle {
    id:statusBarWrapperRectID
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    height: fontMetricsID.height * 1.75
    mainBackgroundRectID.radius: 0
    //mainBackgroundRectID.color: fixedParamsID.ribbonsBackGoundColor
    mainBackgroundShaddowID.verticalOffset: 0
    mainBackgroundShaddowID.horizontalOffset:  0
    Row {
        id: statusBarRowLayoutID
        anchors.fill: parent
        anchors.leftMargin: height * 0.25
        spacing: height * 2
    }

    Connections{
        target: BPBoxManager
        function onShowStatusBarMessage(  msgText ,  msgDuration ,   msgColor ){
            var compVar = Qt.createComponent("qrc:/QML/BottomStatusBar/StatusBarMessageDelegate.qml");
            var objVar = compVar.createObject(statusBarRowLayoutID , {"text":msgText , "messageTimeOut": msgDuration , "color":msgColor});
        }
    }


    ResizeHandle{
        id:resizeHandelID
    }




    SpinBox {
        id: scaleSpinBpxID
        from: decimalToInt(0.001)   // Ensure 'from' is correctly scaled
        value: decimalToInt(1.0)
        to: decimalToInt(2.0)
        stepSize: decimalToInt(0.1)  // Ensure step size is correctly scaled
        editable: true
        anchors.verticalCenter: parent.verticalCenter
        anchors.right:  resizeHandelID.left
        scale: 0.75
        property int decimals: 2
        property real realValue: value / decimalFactor
        readonly property int decimalFactor: Math.pow(10, decimals)

        function decimalToInt(decimal) {
            return Math.round(decimal * decimalFactor) // Ensuring integer values
        }

        validator: DoubleValidator {
            bottom: Math.min(scaleSpinBpxID.from, scaleSpinBpxID.to)
            top:  Math.max(scaleSpinBpxID.from, scaleSpinBpxID.to)
            decimals: scaleSpinBpxID.decimals
            notation: DoubleValidator.StandardNotation
        }

        textFromValue: function(value, locale) {
            return Number(value / decimalFactor).toLocaleString(locale, 'f', scaleSpinBpxID.decimals)
        }

        valueFromText: function(text, locale) {
            return Math.round(Number.fromLocaleString(locale, text) * decimalFactor)
        }
        onValueChanged: {
            var newScale = scaleSpinBpxID.value / 100 ;
            if(newScale < 0.2)
                newScale = 0.2
            BPBoxManager.applicationScaleFactor = newScale ;
        }
        Connections{
            target: BPBoxManager
            function onApplicationScaleFactorChanged(){
                if( scaleSpinBpxID.value != scaleSpinBpxID.decimalToInt(BPBoxManager.applicationScaleFactor))
                    scaleSpinBpxID.value = scaleSpinBpxID.decimalToInt(BPBoxManager.applicationScaleFactor) ;
            }
        }

        Label{
            anchors.right:  parent.left
            anchors.verticalCenter: parent.verticalCenter
            text: "Scale: "
        }

        ToolTip{
            id: resetPosTipID
            text: "Reset Scale & Position"
            timeout: 3000
            visible: resetPosMouseID.containsMouse
        }

        Image {
            id: resetPosIconID
            source: BPBoxManager.darkThemeEnabled ? "qrc:/Images/resetPosWhite.png" : "qrc:/Images/resetPosDark.png"
            height: statusBarWrapperRectID.height
            width: height
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.right
            Rectangle{
                anchors.fill: parent
                color: resetPosMouseID.containsMouse ? ( BPBoxManager.darkThemeEnabled ? "#20ffffff" : "#20000000") : "transparent"
            }
            opacity: resetPosMouseID.containsMouse ? 1.0 : 0.5

            MouseArea{
                id: resetPosMouseID
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    scrollViewInappMainWindowID.flickableItem.contentY = 0 ;
                    scrollViewInappMainWindowID.flickableItem.contentX = 0 ;
                    BPBoxManager.applicationScaleFactor = 1.0 ;
                }
            }
        }

    }





}


