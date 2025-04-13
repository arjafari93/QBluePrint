#include "ForEachLoop.h"


#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "../../CRawValueBase/RawValueBase.h"
#include <memory>


CForEachLoop::CForEachLoop ( int newBlueBox_xPos, int newBlueBox_yPos , QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth , blueBoxHeight , parent }
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigPictureOperator ;
    m_blueBox_HeadColor = QColor(200, 120, 160);
    m_blueBox_HeaderIcon = "qrc:/Images/forLoop.png";
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Array");
    inputNode1->setTerminalCurrentData( std::make_shared<CValue_array>() );
    m_listOfInputTerminals.push_back(inputNode1 );

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("Elmnt");
    m_listOfOutputTerminals.push_back( outPutNode );

    auto indexNode = new COutputTerminal(1, this);
    indexNode->setTerminalName("Index");
    m_listOfOutputTerminals.push_back( indexNode );

    m_blueBox_keyWords = "for each loop iteration iterate all element array";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_LoopsAndArrays;
}

CForEachLoop::~CForEachLoop()
{

}



void CForEachLoop::evaluateOperation()
{
    auto pArray = m_listOfInputTerminals.at(0)->terminalCurrentData().get() ;
    if( !pArray )
        return ;
    CValue_array*  sourceArray=  nullptr;
    if (auto* pVal = dynamic_cast<CValue_int*>(pArray)) {
        m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_int>(pVal->value()) );
        m_listOfOutputTerminals.at(1)->sendValueToFlowLine( std::make_shared<CValue_int>(0) );
        return ;
    } else if (auto* pVal = dynamic_cast<CValue_double*>(pArray)) {
        m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_double>(pVal->value()) );
        m_listOfOutputTerminals.at(1)->sendValueToFlowLine( std::make_shared<CValue_int>(0) );
        return ;
    }else if (auto* pVal = dynamic_cast<CValue_string*>(pArray)) {
        m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_string>(pVal->value()) );
        m_listOfOutputTerminals.at(1)->sendValueToFlowLine( std::make_shared<CValue_int>(0) );
        return ;
    }else if (auto* pVal = dynamic_cast<CValue_bool*>(pArray)) {
        m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_bool>(pVal->value()) );
        m_listOfOutputTerminals.at(1)->sendValueToFlowLine( std::make_shared<CValue_int>(0) );
        return ;
    }else if (auto* pVal = dynamic_cast<CValue_array*>(pArray)) {
        sourceArray =  pVal ;
    }
    ASSERTWITHINFO(sourceArray);
    if(sourceArray->value().length() == 0 ) // nothing to be sent
        return ;

    int iter=0;
    for(auto pVal : sourceArray->value()){
        m_listOfOutputTerminals.at(0)->sendValueToFlowLine( pVal );
        m_listOfOutputTerminals.at(1)->sendValueToFlowLine( std::make_shared<CValue_int>(iter) );
        iter++;
    }
}

