#include "BitWiseRightShift.h"



#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "../../CRawValueBase/RawValueBase.h"

inline const static int blueBoxWidth  = 220 ;
inline const static int blueBoxHeight = 120 ;

class CBitWiseRightShiftVisitor : public CValueVisitor {
public:

    explicit CBitWiseRightShiftVisitor(CRawValueBase* rhs) : mp_rhs(rhs) {}
    std::shared_ptr<CRawValueBase>  result()const { return m_result ;}

    void visit(const CValue_int& lhs) override {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs)) {
            m_result = std::make_shared<CValue_int>(lhs.value() >> pVal->value());
        } else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs)) {
            m_result = std::make_shared<CValue_int>(lhs.value() >> (long long)pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs)) {
            m_result = std::make_shared<CValue_int>(lhs.value() >> (long long)pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs)) {
            auto numShifts = pVal->value().toLongLong();
            m_result = std::make_shared<CValue_int>(lhs.value() >> numShifts);
        }
    }

    void visit(const CValue_double& lhs) override {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs)) {
            m_result = std::make_shared<CValue_double>((long long)lhs.value() >> pVal->value());
        } else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs)) {
            m_result = std::make_shared<CValue_double>((long long)lhs.value() >> (long long)pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs)) {
            m_result = std::make_shared<CValue_double>((long long)lhs.value() >> (long long)pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs)) {
            auto numShifts = pVal->value().toLongLong();
            m_result = std::make_shared<CValue_double>((long long)lhs.value() >> numShifts);
        }
    }

    void visit(const CValue_string& lhs) override {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs)) {
            if(lhs.value().length() >= pVal->value() ){
                auto trmiedStr = lhs.value().left(lhs.value().length() - pVal->value() );  // Keeps all but the last character
                m_result = std::make_shared<CValue_string>(trmiedStr);
            }else{
                m_result = std::make_shared<CValue_string>("");
            }
        } else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs)) {
            if(lhs.value().length() >= (long long)pVal->value() ){
                auto trmiedStr = lhs.value().left(lhs.value().length() - (long long)pVal->value() );  // Keeps all but the last character
                m_result = std::make_shared<CValue_string>(trmiedStr);
            }else{
                m_result = std::make_shared<CValue_string>("");
            }
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs)) {
            if(lhs.value().length() >= (long long)pVal->value() ){
                auto trmiedStr = lhs.value().left(lhs.value().length() - (long long)pVal->value() );  // Keeps all but the last character
                m_result = std::make_shared<CValue_string>(trmiedStr);
            }else{
                m_result = std::make_shared<CValue_string>("");
            }
        }else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs)) {
            if(lhs.value().length() >= pVal->value().toLongLong() ){
                auto trmiedStr = lhs.value().left(lhs.value().length() - pVal->value().toLongLong() );  // Keeps all but the last character
                m_result = std::make_shared<CValue_string>(trmiedStr);
            }else{
                m_result = std::make_shared<CValue_string>("");
            }
        }
    }

    void visit(const CValue_bool& lhs) override {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs)) {
            m_result = std::make_shared<CValue_int>((long long)lhs.value() >> pVal->value());
        } else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs)) {
            m_result = std::make_shared<CValue_int>((long long)lhs.value() >> (long long)pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs)) {
            m_result = std::make_shared<CValue_int>((long long)lhs.value() >> (long long)pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs)) {
            auto numShifts = pVal->value().toLongLong();
            m_result = std::make_shared<CValue_int>((long long)lhs.value() >> numShifts);
        }
    }

    void visit(const CValue_list& lhs) override {
        Q_UNUSED(lhs)
    }

    void visit(const CValue_map& lhs) override {
        Q_UNUSED(lhs)
    }

private:
    std::shared_ptr<CRawValueBase> m_result{nullptr};
    CRawValueBase* mp_rhs = nullptr;  // The second operand (factor)
};



CBitWiseRightShift::CBitWiseRightShift ( int newBlueBox_xPos, int newBlueBox_yPos , QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth , blueBoxHeight , parent }
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigTextOperator ;
    m_blueBox_HeadColor = QColor(160, 132, 230);
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Val");
    auto inputNode2 = new CInputTerminal(1, this);
    inputNode2->setTerminalName("n");
    m_listOfInputTerminals.push_back(inputNode1 );
    m_listOfInputTerminals.push_back(inputNode2 );

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("Out");
    m_listOfOutputTerminals.push_back( outPutNode );

    m_blueBox_keyWords = "BitWise Right Shift";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_LogicalOperation ;
}





void CBitWiseRightShift::evaluateOperation()
{
    auto lhs = m_listOfInputTerminals.at(0)->terminalCurrentData().get();
    auto rhs = m_listOfInputTerminals.at(1)->terminalCurrentData().get();
    if(!lhs || !rhs)
        return ;
    CBitWiseRightShiftVisitor visitor(rhs);
    lhs->accept(visitor);
    sendValueOnAllOutputTerminals( visitor.result() );
}

