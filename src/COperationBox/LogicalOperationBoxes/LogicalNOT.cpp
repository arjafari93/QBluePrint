#include "LogicalNOT.h"

#include "RawValueBase.h"
#include "InputTerminal.h"
#include "OutputTerminal.h"

CLogicalNOT::CLogicalNOT(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent) : COperationBox{m_uniqueBoxName, newBlueBox_xPos, newBlueBox_yPos, blueBoxWidth, blueBoxHeight - 20, parent}
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigTextOperator;
    m_blueBox_HeadColor = QColor(155, 176, 128);
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Input");

    m_listOfInputTerminals.push_back(inputNode1);

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("Out");
    m_listOfOutputTerminals.push_back(outPutNode);

    m_blueBox_keyWords = "logical NOT !";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_LogicalOperation;
}

void CLogicalNOT::evaluateOperation()
{
    auto pCurrentData = m_listOfInputTerminals.at(0)->terminalCurrentData().get();
    std::shared_ptr<CRawValueBase> result{nullptr};
    if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentData))
    {
        result = std::make_shared<CValue_bool>(!pVal->value());
    }
    else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentData))
    {
        result = std::make_shared<CValue_bool>(!((long long)pVal->value()));
    }
    else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentData))
    {
        result = std::make_shared<CValue_bool>(!pVal->value());
    }
    else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentData))
    {
        result = std::make_shared<CValue_bool>(!pVal->value().toLongLong());
    }

    sendValueOnAllOutputTerminals(result);
}
