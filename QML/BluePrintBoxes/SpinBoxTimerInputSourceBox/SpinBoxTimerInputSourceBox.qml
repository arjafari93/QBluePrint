import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import org.QBluePrint.Controls 1.0 as QbpC
import "../SingleTerminalInstance"
import "../SingleBoxInstance"

SingleBoxInstance{
    id:timerSpinBoxMainBoxID

    Column{
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: boxHeaderRectID.bottom
        anchors.topMargin: fontMetricsID.height * 2.5
        anchors.leftMargin: fontMetricsID.height * 0.75
        anchors.rightMargin: anchors.leftMargin * 2
        Item{
            anchors.left: parent.left
            anchors.right: parent.right
            height: fontMetricsID.height * 3
            Label{
                id: intervalLabelID
                text: "Interval(ms): "
                color: "white"
            }
            QbpC.SpinBox{
                id: intervalSpingBoxID
                Material.theme : Material.Dark
                anchors.verticalCenter: intervalLabelID.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin:  fontMetricsID.height * 6
                width: fontMetricsID.height * 13
                from:200
                to:100000
                value: sendValueInterval
                editable: true
                stepSize: 100
                onValueChanged: {
                    sendValueInterval = intervalSpingBoxID.value ;
                }
            }
        }

        Item{
            anchors.left: parent.left
            anchors.right: parent.right
            height: fontMetricsID.height * 3
            Label{
                id: valueToBeSentIntLabelID
                text: "Value(Int):"
                font.pointSize: fontMetricsID.font.pointSize
                color: "white"
            }

            QbpC.SpinBox{
                id: valueToBeSendSpinBox
                Material.theme : Material.Dark
                anchors.left: parent.left
                anchors.leftMargin: intervalSpingBoxID.anchors.leftMargin
                anchors.verticalCenter: valueToBeSentIntLabelID.verticalCenter
                width: intervalSpingBoxID.width
                value: parseInt(valueToBeSentInt)
                from: -100000000
                to:100000000
                editable: true
                onValueChanged: {
                    valueToBeSentInt = valueToBeSendSpinBox.value ;
                }
            }
        }

        Item{
            anchors.left: parent.left
            anchors.right: parent.right
            height: fontMetricsID.height * 3
            Label{
                id: valueToBeSentDoubleLabelID
                text: "Value(Double):"
                font.pointSize: fontMetricsID.font.pointSize
                color: "white"
            }
            QbpC.SpinBox {
                id: valueToBeSendDoubleSpinBox
                Material.theme : Material.Dark
                anchors.left: parent.left
                anchors.leftMargin: intervalSpingBoxID.anchors.leftMargin
                anchors.verticalCenter: valueToBeSentDoubleLabelID.verticalCenter
                width: intervalSpingBoxID.width
                from: -10000000
                value: decimalToInt(0)
                to: decimalToInt(10000000)
                stepSize: decimalFactor
                editable: true
                Component.onCompleted: {
                    value = decimalToInt(valueToBeSentDouble)
                }

                property int decimals: 2
                property real realValue: value / decimalFactor
                readonly property int decimalFactor: Math.pow(10, decimals)

                function decimalToInt(decimal) {
                    return decimal * decimalFactor
                }

                validator: DoubleValidator {
                    bottom: Math.min(valueToBeSendDoubleSpinBox.from, valueToBeSendDoubleSpinBox.to)
                    top:  Math.max(valueToBeSendDoubleSpinBox.from, valueToBeSendDoubleSpinBox.to)
                    decimals: valueToBeSendDoubleSpinBox.decimals
                    notation: DoubleValidator.StandardNotation
                }

                textFromValue: function(value, locale) {
                    return Number(value / decimalFactor).toLocaleString(locale, 'f', valueToBeSendDoubleSpinBox.decimals)
                }

                valueFromText: function(text, locale) {
                    return Math.round(Number.fromLocaleString(locale, text) * decimalFactor)
                }
                onValueChanged: {
                    valueToBeSentDouble = valueToBeSendDoubleSpinBox.value/decimalFactor ;
                }
            }
        }

        Item{
            anchors.left: parent.left
            anchors.right: parent.right
            height: fontMetricsID.height * 3
            Label{
                id: valueToBeSentStringLabelID
                text: "Value(String):"
                font.pointSize: fontMetricsID.font.pointSize
                color: "white"
            }

            ToolTip{
                id: textFieldHoverTipID
                text: valueToBeSendTextSpinBox.text
                visible: valueToBeSendTextSpinBox.hovered  && valueToBeSendTextSpinBox.text.length > 10
                timeout: 30000
            }

            TextField{
                id: valueToBeSendTextSpinBox
                anchors.left: parent.left
                anchors.leftMargin: intervalSpingBoxID.anchors.leftMargin
                anchors.verticalCenter: valueToBeSentStringLabelID.verticalCenter
                width: intervalSpingBoxID.width
                selectByMouse: true
                text: valueToBeSentString
                Material.theme: Material.Dark
                horizontalAlignment: TextInput.AlignHCenter
                onTextChanged: {
                    valueToBeSentString = valueToBeSendTextSpinBox.text
                }
            }
        }

        Item{
            anchors.left: parent.left
            anchors.right: parent.right
            height: fontMetricsID.height * 3
            Label{
                id: valueToBeSentBoolLabelID
                text: "Value(Bool):"
                font.pointSize: fontMetricsID.font.pointSize
                color: "white"
            }

            ComboBox{
                id:valueToBeSendBoolComboID
                anchors.left: parent.left
                width: intervalSpingBoxID.width
                anchors.leftMargin: intervalSpingBoxID.anchors.leftMargin
                anchors.verticalCenter: valueToBeSentBoolLabelID.verticalCenter
                model: [false, true]
                onCurrentIndexChanged: {
                    valueToBeSentBool = currentIndex
                }
            }
        }

        Item{
            anchors.left: parent.left
            anchors.right: parent.right
            height: fontMetricsID.height * 3
            Label{
                id: valueToBeSentArrayLabelID
                text: "Value(Array):"
                font.pointSize: fontMetricsID.font.pointSize
                color: "white"
            }

            Rectangle{
                width: intervalSpingBoxID.width
                height: valueToBeSentArrayLabelID.height * 2
                anchors.left: parent.left
                anchors.leftMargin: intervalSpingBoxID.anchors.leftMargin
                anchors.verticalCenter: valueToBeSentArrayLabelID.verticalCenter
                color: arrayMouseID.containsMouse ?  "#592f65" :  "#4F1C51"
                border.color: arrayMouseID.containsMouse ?  "#40ffffff" :  "transparent"
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
                                                                "currentListOfInfo" : getArrayValueData() ,
                                                                "depthOfPopup": 1 ,
                                                                "parentPopUp": modelData ,
                                                                "indexOfArrayObjInParentInfo": 0,
                                                                "timerSourceButtonAsParent": true
                                                            } );
                    }
                }
            }
        }
    }
}



