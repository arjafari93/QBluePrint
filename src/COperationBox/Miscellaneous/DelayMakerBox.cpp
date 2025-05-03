#include "DelayMakerBox.h"

#include <QTimer>

#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "../../CRawValueBase/RawValueBase.h"


CDelayMakerBox::CDelayMakerBox ( int newBlueBox_xPos, int newBlueBox_yPos , QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth , blueBoxHeight , parent }
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigPictureOperator ;
    m_blueBox_HeadColor = QColor(180, 120, 95);
    m_blueBox_HeaderIcon = "qrc:/Images/hourGlassIcon.png";
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Input");
    auto inputNode2 = new CInputTerminal(1, this);
    inputNode2->setTerminalName("Delay");
    inputNode2->setTerminalCurrentData(std::make_shared<CValue_int>(m_msDelay));
    m_listOfInputTerminals.push_back(inputNode1 );
    m_listOfInputTerminals.push_back(inputNode2 );

    // find delay has changed through popup
    connect(inputNode2 , &CIOTerminal::nodeIsPassingNewValue , this , [this, inputNode2](){
        auto pNewDelay =  dynamic_cast<CValue_int*>(inputNode2->terminalCurrentData().get());
        if(pNewDelay->value() != m_msDelay){
            if(pNewDelay->value() < 0 )
                m_msDelay = 0 ;
            else
                m_msDelay = pNewDelay->value() ;
            mp_sendValueTimer->setInterval(m_msDelay);
        }
    });

    auto outPutNode1 = new COutputTerminal(0, this);
    outPutNode1->setTerminalName("Output");
    m_listOfOutputTerminals.push_back( outPutNode1 );

    auto outPutNode2 = new COutputTerminal(1, this);
    outPutNode2->setTerminalName("Count");
    m_listOfOutputTerminals.push_back( outPutNode2 );

    m_blueBox_keyWords = "Delay Timer late wait ";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_Miscellaneous ;

    mp_sendValueTimer = new QTimer(this);
    connect(mp_sendValueTimer , &QTimer::timeout , this , [this](){
        if(m_valuesToBeSent.size() == 0 ){
            mp_sendValueTimer->stop();
            return ;
        }
        m_listOfOutputTerminals.at(0)->sendValueToFlowLine(m_valuesToBeSent.front()) ;
        m_valuesToBeSent.pop_front();
        m_listOfOutputTerminals.at(1)->sendValueToFlowLine( std::make_shared<CValue_int>(m_valuesToBeSent.size()) );
    });
}

CDelayMakerBox::~CDelayMakerBox()
{

}





void CDelayMakerBox::evaluateOperation()
{
    { // minimize footprint on stack in recursion
        int delay = 10 ;
        auto pNewDelay = m_listOfInputTerminals.at(1)->terminalCurrentData().get() ;
        if(!pNewDelay)
            return ;
        if (auto* pVal = dynamic_cast<CValue_int*>(pNewDelay)) {
            delay =  (long long)pVal->value()   ;
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pNewDelay)) {
            delay = (long long)pVal->value();
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pNewDelay)) {
            delay = pVal->value();
        } else if (auto* pVal = dynamic_cast<CValue_string*>(pNewDelay)) {
            delay = pVal->value().toLongLong();
        }else{
            DEBUG_MSG_PRINT << "inavlid daata type " ;
            return ;
        }
        if(m_msDelay != delay ){
            if(delay < 0 )
                delay = 0 ;
            m_msDelay = delay ;
            mp_sendValueTimer->setInterval(m_msDelay);
            return ;
        }
    }
    // if we are here it means the first input has new data
    m_valuesToBeSent.push_back(m_listOfInputTerminals.at(0)->terminalCurrentData());
    if(!mp_sendValueTimer->isActive())
        mp_sendValueTimer->start();
    // send count on its terminal
    m_listOfOutputTerminals.at(1)->sendValueToFlowLine( std::make_shared<CValue_int>(m_valuesToBeSent.size()) );

}


void CDelayMakerBox::deserializeBoxInfoFromJson(const QJsonObject &jsonObj)
{
    // in this specific box we call the base deserialize method after the derived body, bcz teminals will change in derived body
    COperationBox::deserializeBoxInfoFromJson(jsonObj);
    auto pNewDelay =  dynamic_cast<CValue_int*>(m_listOfInputTerminals.at(1)->terminalCurrentData().get());
    if(pNewDelay->value() != m_msDelay){
        if(pNewDelay->value() < 0 )
            m_msDelay = 0 ;
        else
            m_msDelay = pNewDelay->value() ;
        mp_sendValueTimer->setInterval(m_msDelay);
    }
}
