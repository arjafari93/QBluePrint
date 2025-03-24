import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import "../SingleTerminalInstance"
import "../SingleBoxInstance"

import org.bluePrintType.SocketClientSink 1.0
import org.bluePrintType.AbstractSocket 1.0


SingleBoxInstance{
    id:timerSpinBoxMainBoxID
    property CSocketClientSink pSocketInstance : modelData

    Item{
        id: portNumberWrprID
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: fontMetricsID.height * 5
        height: fontMetricsID.height * 3
        Label{
            id: valueToBeSentIntLabelID
            text: "Port:"
            font.pointSize: fontMetricsID.font.pointSize
            color: "white"
            anchors.left: parent.left
            anchors.leftMargin:  fontMetricsID.height
        }

        SpinBox{
            id: valueToBeSendSpinBox
             Material.theme : Material.Dark
            anchors.left: valueToBeSentIntLabelID.right
            anchors.leftMargin: valueToBeSentIntLabelID.anchors.leftMargin
            anchors.verticalCenter: valueToBeSentIntLabelID.verticalCenter
            width: parent.width * 0.65
            value: pSocketInstance.remotePortNum
            from: 1
            to: 65535
            editable: true
            onValueChanged: {
                pSocketInstance.remotePortNum = valueToBeSendSpinBox.value ;
            }
        }
    }



    Item{
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: portNumberWrprID.bottom
        anchors.topMargin: fontMetricsID.height * 0.5
        height: fontMetricsID.height * 3
        Label{
            id: remoteServerIPLableID
            text: "IP:"
            font.pointSize: fontMetricsID.font.pointSize
            color: "white"
            anchors.left: parent.left
            anchors.leftMargin:  fontMetricsID.height
        }

        TextField{
            id: remoteServerIPTextID
            anchors.left: remoteServerIPLableID.right
            anchors.leftMargin: valueToBeSendSpinBox.anchors.leftMargin
            anchors.verticalCenter: remoteServerIPLableID.verticalCenter
            width: valueToBeSendSpinBox.width
            text: pSocketInstance.remoteServerIPAddress
            Material.theme: Material.Dark
            horizontalAlignment: TextInput.AlignHCenter
            onTextChanged: {
                pSocketInstance.remoteServerIPAddress = remoteServerIPTextID.text
            }
        }
    }


    Rectangle{
        id: connectBtnRectID
        visible: pSocketInstance.socketType == QAbstractSocket.TcpSocket
        function findColorByState( tcpState ){
            if(tcpState === QAbstractSocket.ConnectedState )
                return "#5B913B"
            if(tcpState === QAbstractSocket.UnconnectedState )
                return "#A31D1D"
            if(tcpState === QAbstractSocket.ConnectingState )
                return "#577BC1"
            return "#808080"
        }
        property color btnColorVal: findColorByState( pSocketInstance.clientSocketState )
        Behavior on btnColorVal {
            ColorAnimation{}
        }

        anchors.bottom:  parent.bottom
        anchors.bottomMargin:  fontMetricsID.height
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.8
        height: fontMetricsID.height * 3
        radius: height * 0.2
        border.color: connectionBtnMouseID.containsMouse ? "#80ffffff" : "transparent"
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0.0; color:   connectBtnRectID.btnColorVal }
            GradientStop { position: 0.5; color: appMainWindowID.applyOpacityToColor(connectBtnRectID.btnColorVal , 0.4) }
            GradientStop { position: 1.0; color: connectBtnRectID.btnColorVal }
        }
        MouseArea{
            id: connectionBtnMouseID
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                pSocketInstance.clientConnectionBtnClicked();
            }
        }

        Label{
            function findStateText( tcpState ){
                if(tcpState === QAbstractSocket.UnconnectedState )
                    return "UnconnectedState"
                if(tcpState === QAbstractSocket.HostLookupState )
                    return "HostLookupState"
                if(tcpState === QAbstractSocket.ConnectingState )
                    return "ConnectingState"
                if(tcpState === QAbstractSocket.ConnectedState )
                    return "ConnectedState"
                if(tcpState === QAbstractSocket.BoundState )
                    return "BoundState"
                if(tcpState === QAbstractSocket.ListeningState )
                    return "ListeningState"
                if(tcpState === QAbstractSocket.ClosingState )
                    return "ClosingState"
                return "unkown state"
            }
            anchors.centerIn: parent
            color: "white"
            text: findStateText( pSocketInstance.clientSocketState )
        }
    }





}





