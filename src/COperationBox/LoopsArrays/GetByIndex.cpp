#include "GetByIndex.h"

#include "../../CRawValueBase/RawValueBase.h"
#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include <memory>

CGetByIndex::CGetByIndex(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent) : COperationBox{m_uniqueBoxName, newBlueBox_xPos, newBlueBox_yPos, blueBoxWidth, blueBoxHeight - 10, parent}
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigPictureOperator;
    m_blueBox_HeadColor = QColor(170, 150, 180);
    m_blueBox_HeaderIcon = "qrc:/Images/getIndex.png";
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Input");
    inputNode1->setTerminalCurrentData(std::make_shared<CValue_array>());
    m_listOfInputTerminals.push_back(inputNode1);

    auto indexNode = new CInputTerminal(1, this);
    indexNode->setTerminalName("Index");
    indexNode->setTerminalCurrentData(std::make_shared<CValue_int>(0));
    m_listOfInputTerminals.push_back(indexNode);

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("Elmnt");
    m_listOfOutputTerminals.push_back(outPutNode);

    m_blueBox_keyWords = "for each loop iteration iterate all element get by index";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_LoopsAndArrays;
}

CGetByIndex::~CGetByIndex() {}

void CGetByIndex::evaluateOperation()
{
    auto pArray = m_listOfInputTerminals.at(0)->terminalCurrentData().get();
    auto pIndex = m_listOfInputTerminals.at(1)->terminalCurrentData().get();
    if (!pArray || !pIndex)
        return;

    int indexInArr = -1;
    ;
    if (auto* pVal = dynamic_cast<CValue_int*>(pIndex))
    {
        indexInArr = pVal->value();
    }
    else if (auto* pVal = dynamic_cast<CValue_double*>(pIndex))
    {
        indexInArr = (long long)pVal->value();
    }
    else if (auto* pVal = dynamic_cast<CValue_string*>(pIndex))
    {
        indexInArr = pVal->value().toLongLong();
    }
    else if (auto* pVal = dynamic_cast<CValue_bool*>(pIndex))
    {
        indexInArr = (long long)pVal->value();
    }
    else if (auto* pVal = dynamic_cast<CValue_array*>(pIndex))
    {
        indexInArr = pVal->convertToString().toLongLong();
    }
    if (indexInArr < 0)
        return;

    CValue_array* sourceArray = nullptr;
    if (auto* pVal = dynamic_cast<CValue_int*>(pArray))
    {
        if (indexInArr == 0)
            m_listOfOutputTerminals.at(0)->sendValueToFlowLine(std::make_shared<CValue_int>(pVal->value()));
        return;
    }
    else if (auto* pVal = dynamic_cast<CValue_double*>(pArray))
    {
        if (indexInArr == 0)
            m_listOfOutputTerminals.at(0)->sendValueToFlowLine(std::make_shared<CValue_double>(pVal->value()));
        return;
    }
    else if (auto* pVal = dynamic_cast<CValue_string*>(pArray))
    {
        if (indexInArr < pVal->value().length())
            m_listOfOutputTerminals.at(0)->sendValueToFlowLine(std::make_shared<CValue_string>(pVal->value().at(indexInArr)));
        return;
    }
    else if (auto* pVal = dynamic_cast<CValue_bool*>(pArray))
    {
        if (indexInArr == 0)
            m_listOfOutputTerminals.at(0)->sendValueToFlowLine(std::make_shared<CValue_bool>(pVal->value()));
        return;
    }
    else if (auto* pVal = dynamic_cast<CValue_array*>(pArray))
    {
        sourceArray = pVal;
    }
    ASSERTWITHINFO(sourceArray);
    if (sourceArray->value().length() == 0 || indexInArr >= sourceArray->value().length()) // nothing to be sent or index out of range
        return;

    m_listOfOutputTerminals.at(0)->sendValueToFlowLine(sourceArray->value().at(indexInArr));
}
