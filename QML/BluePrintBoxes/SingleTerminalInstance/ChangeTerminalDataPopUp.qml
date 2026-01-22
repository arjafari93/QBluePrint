import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Dialogs
import Qt.labs.platform 1.0
import Qt5Compat.GraphicalEffects
import QtQuick.Controls.Material 2.15
import QtQuick.Templates 2.12 as TempQuick

import org.QBluePrint.Boxes 1.0

import "../../Style"

Popup {
    id: terminalModifyPupUpCompID
    required property CIOTerminal pTerminalInstance

    anchors.centerIn: parent
    width: fontMetricsID.height * 40
    height: fontMetricsID.height * 20
    modal: true
    clip: true
    Material.accent:   Material.Purple

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    Component.onCompleted: {
        leftDrawerInappMainWindowID.close();
        var dataType = cBPStatic.getNameOfTypeAsString(pTerminalInstance);
        terminalModifyPupUpCompID.open()
    }

    onClosed: {
        terminalModifyPupUpCompID.destroy();
    }

    TempQuick.Overlay.modal:  Rectangle{
        color: "#E0000000"
    }

    enter: Transition {
        NumberAnimation { properties: "scale"; from: 0.5; to: 1; duration: 500 ; easing.type: Easing.OutBack; }
        NumberAnimation { properties: "opacity"; from: 0.1; to: 1; duration: 500 ;  }
    }

    background: Item{
        ShadowedRectangle{
            anchors.fill: parent
            anchors.margins: fontMetricsID.height * 2
        }
    }

    function saveChildInfoOnChildClose(childInfo , dataIndexInParent){ // called by child popup in array modify popup
        // here dataIndexInParent desont matter, but we keep it to comply the saveChildInfoOnChildClose syntax in other popups
        pTerminalInstance.changeTerminalCurrentDataArray(childInfo);
    }

    Label{
        id: dataTypeLableID
        text: "Data Type: "
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin:  fontMetricsID.height * 4
        anchors.topMargin:   fontMetricsID.height * 6
    }

    ComboBox{
        id: targetTypeComboID
        model: cBPStatic.getListOfSupportedTypes()
        currentIndex: -1
        anchors.left: parent.left
        anchors.leftMargin: fontMetricsID.height * 12
        width: parent.width * 0.35
        anchors.verticalCenter: dataTypeLableID.verticalCenter
        //onCurrentIndexChanged: selectedOutputType = cBPStatic.getListOfSupportedTypes()[currentIndex]
        Component.onCompleted: {
            var currentDataType = cBPStatic.getNameOfTypeAsString(pTerminalInstance);
            for(var iter=0 ; iter < cBPStatic.getListOfSupportedTypes().length ; iter++){
                if(cBPStatic.getListOfSupportedTypes()[iter] == currentDataType ){
                    targetTypeComboID.currentIndex = iter ;
                    return ;
                }
            }
        }
    }

    Label{
        id: dataValueLableID
        text: "Value: "
        anchors.left: dataTypeLableID.left
        anchors.top: dataTypeLableID.bottom
        anchors.topMargin: fontMetricsID.height * 2.5
    }

    Loader {
        id: dynamicTypeEditorID
        anchors.left: targetTypeComboID.left
        anchors.right: targetTypeComboID.right
        anchors.verticalCenter: dataValueLableID.verticalCenter
        sourceComponent: {
            switch (targetTypeComboID.currentIndex) {
            case 0: return intComponent;
            case 1: return doubleComponent;
            case 2: return boolComponent;
            case 3: return stringComponent;
            case 4: return arrayComponent;
            default: return undefined;
            }
        }
    }

    // Components
    Component {
        id: intComponent
        SpinBox {
            from: -99999999
            to: 99999999
            value:  pTerminalInstance.getTerminalCurrentData() != undefined ? pTerminalInstance.getTerminalCurrentData() : 0
            onValueChanged: {
                pTerminalInstance.changeTerminalCurrentData(value);
            }
            Component.onCompleted: {
                pTerminalInstance.changeTerminalCurrentData(value);
            }
            editable: true
        }
    }

    Component {
        id: doubleComponent
        SpinBox {
            id: doubleSpinBoxID
            //Material.theme : Material.Dark
            from: -10000000
            value: decimalToInt(pTerminalInstance.getTerminalCurrentData() != undefined ? pTerminalInstance.getTerminalCurrentData() : 0)
            to: decimalToInt(10000000)
            stepSize: decimalFactor
            editable: true
            // e.g.:  value 110 decimalFactor 100 realValue 1.10
            property int decimals: 2
            property real realValue: value / decimalFactor
            readonly property int decimalFactor: Math.pow(10, decimals)  // 100

            function decimalToInt(decimalVal) {
                return decimalVal * decimalFactor
            }

            validator: DoubleValidator {
                bottom: Math.min(doubleSpinBoxID.from, doubleSpinBoxID.to)
                top:  Math.max(doubleSpinBoxID.from, doubleSpinBoxID.to)
                decimals: doubleSpinBoxID.decimals
                notation: DoubleValidator.StandardNotation
            }

            textFromValue: function(value, locale) { // vaalue is  e.g.: 110
                return Number(value / decimalFactor).toLocaleString(locale, 'f', doubleSpinBoxID.decimals);
            }

            valueFromText: function(text, locale) { //text is e.g.: 1.10
                return Math.round(Number.fromLocaleString(locale, text) * decimalFactor);
            }
            onValueChanged: {
                pTerminalInstance.changeTerminalCurrentData(  doubleSpinBoxID.value/ parseFloat( decimalFactor) );
            }
            Component.onCompleted: {
                pTerminalInstance.changeTerminalCurrentData(  doubleSpinBoxID.value/ parseFloat( decimalFactor) );
            }
        }
    }

    Component {
        id: boolComponent
        ComboBox {
            model: [ "false" ,"true" ]
            currentIndex: pTerminalInstance.getTerminalCurrentData() != undefined ? pTerminalInstance.getTerminalCurrentData() : 0
            onCurrentIndexChanged:  {
                pTerminalInstance.changeTerminalCurrentData( (currentIndex ? true : false) )
            }
            Component.onCompleted: {
                pTerminalInstance.changeTerminalCurrentData( (currentIndex ? true : false) )
            }
        }
    }

    Component {
        id: stringComponent
        TextField {
            id: textFieldID
            ToolTip{
                id: textFieldHoverTipID2
                text: textFieldID.text
                visible: textFieldID.hovered && textFieldID.text.length > 10
                timeout: 30000
            }
            placeholderText: "Enter text"
            selectByMouse: true
            text: pTerminalInstance.getTerminalCurrentData() != undefined ? pTerminalInstance.getTerminalCurrentData() : ""
            onTextChanged:  {
                pTerminalInstance.changeTerminalCurrentData( text )
            }
            Component.onCompleted: {
                pTerminalInstance.changeTerminalCurrentData( text )
            }
        }
    }

    Component {
        id: arrayComponent
        Rectangle{
            width: targetTypeComboID.width
            height: targetTypeComboID.height * 0.75
            anchors.centerIn: parent
            color: arrayMouseID.containsMouse ?  "#592f65" :  "#4F1C51"
            border.color: arrayMouseID.containsMouse ?  "#40ffffff" :  "transparent"
            function isArrayLike(v) {
                if (v === null || v === undefined) return false;
                if (Array.isArray(v)) return true;                 // real JS array

                // Qt 6 sequences: not JS arrays, but have numeric length + index access
                if (typeof v === "object" &&
                    typeof v.length === "number" &&
                    Number.isFinite(v.length) &&
                    v.length >= 0 &&
                    Math.floor(v.length) === v.length) {
                    return true;
                }
                return false;
            }

            Component.onCompleted: {
                if( isArrayLike(pTerminalInstance.getTerminalCurrentData()) == false)
                    pTerminalInstance.changeTerminalCurrentDataArray( [] )
            }
            Label{
                anchors.centerIn: parent
                text: "Edit"
                color: "white"
            }
            MouseArea{
                id: arrayMouseID
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    var tempComp = Qt.createComponent("qrc:/QML/BluePrintBoxes/SingleTerminalInstance/ArrayValueModifierPopUp.qml");
                    var tempObj = tempComp.createObject(appMainWindowID ,  {
                                                            "currentListOfInfo" : pTerminalInstance.getTerminalCurrentData() ,
                                                            "depthOfPopup": 1 ,
                                                            "parentPopUp": terminalModifyPupUpCompID ,
                                                            "indexOfArrayObjInParentInfo": 0
                                                        } );
                }
            }
        }
    }

}
