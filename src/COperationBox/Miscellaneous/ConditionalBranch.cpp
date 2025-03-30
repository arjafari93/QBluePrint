#include "ConditionalBranch.h"

#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "../../CRawValueBase/RawValueBase.h"

inline const static int blueBoxWidth  = 220 ;
inline const static int blueBoxHeight = 120 ;


CConditionalBranch::CConditionalBranch ( int newBlueBox_xPos, int newBlueBox_yPos , QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth , blueBoxHeight , parent }
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigPictureOperator ;
    m_blueBox_HeadColor = QColor(25, 167, 206);
    m_blueBox_HeaderIcon = "qrc:/Images/branch.png";
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Data");
    auto inputNode2 = new CInputTerminal(1, this);
    inputNode2->setTerminalName("Condition");
    m_listOfInputTerminals.push_back(inputNode1 );
    m_listOfInputTerminals.push_back(inputNode2 );

    auto outPutNodeTrue = new COutputTerminal(0, this);
    outPutNodeTrue->setTerminalName("True");
    m_listOfOutputTerminals.push_back( outPutNodeTrue );

    auto outPutNodeFalse = new COutputTerminal(1, this);
    outPutNodeFalse->setTerminalName("False");
    m_listOfOutputTerminals.push_back( outPutNodeFalse );

    m_blueBox_keyWords = "Conditional Branch";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_Miscellaneous ;
}





void CConditionalBranch::evaluateOperation()
{
    bool condData = false ;
    {// make scope to minimize the stack size on recursion
        auto pCondData = m_listOfInputTerminals.at(1)->terminalCurrentData().get() ;
        if(!pCondData)
            return ;

        if (auto* pVal = dynamic_cast<CValue_int*>(pCondData)) {
            condData =  (bool)pVal->value()   ;
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCondData)) {
            condData = (bool)pVal->value();
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCondData)) {
            condData = pVal->value();
        } else if (auto* pVal = dynamic_cast<CValue_string*>(pCondData)) {
            condData = pVal->value().size();
        }else{
            DEBUG_MSG_PRINT << "inavlid daata type " ;
            return ;
        }
    }

    if(!m_listOfInputTerminals.at(0)->terminalCurrentData().get())
        return ;
    if( condData ){
        m_listOfOutputTerminals.at(0)->sendValueToFlowLine( m_listOfInputTerminals.at(0)->terminalCurrentData() );
    }else{
        m_listOfOutputTerminals.at(1)->sendValueToFlowLine( m_listOfInputTerminals.at(0)->terminalCurrentData() );
    }
}
