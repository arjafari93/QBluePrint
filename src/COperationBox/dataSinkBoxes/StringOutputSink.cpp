#include "StringOutputSink.h"

#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"

#include "src/CRawValueBase/RawValueBase.h"


inline const static int blueBoxWidth  = 300 ;
inline const static int blueBoxHeight = 150 ;





CStringOutputSink::CStringOutputSink ( int newBlueBox_xPos, int newBlueBox_yPos,  QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth , blueBoxHeight , parent }
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_OutputSinkWithString ;
    m_blueBox_HeadColor = QColor(116, 142, 99);
    m_blueBox_HeaderIcon = "qrc:/Images/textOutput.png";
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Input");
    m_listOfInputTerminals.push_back(inputNode1 );

    m_blueBox_keyWords = "output, out put, sink, display, string ";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_OutPutSink ;
}



void CStringOutputSink::evaluateOperation()
{
    auto rhs = m_listOfInputTerminals.at(0)->terminalCurrentData().get() ;
    if (auto* pVal = dynamic_cast<CValue_int*>(rhs)) {
        m_stringToBeDisplayed = QString::number(pVal->value()) ;
    } else if (auto* pVal = dynamic_cast<CValue_double*>(rhs)) {
        m_stringToBeDisplayed = QString::number(pVal->value() , 'f' , MAX_DOUBLE_PRECISION ) ;
    }else if (auto* pVal = dynamic_cast<CValue_string*>(rhs)) {
        m_stringToBeDisplayed = pVal->value() ;
    }else if (auto* pVal = dynamic_cast<CValue_bool*>(rhs)) {
        m_stringToBeDisplayed =  QString::number(pVal->value()) ;
    }
    emit stringToBeDisplayedChanged() ;
    return  ;
}


