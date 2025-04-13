#include "LineSeriesChartBox.h"


#include <QAbstractTableModel>
#include <QVXYModelMapper>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QJsonObject>


#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "LiveDataXYModel.h"
#include "../../CRawValueBase/RawValueBase.h"


CLineSeriesChartBox::CLineSeriesChartBox ( int newBlueBox_xPos, int newBlueBox_yPos , QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth + 280 , blueBoxHeight + 230 , parent } ,
      mp_modelXYMapperLiveData {nullptr}, mp_dataListModelInstace {nullptr}
{
    m_blueBox_settingQMLPath = "qrc:/QML/BluePrintBoxes/ChartBoxes/ChartBoxSettings.qml";
    mp_dataListModelInstace = std::make_unique<CLiveDataXYModel>();
    mp_modelXYMapperLiveData = std::make_unique<QtCharts::QVXYModelMapper>();
    mp_modelXYMapperLiveData->setModel(mp_dataListModelInstace.get());
    mp_modelXYMapperLiveData->setXColumn(0);
    mp_modelXYMapperLiveData->setYColumn(1);

    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_ChartBoxLineSeries ;
    m_blueBox_HeadColor = QColor(100, 100, 250);
    m_blueBox_HeaderIcon = "qrc:/Images/chartIcon.png";
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Input");
    auto inputNode2 = new CInputTerminal(1, this);
    inputNode2->setTerminalName("Reset");
    m_listOfInputTerminals.push_back(inputNode1 );
    m_listOfInputTerminals.push_back(inputNode2 );

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("Count");
    m_listOfOutputTerminals.push_back( outPutNode );

    m_blueBox_keyWords = "LineSeries Chart line graph series output sink ";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_OutPutSink ;
}

CLineSeriesChartBox::~CLineSeriesChartBox()
{

}





void CLineSeriesChartBox::evaluateOperation()
{
    auto pResetStatus = m_listOfInputTerminals.at(1)->terminalCurrentData().get() ;
    bool resetChart = false ;
    if (auto* pVal = dynamic_cast<CValue_int*>(pResetStatus)) {
        resetChart = pVal->value() ;
    } else if (auto* pVal = dynamic_cast<CValue_double*>(pResetStatus)) {
        resetChart = pVal->value() ;
    }else if (auto* pVal = dynamic_cast<CValue_bool*>(pResetStatus)) {
        resetChart = pVal->value() ;
    }else if (auto* pVal = dynamic_cast<CValue_string*>(pResetStatus)) {
        resetChart = pVal->value().toLongLong();
    }

    if(resetChart == true ){
        mp_dataListModelInstace->resetRequestReceived();
        m_listOfInputTerminals.at(1)->setTerminalCurrentData( std::make_shared<CValue_bool>(false ) );
        return ;
    }

    auto pCurrentData = m_listOfInputTerminals.at(0)->terminalCurrentData().get() ;
    float result = 0 ;
    if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentData)) {
        result = pVal->value() ;
    } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentData)) {
        result = pVal->value() ;
    }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentData)) {
        result = pVal->value() ;
    }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentData)) {
        result = pVal->value().toDouble();
    }else{
        DEBUG_MSG_PRINT << " invalid data type " ;
        return ;
    }

    mp_dataListModelInstace->newDataReceivedFromTerminal(result);
    sendValueOnAllOutputTerminals( std::make_shared<CValue_int>(mp_dataListModelInstace->totalLengthOfSessionData()) );
}

void CLineSeriesChartBox::setModelMapperLineSeries(QtCharts::QLineSeries *newLineSeries )
{
    ASSERTWITHINFO(newLineSeries);
    mp_modelXYMapperLiveData->setSeries(newLineSeries) ;
}



void CLineSeriesChartBox::serializeBoxInfoIntoJson(QJsonObject &jsonObj)
{
    COperationBox::serializeBoxInfoIntoJson(jsonObj);
    jsonObj["movingWinLen"] = QString::number( mp_dataListModelInstace->movingWindowLength() ) ;
}

void CLineSeriesChartBox::deserializeBoxInfoFromJson(const QJsonObject &jsonObj)
{
    COperationBox::deserializeBoxInfoFromJson(jsonObj);
    auto movLen =  jsonObj["movingWinLen"].toString().toInt();
    if(movLen > 10)
        mp_dataListModelInstace->setMovingWindowLength(movLen);
}

