import QtQuick 2.15
import "SingleLineFlowInstance"
Repeater{
    id:repeaterID
    anchors.fill: parent
    delegate: SingleLineFlowInstance{

    }
}
