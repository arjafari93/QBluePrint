#include "MathSubtraction.h"

#include "RawValueBase.h"
#include "InputTerminal.h"
#include "OutputTerminal.h"

class CMathSubtractionVisitor : public CValueVisitor
{
  public:
    explicit CMathSubtractionVisitor(CRawValueBase* rhs) : mp_rhs(rhs) {}
    std::shared_ptr<CRawValueBase> result() const { return m_result; }

    void visit(const CValue_int& lhs) override
    {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs))
        {
            m_result = std::make_shared<CValue_int>(lhs.value() - pVal->value());
        }
        else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs))
        {
            m_result = std::make_shared<CValue_double>(lhs.value() - pVal->value());
        }
        else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs))
        {
            m_result = std::make_shared<CValue_int>(lhs.value() - (long long)pVal->value());
        }
        else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs))
        {
            m_result = std::make_shared<CValue_string>(QString::number(lhs.value()).remove(pVal->value()));
        }
        else if (auto* pVal = dynamic_cast<CValue_array*>(mp_rhs))
        {
            m_result = lhs.value() - *pVal;
        }
    }

    void visit(const CValue_double& lhs) override
    {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs))
        {
            m_result = std::make_shared<CValue_double>(lhs.value() - pVal->value());
        }
        else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs))
        {
            m_result = std::make_shared<CValue_double>(lhs.value() - pVal->value());
        }
        else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs))
        {
            m_result = std::make_shared<CValue_double>(lhs.value() - pVal->value());
        }
        else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs))
        {
            m_result = std::make_shared<CValue_string>(QString::number(lhs.value(), 'f', MAX_DOUBLE_PRECISION).remove(pVal->value()));
        }
        else if (auto* pVal = dynamic_cast<CValue_array*>(mp_rhs))
        {
            m_result = lhs.value() - *pVal;
        }
    }

    void visit(const CValue_string& lhs) override
    {
        QString tempLHS = lhs.value();
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs))
        {
            m_result = std::make_shared<CValue_string>(tempLHS.remove(QString::number(pVal->value())));
        }
        else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs))
        {
            m_result = std::make_shared<CValue_string>(tempLHS.remove(QString::number(pVal->value(), 'f', MAX_DOUBLE_PRECISION)));
        }
        else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs))
        {
            m_result = std::make_shared<CValue_string>(tempLHS.remove(QString::number(pVal->value())));
        }
        else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs))
        {
            m_result = std::make_shared<CValue_string>(tempLHS.remove(pVal->value()));
        }
        else if (auto* pVal = dynamic_cast<CValue_array*>(mp_rhs))
        {
            m_result = lhs.value() - *pVal;
        }
    }

    void visit(const CValue_bool& lhs) override
    {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs))
        {
            m_result = std::make_shared<CValue_int>((long long)lhs.value() - pVal->value());
        }
        else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs))
        {
            m_result = std::make_shared<CValue_double>(lhs.value() - pVal->value());
        }
        else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs))
        {
            m_result = std::make_shared<CValue_bool>(lhs.value() - pVal->value());
        }
        else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs))
        {
            m_result = std::make_shared<CValue_string>(QString::number(lhs.value()).remove(pVal->value()));
        }
        else if (auto* pVal = dynamic_cast<CValue_array*>(mp_rhs))
        {
            m_result = lhs.value() - *pVal;
        }
    }

    void visit(const CValue_array& lhs) override
    {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs))
        {
            m_result = lhs - pVal->value();
        }
        else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs))
        {
            m_result = lhs - pVal->value();
        }
        else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs))
        {
            m_result = lhs - pVal->value();
        }
        else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs))
        {
            m_result = lhs - pVal->value();
        }
        else if (auto* pVal = dynamic_cast<CValue_array*>(mp_rhs))
        {
            m_result = lhs - *pVal;
        }
    }

    void visit(const CValue_map& lhs) override { Q_UNUSED(lhs) }

  private:
    std::shared_ptr<CRawValueBase> m_result{nullptr};
    CRawValueBase* mp_rhs = nullptr; // The second operand (factor)
};

CMathSubtraction::CMathSubtraction(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent) : COperationBox{m_uniqueBoxName, newBlueBox_xPos, newBlueBox_yPos, blueBoxWidth, blueBoxHeight, parent}
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigPictureOperator;
    m_blueBox_HeaderIcon = "qrc:/Images/minus.png";
    m_blueBox_HeadColor = QColor(150, 220, 255);
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Left");
    auto inputNode2 = new CInputTerminal(1, this);
    inputNode2->setTerminalName("Right");
    m_listOfInputTerminals.push_back(inputNode1);
    m_listOfInputTerminals.push_back(inputNode2);

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("Out");
    m_listOfOutputTerminals.push_back(outPutNode);

    m_blueBox_keyWords = "Math Subtraction, minus -";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_MathOperation;
}

void CMathSubtraction::evaluateOperation()
{
    auto lhs = m_listOfInputTerminals.at(0)->terminalCurrentData().get();
    auto rhs = m_listOfInputTerminals.at(1)->terminalCurrentData().get();
    if (!lhs || !rhs)
        return;
    CMathSubtractionVisitor visitor(rhs);
    lhs->accept(visitor);
    sendValueOnAllOutputTerminals(visitor.result());
}
