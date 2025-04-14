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
    id: arrayModifyPupUpID
    property bool timerSourceButtonAsParent: false // whether this popup is coming from the edit button for the array in timer source
    required property var currentListOfInfo // this is a qvariantlist
    required property int depthOfPopup
    required property var parentPopUp
    required property int indexOfArrayObjInParentInfo
    function removeFromList(targetIndex){
        if (targetIndex >= 0 && targetIndex < currentListOfInfo.length) {
            currentListOfInfo.splice(targetIndex, 1);
        } else {
            console.warn("Invalid index:", targetIndex);
        }
        currentListOfInfo = currentListOfInfo; // Triggers change
    }

    function addNewElementToList( newValue ){
        currentListOfInfo.push(newValue)
        currentListOfInfo = currentListOfInfo; // Triggers change
        Qt.callLater(function() {
            let lastIndex = currentListOfInfo.length - 1 ;
            if(lastIndex >= 0  )
                listOfHeaderkeyValuesID.currentIndex = lastIndex;
        });
    }


    function saveChildInfoOnChildClose(childInfo , dataIndexInParent){ // called by child popup
        if( dataIndexInParent >= currentListOfInfo.length ||  dataIndexInParent < 0  ){
            console.log(" index out of range in saveChildInfoOnChildClose" , dataIndexInParent ,arrayModifyPupUpID.currentListOfInfo.length );
            return ;
        }
        currentListOfInfo[dataIndexInParent] = childInfo ;
        currentListOfInfo = currentListOfInfo; // Triggers change

    }


    anchors.centerIn: parent
    width: fontMetricsID.height * 45
    height: fontMetricsID.height * 30
    modal: true
    clip: true
    Material.accent:   Material.Purple

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    Component.onCompleted: {
        leftDrawerInappMainWindowID.close();
        //var dataType = cBPStatic.getNameOfTypeAsString(pTerminalInstance);
        if(Array.isArray(currentListOfInfo) == false )
            currentListOfInfo = [];
        arrayModifyPupUpID.open()
    }

    onClosed: {
        if(arrayModifyPupUpID.timerSourceButtonAsParent == false )
            arrayModifyPupUpID.parentPopUp.saveChildInfoOnChildClose( currentListOfInfo , indexOfArrayObjInParentInfo );
        else{
            // this popup is coming from timer source edit button for the array
            arrayModifyPupUpID.parentPopUp.changeArrayValueData( currentListOfInfo  );
        }

        arrayModifyPupUpID.destroy();
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
        id: keyLabelID
        text: "Array Data ( page " + depthOfPopup + " )"
        anchors.top:  parent.top
        anchors.topMargin:  fontMetricsID.height * 2.5
        anchors.horizontalCenter:  parent.horizontalCenter
        font.pointSize: fontMetricsID.font.pointSize + 2
    }

    function findDatTypeAsString(dataVal){
        let dataType = typeof dataVal ;
        switch (dataType) {
        case "text": return "string";
        case "number":{
            if (Number.isInteger(dataVal)) {
                return "int"; // Differentiating integers and floating points
            } else {
                return "double";
            }
        }
        case "boolean": return "bool";
        case "float": return "double";
        case "string": return "string";
        case "object": {
            if (Array.isArray(dataVal)) {
                return "array" ;
            } else  {
                console.log(" unknown type detected: unknow object type not array" , dataVal );
                return "unknown";
            }
        }
        default: {
            console.log(" unknown type detected in findDatTypeAsString:" , dataVal , dataType );
            return "unknown";
        }
        }
    }

    function findDelegateForData(dataVal){
        let dataType = findDatTypeAsString( dataVal); // Get the type
        switch (dataType) {
        case "string": return stringComponent;
        case "int": return intComponent;
        case "double": return doubleComponent;
        case "bool": return boolComponent;
        case "array": return arrayComponent ;
        default: {
            console.log(" unknown type detected:" , dataType );
            return null;
        }
        }
    }



    ListView{
        id:listOfHeaderkeyValuesID
        property int compHeight: fontMetricsID.height * 4
        property int compWidth: listOfHeaderkeyValuesID.width * 0.9
        property int leftEditorWidth: listOfHeaderkeyValuesID.width * 0.4
        anchors.top:keyLabelID.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: addNewRowBtnID.top
        anchors.margins: fontMetricsID.height * 2
        anchors.topMargin: fontMetricsID.height * 1.5
        clip: true
        model: currentListOfInfo
        spacing: fontMetricsID.height * 0.25
        ScrollBar.vertical: ScrollBar {
            id:scrollBarOfListViewID
            anchors.right: parent.right
            policy: ScrollBar.AsNeeded
            width: fontMetricsID.height
        }
        delegate: Loader{
            id: dlgtLoaderID
            property var loaderModelData: modelData // this is a qvariant and can be qvariantlist
            property var loaderModelIndex: index
            sourceComponent: findDelegateForData (modelData)
            asynchronous: true
        }
        Rectangle{
            anchors.fill: parent
            color: BPBoxManager.darkThemeEnabled ?  "#20000000" : "#20ffffff"
            border.color: BPBoxManager.darkThemeEnabled ? "#10ffffff" : "#20000000"
        }
    }


    Rectangle{
        id: addNewRowBtnID
        z:100
        anchors.bottom:  parent.bottom
        anchors.bottomMargin:  fontMetricsID.height * 2
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.5
        height: fontMetricsID.height * 3
        radius: height * 0.2
        property color btnColorVal: btnMouseID.containsPress ?  "#309030" :  "#307030"
        border.color: btnMouseID.containsMouse ? "#80ffffff" : "transparent"
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0.0; color:   addNewRowBtnID.btnColorVal }
            GradientStop { position: 0.5; color: appMainWindowID.applyOpacityToColor(addNewRowBtnID.btnColorVal , 0.4) }
            GradientStop { position: 1.0; color: addNewRowBtnID.btnColorVal }
        }
        MouseArea{
            id: btnMouseID
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                var tempComp = Qt.createComponent("qrc:/QML/BluePrintBoxes/SingleTerminalInstance/AddNewArrayElementPopup.qml");
                var tempObj = tempComp.createObject(appMainWindowID , {"parentPopUp": arrayModifyPupUpID , "depthOfPopup": depthOfPopup+1} );
            }
        }

        Label{
            anchors.centerIn: parent
            color: "white"
            text: "Add New Data"
        }
        Rectangle{
            anchors.fill: parent
            color: "black"
            z:-1
            radius: addNewRowBtnID.radius
        }
    }


    // Components
    Component {
        id: intComponent
        Item {
            id: rootItemID
            width:  listOfHeaderkeyValuesID.compWidth
            height: listOfHeaderkeyValuesID.compHeight
            x: (  listOfHeaderkeyValuesID.width - listOfHeaderkeyValuesID.compWidth ) * 0.5
            Label{
                id: indexLableID
                text: rootItemID.parent.loaderModelIndex + ":"
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
            }
            Label{
                id: dataTypeLabelID
                text: "(int)"
                anchors.left: indexLableID.right
                anchors.leftMargin: fontMetricsID.height
                anchors.verticalCenter: parent.verticalCenter
            }
            SpinBox{
                width: listOfHeaderkeyValuesID.leftEditorWidth
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                from: -99999999
                to: 99999999
                value: rootItemID.parent.loaderModelData
                editable: true
                onValueChanged: {
                    arrayModifyPupUpID.currentListOfInfo[rootItemID.parent.loaderModelIndex] = value ;
                }
            }
            Rectangle{
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                color: Material.accent
            }
            Rectangle{
                id: removeRectID
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                height: fontMetricsID.height * 2
                width: height
                color: removeMosueID.containsMouse ? "#E02020"  : "#902020"
                radius: height * 0.1
                Label{
                    text: "X"
                    font.pointSize: fontMetricsID.font.pointSize + 4
                    color: "white"
                    anchors.centerIn: parent
                }
                MouseArea{
                    id: removeMosueID
                    z:100
                    cursorShape: Qt.PointingHandCursor
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        removeFromList(rootItemID.parent.loaderModelIndex)
                    }
                }
            }
        }
    }

    Component {
        id: doubleComponent
        Item {
            id: rootItemID
            width:  listOfHeaderkeyValuesID.compWidth
            height: listOfHeaderkeyValuesID.compHeight
            x: (  listOfHeaderkeyValuesID.width - listOfHeaderkeyValuesID.compWidth ) * 0.5
            Rectangle{
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                color: Material.accent
            }
            Rectangle{
                id: removeRectID
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                height: fontMetricsID.height * 2
                width: height
                color: removeMosueID.containsMouse ? "#E02020"  : "#902020"
                radius: height * 0.1
                Label{
                    text: "X"
                    font.pointSize: fontMetricsID.font.pointSize + 4
                    color: "white"
                    anchors.centerIn: parent
                }
                MouseArea{
                    id: removeMosueID
                    z:100
                    cursorShape: Qt.PointingHandCursor
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        removeFromList(rootItemID.parent.loaderModelIndex)
                    }
                }
            }
            Label{
                id: indexLableID
                text: rootItemID.parent.loaderModelIndex + ":"
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
            }
            Label{
                id: dataTypeLabelID
                text: "(double)"
                anchors.left: indexLableID.right
                anchors.leftMargin: fontMetricsID.height
                anchors.verticalCenter: parent.verticalCenter
            }
            SpinBox {
                id: doubleSpinBoxID
                width: listOfHeaderkeyValuesID.leftEditorWidth
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                from: -10000000
                value: decimalToInt(rootItemID.parent.loaderModelData)
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
                    arrayModifyPupUpID.currentListOfInfo[rootItemID.parent.loaderModelIndex] =  doubleSpinBoxID.value/ parseFloat( decimalFactor) ;
                }
            }
        }
    }

    Component {
        id: boolComponent
        Item {
            id: rootItemID
            width:  listOfHeaderkeyValuesID.compWidth
            height: listOfHeaderkeyValuesID.compHeight
            x: (  listOfHeaderkeyValuesID.width - listOfHeaderkeyValuesID.compWidth ) * 0.5
            Label{
                id: indexLableID
                text: rootItemID.parent.loaderModelIndex + ":"
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
            }
            Label{
                id: dataTypeLabelID
                text: "(bool)"
                anchors.left: indexLableID.right
                anchors.leftMargin: fontMetricsID.height
                anchors.verticalCenter: parent.verticalCenter
            }
            Rectangle{
                id: removeRectID
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                height: fontMetricsID.height * 2
                width: height
                color: removeMosueID.containsMouse ? "#E02020"  : "#902020"
                radius: height * 0.1
                Label{
                    text: "X"
                    font.pointSize: fontMetricsID.font.pointSize + 4
                    color: "white"
                    anchors.centerIn: parent
                }
                MouseArea{
                    id: removeMosueID
                    z:100
                    cursorShape: Qt.PointingHandCursor
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        removeFromList(rootItemID.parent.loaderModelIndex)
                    }
                }
            }
            Rectangle{
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                color: Material.accent
            }
            ComboBox {
                width: listOfHeaderkeyValuesID.leftEditorWidth
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                model: [ "false" ,"true" ]
                currentIndex: rootItemID.parent.loaderModelData
                onCurrentIndexChanged: {
                    arrayModifyPupUpID.currentListOfInfo[rootItemID.parent.loaderModelIndex] = (currentIndex ? true : false );
                }
            }
        }
    }

    Component {
        id: stringComponent
        Item {
            id: rootItemID
            width:  listOfHeaderkeyValuesID.compWidth
            height: listOfHeaderkeyValuesID.compHeight
            x: (  listOfHeaderkeyValuesID.width - listOfHeaderkeyValuesID.compWidth ) * 0.5
            Label{
                id: indexLableID
                text: rootItemID.parent.loaderModelIndex + ":"
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
            }
            Label{
                id: dataTypeLabelID
                text: "(string)"
                anchors.left: indexLableID.right
                anchors.leftMargin: fontMetricsID.height
                anchors.verticalCenter: parent.verticalCenter
            }
            Rectangle{
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                color: Material.accent
            }
            Rectangle{
                id: removeRectID
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                height: fontMetricsID.height * 2
                width: height
                color: removeMosueID.containsMouse ? "#E02020"  : "#902020"
                radius: height * 0.1
                Label{
                    text: "X"
                    font.pointSize: fontMetricsID.font.pointSize + 4
                    color: "white"
                    anchors.centerIn: parent
                }
                MouseArea{
                    id: removeMosueID
                    z:100
                    cursorShape: Qt.PointingHandCursor
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        removeFromList(rootItemID.parent.loaderModelIndex)
                    }
                }
            }
            TextField {
                id: textFieldID
                width: listOfHeaderkeyValuesID.leftEditorWidth
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                ToolTip{
                    id: textFieldHoverTipID2
                    text: textFieldID.text
                    visible: textFieldID.hovered && textFieldID.text.length > 10
                    timeout: 30000
                }
                placeholderText: "Enter text"
                selectByMouse: true
                text: rootItemID.parent.loaderModelData
                onTextChanged: {
                    arrayModifyPupUpID.currentListOfInfo[rootItemID.parent.loaderModelIndex] = text;
                }
            }
        }
    }

    Component {
        id: arrayComponent
        Item {
            id: rootItemID
            width:  listOfHeaderkeyValuesID.compWidth
            height: listOfHeaderkeyValuesID.compHeight
            x: (  listOfHeaderkeyValuesID.width - listOfHeaderkeyValuesID.compWidth ) * 0.5
            Label{
                id: indexLableID
                text: rootItemID.parent.loaderModelIndex + ":"
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
            }
            Label{
                id: dataTypeLabelID
                text: "(array)"
                anchors.left: indexLableID.right
                anchors.leftMargin: fontMetricsID.height
                anchors.verticalCenter: parent.verticalCenter
            }
            Rectangle{
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                color: Material.accent
            }
            Rectangle{
                id: removeRectID
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                height: fontMetricsID.height * 2
                width: height
                color: removeMosueID.containsMouse ? "#E02020"  : "#902020"
                radius: height * 0.1
                Label{
                    text: "X"
                    font.pointSize: fontMetricsID.font.pointSize + 4
                    color: "white"
                    anchors.centerIn: parent
                }
                MouseArea{
                    id: removeMosueID
                    z:100
                    cursorShape: Qt.PointingHandCursor
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        removeFromList(rootItemID.parent.loaderModelIndex)
                    }
                }
            }
            Rectangle{
                width: listOfHeaderkeyValuesID.leftEditorWidth
                height: fontMetricsID.height * 2.5
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                color: arrayMouseID.containsMouse ?  "#592f65" :  "#4F1C51"
                border.color: arrayMouseID.containsMouse ?  "#40ffffff" :  "transparent"
                Label{
                    id: editLabelID
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
                        var tempObj = tempComp.createObject(appMainWindowID , {
                                                                "currentListOfInfo" : rootItemID.parent.loaderModelData,
                                                                "depthOfPopup": depthOfPopup+1,
                                                                "parentPopUp": arrayModifyPupUpID,
                                                                "indexOfArrayObjInParentInfo" : rootItemID.parent.loaderModelIndex
                                                            } );
                    }
                }
            }
        }
    }


}
