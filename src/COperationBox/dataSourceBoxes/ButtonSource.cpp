#include "ButtonSource.h"


#include <memory>

#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CRawValueBase/RawValueBase.h"



CButtonSource::CButtonSource ( int newBlueBox_xPos, int newBlueBox_yPos, QObject *parent)
    : COperationBox{m_uniqueBoxName , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth , blueBoxHeight - 20  , parent }
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_InputButtonSource ;
    m_blueBox_HeaderIcon = "qrc:/Images/buttonClickIcon.png" ;
    m_blueBox_HeadColor = QColor(200 , 200 , 250 );

    auto outPutNodeString = new COutputTerminal(0, this);
    outPutNodeString->setTerminalName("Out");
    m_listOfOutputTerminals.push_back( outPutNodeString );

    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("In");
    // we put a zero in input terminal by default
    inputNode1->setTerminalCurrentData(std::make_shared<CValue_int>(0));
    m_listOfInputTerminals.push_back(inputNode1 );

    m_blueBox_keyWords = "button click press source input";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_InputSource ;
}

void CButtonSource::evaluateOperation()
{
    auto pInput = m_listOfInputTerminals.at(0)->terminalCurrentData() ;
    if(!pInput.get())
        return ;
    m_listOfOutputTerminals.at(0)->sendValueToFlowLine(  pInput );
}

CButtonSource::~CButtonSource()
{

}

