import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.0
import QtGraphicalEffects 1.15
import QtQuick.Controls.Material 2.15
import QtQuick.Templates 2.12 as TempQuick


import "../../Style"

Popup {
    id: addNewArrayElmntPopupID
    property var newVarToBeAdded: 0
    required property var parentPopUP
    anchors.centerIn: parent
    width: fontMetricsID.height * 40
    height: fontMetricsID.height * 20
    modal: true
    clip: true
    Material.accent:   Material.Purple

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    Component.onCompleted: {
        leftDrawerInappMainWindowID.close();
        addNewArrayElmntPopupID.open()
    }

    onClosed: {
        addNewArrayElmntPopupID.parentPopUP.addNewElementToList(addNewArrayElmntPopupID.newVarToBeAdded)
        addNewArrayElmntPopupID.destroy();
    }


    TempQuick.Overlay.modal:  Rectangle{
        color: "#90000000"
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
        currentIndex: 0
        anchors.left: parent.left
        anchors.leftMargin: fontMetricsID.height * 12
        width: parent.width * 0.35
        anchors.verticalCenter: dataTypeLableID.verticalCenter

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
            value: 0
            onValueChanged: {
                addNewArrayElmntPopupID.newVarToBeAdded = value ;
            }
            Component.onCompleted: {
                addNewArrayElmntPopupID.newVarToBeAdded = value ;
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
            value: decimalToInt(0)
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
                addNewArrayElmntPopupID.newVarToBeAdded =   doubleSpinBoxID.value/ parseFloat( decimalFactor) ;
            }
            Component.onCompleted: {
                addNewArrayElmntPopupID.newVarToBeAdded =  doubleSpinBoxID.value/ parseFloat( decimalFactor) ;
            }
        }
    }

    Component {
        id: boolComponent
        ComboBox {
            model: [ "false" ,"true" ]
            currentIndex:  0
            onCurrentIndexChanged:  {
                addNewArrayElmntPopupID.newVarToBeAdded = (currentIndex ? true : false) ;
            }
            Component.onCompleted: {
                addNewArrayElmntPopupID.newVarToBeAdded = (currentIndex ? true : false) ;
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
            text:  ""
            onTextChanged:  {
                addNewArrayElmntPopupID.newVarToBeAdded = text ;
            }
            Component.onCompleted: {
                addNewArrayElmntPopupID.newVarToBeAdded = text ;
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
            enabled: false
            Label{
                anchors.centerIn: parent
                text: "Array ( Edit In page " + addNewArrayElmntPopupID.parentPopUP.depthOfPopup + " )"
                color: "white"
            }
            MouseArea{
                id: arrayMouseID
                enabled: false
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
            }
            Component.onCompleted: {
                addNewArrayElmntPopupID.newVarToBeAdded = [] ;
            }
        }
    }


}
