#include "MathAbsolute.h"


#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "../../CRawValueBase/RawValueBase.h"

inline const static int blueBoxWidth  = 220 ;
inline const static int blueBoxHeight = 100 ;


CMathAbsolute::CMathAbsolute ( int newBlueBox_xPos, int newBlueBox_yPos , QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth , blueBoxHeight , parent }
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigPictureOperator ;
    m_blueBox_HeadColor = QColor(148, 0, 255);
    m_blueBox_HeaderIcon = "qrc:/Images/absolute.png";
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Input");

    m_listOfInputTerminals.push_back(inputNode1 );

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("out");
    m_listOfOutputTerminals.push_back( outPutNode );

    m_blueBox_keyWords = "Math Abstract | |";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_MathOperation ;
}



void CMathAbsolute::evaluateOperation()
{
    auto pCurrentData = m_listOfInputTerminals.at(0)->terminalCurrentData().get() ;
    std::shared_ptr<CRawValueBase> result{nullptr};
    if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentData)) {
        result = std::make_shared<CValue_int>( abs(pVal->value()) );
    } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentData)) {
        result = std::make_shared<CValue_double>(abs( pVal->value()));
    }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentData)) {
        result = std::make_shared<CValue_bool>(pVal->value());
    }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentData)) {
        result = std::make_shared<CValue_int>(abs(pVal->value().toLongLong()));
    }

    sendValueOnAllOutputTerminals( result );


}
