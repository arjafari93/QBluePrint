#include "ParseIntoArray.h"

#include <QJsonDocument>
#include <QJsonObject>

#include "../../CRawValueBase/RawValueBase.h"
#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"

CParseIntoArray::CParseIntoArray(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent) : COperationBox{m_uniqueBoxName, newBlueBox_xPos, newBlueBox_yPos, blueBoxWidth, blueBoxHeight + 20, parent}
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigPictureOperator;
    m_blueBox_HeaderIcon = "qrc:/Images/parseToArray.png";
    m_blueBox_HeadColor = QColor(200, 50, 200);
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Source");
    m_listOfInputTerminals.push_back(inputNode1);

    auto inputNode2 = new CInputTerminal(1, this);
    inputNode2->setTerminalName("Delimiter");
    inputNode2->setTerminalCurrentData(std::make_shared<CValue_string>("\n"));
    m_listOfInputTerminals.push_back(inputNode2);

    auto inputNode3 = new CInputTerminal(2, this);
    inputNode3->setTerminalName("Cull Empty");
    inputNode3->setTerminalCurrentData(std::make_shared<CValue_bool>(true));
    m_listOfInputTerminals.push_back(inputNode3);

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("Array");
    m_listOfOutputTerminals.push_back(outPutNode);

    auto countNode = new COutputTerminal(1, this);
    countNode->setTerminalName("len");
    m_listOfOutputTerminals.push_back(countNode);

    m_blueBox_keyWords = "parse string array convert multi cast split list";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_LoopsAndArrays;
}

void CParseIntoArray::evaluateOperation()
{
    auto pSrc = m_listOfInputTerminals.at(0)->terminalCurrentData().get();
    auto pDelmtr = m_listOfInputTerminals.at(1)->terminalCurrentData().get();
    auto pCullEmpty = m_listOfInputTerminals.at(2)->terminalCurrentData().get();
    if (!pSrc || !pDelmtr || !pCullEmpty)
        return;
    QString sourceVal = "";
    if (auto* pVal = dynamic_cast<CValue_int*>(pSrc))
    {
        sourceVal = QString::number(pVal->value());
    }
    else if (auto* pVal = dynamic_cast<CValue_double*>(pSrc))
    {
        sourceVal = QString::number(pVal->value(), 'f', MAX_DOUBLE_PRECISION);
    }
    else if (auto* pVal = dynamic_cast<CValue_string*>(pSrc))
    {
        sourceVal = pVal->value();
    }
    else if (auto* pVal = dynamic_cast<CValue_bool*>(pSrc))
    {
        sourceVal = QString::number(pVal->value());
    }
    else if (auto* pVal = dynamic_cast<CValue_array*>(pSrc))
    {
        sourceVal = pVal->convertToString();
    }

    if (sourceVal.length() == 0) // nothing to be parsed
        return;

    QString delimiterStr = "\n";
    if (auto* pVal = dynamic_cast<CValue_int*>(pDelmtr))
    {
        delimiterStr = QString::number(pVal->value());
    }
    else if (auto* pVal = dynamic_cast<CValue_double*>(pDelmtr))
    {
        delimiterStr = QString::number(pVal->value(), 'f', MAX_DOUBLE_PRECISION);
    }
    else if (auto* pVal = dynamic_cast<CValue_string*>(pDelmtr))
    {
        delimiterStr = pVal->value();
    }
    else if (auto* pVal = dynamic_cast<CValue_bool*>(pDelmtr))
    {
        delimiterStr = QString::number(pVal->value());
    }
    else if (auto* pVal = dynamic_cast<CValue_array*>(pDelmtr))
    {
        delimiterStr = pVal->convertToString();
    }

    bool skipTheEmpty = true;
    ;
    if (auto* pVal = dynamic_cast<CValue_int*>(pCullEmpty))
    {
        skipTheEmpty = pVal->value();
    }
    else if (auto* pVal = dynamic_cast<CValue_double*>(pCullEmpty))
    {
        skipTheEmpty = pVal->value();
    }
    else if (auto* pVal = dynamic_cast<CValue_string*>(pCullEmpty))
    {
        skipTheEmpty = pVal->value().toLongLong();
    }
    else if (auto* pVal = dynamic_cast<CValue_bool*>(pCullEmpty))
    {
        skipTheEmpty = pVal->value();
    }
    else if (auto* pVal = dynamic_cast<CValue_array*>(pCullEmpty))
    {
        skipTheEmpty = pVal->convertToString().toLongLong();
    }

    auto strArray = sourceVal.split(delimiterStr, (skipTheEmpty ? Qt::SkipEmptyParts : Qt::KeepEmptyParts));
    m_listOfOutputTerminals.at(0)->sendValueToFlowLine(std::make_shared<CValue_array>(strArray));
    m_listOfOutputTerminals.at(1)->sendValueToFlowLine(std::make_shared<CValue_int>(strArray.length()));
}
