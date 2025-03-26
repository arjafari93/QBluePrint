import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQuick.Window 2.15
import "SingleBoxInstance"

import org.bluePrintType.BPStatic 1.0

Repeater{
    id:boxesMainRepeaterID
    anchors.fill: parent
    model: BPBoxManager.listOfBlueBoxes
    function defineGUIDeleage ( guiType ){
        switch(guiType){
        case CBPStatic.E_SimpleBluePrint :
            return "qrc:/QML/BluePrintBoxes/SingleBoxInstance/SingleBoxInstance.qml"
        case CBPStatic.E_OutputSinkWithString :
            return "qrc:/QML/BluePrintBoxes/SinkOutputString/SinkOutputString.qml"
        case CBPStatic.E_InputSpinBoxWithTimer :
            return "qrc:/QML/BluePrintBoxes/SpinBoxTimerInputSourceBox/SpinBoxTimerInputSourceBox.qml"
        case CBPStatic.E_BigTextOperator :
            return "qrc:/QML/BluePrintBoxes/OperatorWithBigText/OperatorWithBigText.qml"
        case CBPStatic.E_BigPictureOperator :
            return "qrc:/QML/BluePrintBoxes/BigPictureOperator/BigPictureOperator.qml"
        case CBPStatic.E_InputNetworkServer :
            return "qrc:/QML/BluePrintBoxes/NetworkBoxes/TCPServerInputBox.qml"
        case CBPStatic.E_TypeConvrtrOperator :
            return "qrc:/QML/BluePrintBoxes/TypeConvertorOperatorBox/TypeConvertorOperatorBox.qml"
        case CBPStatic.E_OutputSinkNetworkClient :
            return "qrc:/QML/BluePrintBoxes/NetworkBoxes/TCPClientOutputBox.qml"
        case CBPStatic.E_ChartBoxLineSeries:
            return "qrc:/QML/BluePrintBoxes/ChartBoxes/LineSeriesChartBox.qml"
        case CBPStatic.E_InputButtonSource:
            return "qrc:/QML/BluePrintBoxes/ButtonSourceBox/ButtonSourceBox.qml"
        }
        console.log("GUI Type Doesnt exist " ,guiType );
        return "qrc:/QML/BluePrintBoxes/BigPictureOperator/BigPictureOperator.qml"
    }
    delegate: Loader{
        source: boxesMainRepeaterID.defineGUIDeleage (blueBox_GUIType)
        asynchronous: true
    }

}
