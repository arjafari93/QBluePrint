import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Dialogs
import Qt.labs.platform 1.0
import Qt5Compat.GraphicalEffects
import QtQuick.Templates 2.12 as TempQuick

Popup {
    id: applicationInfoPopUpID
    anchors.centerIn: parent
    width:  fontMetricsID.height * 50
    height:  fontMetricsID.height * 32
    modal: true
    clip: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    Component.onCompleted: {
        leftDrawerInappMainWindowID.close();
        applicationInfoPopUpID.open();
    }

    onClosed: {
        applicationInfoPopUpID.destroy();
    }

    enter: Transition {
        NumberAnimation { properties: "scale"; from: 0.2; to: 1; duration: 500 ; easing.type: Easing.OutBack; }
        NumberAnimation { properties: "opacity"; from: 0.1; to: 1; duration: 500 ;  }
    }

    background: Rectangle{
        radius: height * 0.075
        clip: true
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 1.0; color:  "#000000" }
            GradientStop { position: 0.3; color:  "#101010" }
            GradientStop { position: 0.0; color:  "#303030" }
        }
        border.color: "#90FFFFFF"
    }

    TempQuick.Overlay.modal:  Rectangle{
        color: "#E0000000"
    }

    Image {
        id: applicationIconImageID
        source: "qrc:/Images/AppICon.png"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: applicationNameTextID.height * 0.1
        width: Screen.width * 0.15
        height: width

        antialiasing: true
        mipmap: true
        smooth: true
    }

    ShaderEffect {
          id: shaderEffectOfCompanyName
          width: applicationIconImageID.width
          height: applicationIconImageID.height * 0.6

          anchors.horizontalCenter: applicationIconImageID.horizontalCenter
          anchors.top: applicationIconImageID.bottom
          anchors.topMargin: 0// -height * 0.1
          property real u_time: 0.0
          property real u_amplitute: 0.02
          Behavior on u_amplitute{
              NumberAnimation{duration: 1000}
          }

          UniformAnimator {
              target: shaderEffectOfCompanyName
              uniform: "u_time"
              from: 0
              to: 2*3.143
              duration: 1500
              running: true
              loops: Animation.Infinite
          }
          // the source where the effect shall be applied to
          property variant source: ShaderEffectSource{
              sourceItem: applicationIconImageID
              width: applicationIconImageID.width
              height: applicationIconImageID.height
          }

          fragmentShader: "qrc:/org/QBluePrint/GUI/shaders/wave.frag.qsb"
      }

    Column{
        id:columnOfTexts
        anchors.top: applicationIconImageID.top
        anchors.topMargin: applicationNameTextID.height * 0.5
        anchors.left: applicationIconImageID.right
        anchors.leftMargin: applicationNameTextID.height * 0.5
        spacing: fontMetricsID.font.pointSize
        Text {
            id: applicationNameTextID
            text: appMainWindowID.title
            color: "white"
            font.pointSize: fontMetricsID.font.pointSize + 12
            anchors.left: parent.left
        }

        Text {
            text: qsTr("Based on Qt 6.7")
            color: "white"
            font.pointSize: fontMetricsID.font.pointSize + 2
            anchors.left: parent.left
        }

        Text {
            text: qsTr("Release On Feb 2026")
            color: "white"
            font.pointSize: fontMetricsID.font.pointSize + 2
            anchors.left: parent.left
        }

        Text {
            text: "Source: github.com/arjafari93"
            color: "#489EE2"
            font.pointSize: fontMetricsID.font.pointSize + 2
            anchors.left: parent.left
            font.underline: true
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    cursorShape = Qt.PointingHandCursor
                }
                onClicked: {
                    Qt.openUrlExternally("https://github.com/arjafari93")
                }
            }
        }

        Text {
            text: "Demo Videos at my youtube channel "
            color: "#489EE2"
            font.pointSize: fontMetricsID.font.pointSize + 2
            anchors.left: parent.left
            font.underline: true
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    cursorShape = Qt.PointingHandCursor
                }
                onClicked: {
                    Qt.openUrlExternally("https://www.youtube.com/playlist?list=PLWlFycMes7_7DIiUJyj-BgJh1ARTclklZ")
                }
            }
        }
    }

    ShaderEffect {
          id: shaderEffectOfColumns
          width: columnOfTexts.width
          height: columnOfTexts.height * 0.6

          anchors.horizontalCenter: columnOfTexts.horizontalCenter
          anchors.top: shaderEffectOfCompanyName.top
          anchors.topMargin: fontMetricsID.height
          property real u_time: 0.0
          property real u_amplitute: 0.02
          Behavior on u_amplitute{
              NumberAnimation{duration: 1000}
          }

          UniformAnimator {
              target: shaderEffectOfColumns
              uniform: "u_time"
              from: 0
              to: 2*3.143
              duration: 1500
              running: true
              loops: Animation.Infinite
          }
          // the source where the effect shall be applied to
          property variant source: ShaderEffectSource{
              sourceItem: columnOfTexts
              width: columnOfTexts.width
              height: columnOfTexts.height
          }

          fragmentShader: "qrc:/org/QBluePrint/GUI/shaders/wave.frag.qsb"
      }

}
