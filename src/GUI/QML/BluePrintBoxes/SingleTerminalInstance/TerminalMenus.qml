import QtQuick 2.15
import QtQuick.Controls 2.15

MenuItem { // modelData here is the Terminal
    id: menueItemID
    property int indexOfMenuItem: 0
    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        propagateComposedEvents: true
        onEntered: {
            modelData.highlightLineFlowAtIndex(indexOfMenuItem   , true);
        }
        onExited: {
            modelData.highlightLineFlowAtIndex(indexOfMenuItem  , false );
        }
        onClicked: {
            modelData.removeLineFlowAtIndex(indexOfMenuItem);
            terminalConnectedLinesMenusID.close()
        }
    }
}
