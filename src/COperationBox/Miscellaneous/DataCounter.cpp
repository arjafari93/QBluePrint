#include "DataCounter.h"

#include "../../CRawValueBase/RawValueBase.h"
#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include <memory>

CDataCounter::CDataCounter(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent) : COperationBox{m_uniqueBoxName, newBlueBox_xPos, newBlueBox_yPos, blueBoxWidth, blueBoxHeight + 20, parent}
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigTextOperator;
    m_blueBox_HeadColor = QColor(200, 120, 160);
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("++");

    auto inputNode2 = new CInputTerminal(1, this);
    inputNode2->setTerminalName("Init");
    inputNode2->setTerminalCurrentData(std::make_shared<CValue_int>(0));
    auto inputNode3 = new CInputTerminal(2, this);
    inputNode3->setTerminalName("Step");
    inputNode3->setTerminalCurrentData(std::make_shared<CValue_int>(1));

    m_listOfInputTerminals.push_back(inputNode1);
    m_listOfInputTerminals.push_back(inputNode2);
    m_listOfInputTerminals.push_back(inputNode3);

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("Count");
    m_listOfOutputTerminals.push_back(outPutNode);

    m_blueBox_keyWords = "counter increament count ";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_Miscellaneous;
}

CDataCounter::~CDataCounter() {}

void CDataCounter::evaluateOperation()
{
    if (!m_listOfInputTerminals.at(0)->terminalCurrentData().get() || !m_listOfInputTerminals.at(1)->terminalCurrentData().get())
        return;
    { // make scope to minimize the stack size on recursion
        auto pinitialValue = m_listOfInputTerminals.at(1)->terminalCurrentData().get();
        int newResetVal = 0;
        if (auto* pVal = dynamic_cast<CValue_int*>(pinitialValue))
        {
            newResetVal = pVal->value();
        }
        else if (auto* pVal = dynamic_cast<CValue_double*>(pinitialValue))
        {
            newResetVal = (long long)pVal->value();
        }
        else if (auto* pVal = dynamic_cast<CValue_bool*>(pinitialValue))
        {
            newResetVal = (long long)pVal->value();
        }
        else if (auto* pVal = dynamic_cast<CValue_string*>(pinitialValue))
        {
            newResetVal = pVal->value().toLongLong();
        }

        if (newResetVal != m_initialValue)
        {
            // we have a new reset value, set new reset value wihtout adding to counter
            m_dataCounter = newResetVal; // reset the actual counter
            m_initialValue = newResetVal;
            sendValueOnAllOutputTerminals(std::make_shared<CValue_int>(newResetVal));
            return;
        }
    }
    {
        auto pStepSizeValue = m_listOfInputTerminals.at(2)->terminalCurrentData().get();
        int newStepVal = 1;
        if (auto* pVal = dynamic_cast<CValue_int*>(pStepSizeValue))
        {
            newStepVal = pVal->value();
        }
        else if (auto* pVal = dynamic_cast<CValue_double*>(pStepSizeValue))
        {
            newStepVal = (long long)pVal->value();
        }
        else if (auto* pVal = dynamic_cast<CValue_bool*>(pStepSizeValue))
        {
            newStepVal = (long long)pVal->value();
        }
        else if (auto* pVal = dynamic_cast<CValue_string*>(pStepSizeValue))
        {
            newStepVal = pVal->value().toLongLong();
        }

        if (newStepVal != m_stepSize)
        {
            // we have a new stepSize , set new stepsize value wihtout adding to counter
            m_stepSize = newStepVal;
            return;
        }
    }

    // if we are here, it means there was a reception of data at terminal 0, we dont care what the data was
    // we only increament the counter and send it to the output
    m_dataCounter += m_stepSize;
    sendValueOnAllOutputTerminals(std::make_shared<CValue_int>(m_dataCounter));
}
