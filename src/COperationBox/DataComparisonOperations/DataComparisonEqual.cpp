#include "DataComparisonEqual.h"


#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "../../CRawValueBase/RawValueBase.h"


class CDataComparisonEqualVisitor : public CValueVisitor {
public:

    explicit CDataComparisonEqualVisitor(CRawValueBase* rhs) : mp_rhs(rhs) {}
    std::shared_ptr<CRawValueBase>  result()const { return m_result ;}

    void visit(const CValue_int& lhs) override {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(lhs.value() == pVal->value());
        } else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(lhs.value() == pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(lhs.value() == (long long)pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(lhs.value() == pVal->value().toLongLong());
        }else if (auto* pVal = dynamic_cast<CValue_array*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(false);
        }
    }

    void visit(const CValue_double& lhs) override {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(lhs.value() == pVal->value());
        } else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(lhs.value() == pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(lhs.value() == (long double)pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(lhs.value() == pVal->value().toDouble());
        }else if (auto* pVal = dynamic_cast<CValue_array*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(false);
        }
    }

    void visit(const CValue_string& lhs) override {
        Q_UNUSED(lhs)
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(lhs.value().toLongLong() == pVal->value());
        } else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(lhs.value().toDouble() == pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(lhs.value().toLongLong() == (long long)pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(lhs.value() == pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_array*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(false);
        }
    }

    void visit(const CValue_bool& lhs) override {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>((long long)lhs.value() == pVal->value());
        } else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>((long double)lhs.value() == pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(lhs.value() == pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>((long long)lhs.value() == pVal->value().size());
        }else if (auto* pVal = dynamic_cast<CValue_array*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(false);
        }
    }

    void visit(const CValue_array& lhs) override {
        if (auto* pVal = dynamic_cast<CValue_array*>(mp_rhs)) {
            m_result = *pVal == lhs ;
        }else{
            m_result = std::make_shared<CValue_bool>(false);
        }
    }

    void visit(const CValue_map& lhs) override {
        Q_UNUSED(lhs)
    }

private:
    std::shared_ptr<CRawValueBase> m_result{nullptr};
    CRawValueBase* mp_rhs = nullptr;  // The second operand (factor)
};



CDataComparisonEqual::CDataComparisonEqual ( int newBlueBox_xPos, int newBlueBox_yPos , QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth , blueBoxHeight , parent }
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigTextOperator ;
    m_blueBox_HeadColor = QColor(200, 0, 255);
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Left");
    auto inputNode2 = new CInputTerminal(1, this);
    inputNode2->setTerminalName("Right");
    m_listOfInputTerminals.push_back(inputNode1 );
    m_listOfInputTerminals.push_back(inputNode2 );

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("Out");
    m_listOfOutputTerminals.push_back( outPutNode );

    m_blueBox_keyWords = "Comparator compare comparison equal  same ==";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_DataComparison ;
}





void CDataComparisonEqual::evaluateOperation()
{
    auto lhs = m_listOfInputTerminals.at(0)->terminalCurrentData().get();
    auto rhs = m_listOfInputTerminals.at(1)->terminalCurrentData().get();
    if(!lhs || !rhs)
        return ;
    CDataComparisonEqualVisitor visitor(rhs);
    lhs->accept(visitor);
    sendValueOnAllOutputTerminals( visitor.result() );

}
