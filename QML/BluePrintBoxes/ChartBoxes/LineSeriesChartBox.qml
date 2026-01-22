import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Qt5Compat.GraphicalEffects
import QtCharts 2.15

import "../SingleTerminalInstance"
import "../SingleBoxInstance"

import org.QBluePrint.Boxes 1.0

SingleBoxInstance{
    id:timerSpinBoxMainBoxID
    property CLineSeriesChartBox pMainBox : modelData
    property CLiveDataXYModel pChartModel : modelData.dataListModelInstace

    Label{
        id: countLableID
        text: "Count: " + mainLiveLineSeriesID.count
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: fontMetricsID.height * 3
        color: "white"
    }

    Label{
        id: latestValueLableID
        text: "Last Value: " + timerSpinBoxMainBoxID.pChartModel.lastLiveCapturedVal.toFixed(2)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: countLableID.bottom
        anchors.topMargin: fontMetricsID.height * 0.25
        color: "white"
    }

    ChartView {
        id: mainChartViewID
        anchors.fill: parent
        anchors.topMargin:  fontMetricsID.height * 6
        anchors.leftMargin:  fontMetricsID.height * 0.1
        anchors.rightMargin: anchors.leftMargin
        anchors.bottomMargin:  fontMetricsID.height *  0.1
        z:9

        height: parent.height //  Math.min( width * 0.6 ,  parent.height)
        theme: BPBoxManager.darkThemeEnabled ?  ChartView.ChartThemeDark : ChartView.ChartThemeLight

        Component.onCompleted:  {
            timerSpinBoxMainBoxID.pMainBox.setModelMapperLineSeries(mainLiveLineSeriesID )
        }

        antialiasing: true
        legend.visible: false

        ValueAxis {
            id: axisXOfChart
            labelsVisible: true
            gridVisible:false
            color: "transparent"
            max: timerSpinBoxMainBoxID.pChartModel ?
                      (timerSpinBoxMainBoxID.pChartModel.totalPointsCounter > timerSpinBoxMainBoxID.pChartModel.movingWindowLength ?
                         timerSpinBoxMainBoxID.pChartModel.totalPointsCounter : mainLiveLineSeriesID.count + 2)
            : 10
            min: timerSpinBoxMainBoxID.pChartModel ?
                     (timerSpinBoxMainBoxID.pChartModel.totalPointsCounter > timerSpinBoxMainBoxID.pChartModel.movingWindowLength ?
                      timerSpinBoxMainBoxID.pChartModel.totalPointsCounter - timerSpinBoxMainBoxID.pChartModel.movingWindowLength : 0)
                   : 0
        }

        ValueAxis {
            id: axisYOfChart
            labelsVisible: true
            gridVisible: true
            gridLineColor:  BPBoxManager.darkThemeEnabled ?  "#20ffffff" : "#20000000"
            //tickCount: 10
            max: timerSpinBoxMainBoxID.pChartModel ?
                     (timerSpinBoxMainBoxID.pChartModel.minValueLiveData ==  timerSpinBoxMainBoxID.pChartModel.maxValueLiveData ?
                         timerSpinBoxMainBoxID.pChartModel.lastLiveCapturedVal * 1.1 :
                          timerSpinBoxMainBoxID.pChartModel.maxValueLiveData ) : 10
            min: timerSpinBoxMainBoxID.pChartModel ?
                     (timerSpinBoxMainBoxID.pChartModel.minValueLiveData ==  timerSpinBoxMainBoxID.pChartModel.maxValueLiveData ?
                         timerSpinBoxMainBoxID.pChartModel.lastLiveCapturedVal * 0.9 :
                          timerSpinBoxMainBoxID.pChartModel.minValueLiveData ) : 0
        }

        LineSeries {
            id:mainLiveLineSeriesID
            name: "LineSeries"
            axisX: axisXOfChart
            axisY: axisYOfChart
        }

        MouseArea{
            anchors.fill: parent
            drag.target: dragTarget
            drag.axis: Drag.XAndYAxis
        }

        Item {
            // A virtual item to receive drag signals from the MouseArea.
            // When x or y properties are changed by the MouseArea's
            // drag signals, the ChartView is scrolled accordingly.
            id: dragTarget

            property real oldX : x
            property real oldY : y

            onXChanged: {
                mainChartViewID.scrollLeft( x - oldX );
                oldX = x;
            }
            onYChanged: { // we dont drag for y axis
                // mainChartViewID.scrollUp( y - oldY );
                // oldY = y;
            }
        }
    }

}

