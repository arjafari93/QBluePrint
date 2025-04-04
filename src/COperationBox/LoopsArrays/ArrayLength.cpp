#include "ArrayLength.h"

#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "../../CRawValueBase/RawValueBase.h"
#include <memory>

inline const static int blueBoxWidth  = 220 ;
inline const static int blueBoxHeight = 100 ;


CArrayLength::CArrayLength ( int newBlueBox_xPos, int newBlueBox_yPos , QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth , blueBoxHeight , parent }
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigPictureOperator ;
    m_blueBox_HeadColor = QColor(170, 150, 220);
    m_blueBox_HeaderIcon = "qrc:/Images/arrayLen.png";
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Input");
    inputNode1->setTerminalCurrentData( std::make_shared<CValue_list>() );
    m_listOfInputTerminals.push_back(inputNode1 );

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("Len");
    m_listOfOutputTerminals.push_back( outPutNode );

    m_blueBox_keyWords = "array size element length number";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_LoopsAndArrays;
}

CArrayLength::~CArrayLength()
{

}



void CArrayLength::evaluateOperation()
{
    auto pArray = m_listOfInputTerminals.at(0)->terminalCurrentData().get() ;
    if( !pArray)
        return ;

    if (auto* pVal = dynamic_cast<CValue_int*>(pArray)) {
        m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_int>(1) );
    } else if (auto* pVal = dynamic_cast<CValue_double*>(pArray)) {
        m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_int>(1)) ;
    }else if (auto* pVal = dynamic_cast<CValue_string*>(pArray)) {
        m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_int>(pVal->value().length()) );
    }else if (auto* pVal = dynamic_cast<CValue_bool*>(pArray)) {
        m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_int>( 1 ) );
    }else if (auto* pVal = dynamic_cast<CValue_list*>(pArray)) {
        m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_int>( pVal->value().length() ) );
    }
}

