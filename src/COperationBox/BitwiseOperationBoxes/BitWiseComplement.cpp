#include "BitWiseComplement.h"

#include "../../CRawValueBase/RawValueBase.h"
#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"

CBitWiseComplement::CBitWiseComplement(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent)
    : COperationBox{m_uniqueBoxName, newBlueBox_xPos, newBlueBox_yPos, blueBoxWidth, blueBoxHeight - 20, parent}
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigTextOperator;
    m_blueBox_HeadColor = QColor(151, 254, 237);
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Input");

    m_listOfInputTerminals.push_back(inputNode1);

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("Out");
    m_listOfOutputTerminals.push_back(outPutNode);

    m_blueBox_keyWords = "BitWise Complement ~";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_LogicalOperation;
}

void CBitWiseComplement::evaluateOperation()
{
    auto pCurrentData = m_listOfInputTerminals.at(0)->terminalCurrentData().get();
    std::shared_ptr<CRawValueBase> result{nullptr};
    if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentData))
    {
        result = std::make_shared<CValue_int>(~pVal->value());
    }
    else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentData))
    {
        result = std::make_shared<CValue_double>(~((long long)pVal->value()));
    }
    else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentData))
    {
        result = std::make_shared<CValue_bool>(!pVal->value());
    }
    else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentData))
    {
        result = std::make_shared<CValue_string>("");
    }
    else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentData))
    {
        result = ~(*pVal);
    }
    else
    {
        DEBUG_MSG_PRINT << "invalid type ";
        return;
    }

    sendValueOnAllOutputTerminals(result);
}
