#include "MathPower.h"

#include <cmath>

#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "../../CRawValueBase/RawValueBase.h"


class  CMathPowerVisitor : public CValueVisitor {
public:

    explicit  CMathPowerVisitor(CRawValueBase* rhs) : mp_rhs(rhs) {}
    std::shared_ptr<CRawValueBase>  result()const { return m_result ;}

    void visit(const CValue_int& lhs) override {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs)) {
            m_result = std::make_shared<CValue_int>(std::pow( lhs.value() , pVal->value()));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs)) {
            m_result = std::make_shared<CValue_double>(std::pow(lhs.value() , pVal->value()));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs)) {
            m_result = std::make_shared<CValue_int>(std::pow(lhs.value() , pVal->value()));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs)) {
            m_result = std::make_shared<CValue_string>("");
        }
    }

    void visit(const CValue_double& lhs) override {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs)) {
            m_result = std::make_shared<CValue_double>(std::pow(lhs.value() , pVal->value()));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs)) {
            m_result = std::make_shared<CValue_double>(std::pow(lhs.value() , pVal->value()));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs)) {
            m_result = std::make_shared<CValue_double>(std::pow(lhs.value() , pVal->value()));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs)) {
            m_result = std::make_shared<CValue_string>("");
        }
    }

    void visit(const CValue_string& lhs) override {
        Q_UNUSED(lhs)
        m_result = std::make_shared<CValue_string>("");
    }

    void visit(const CValue_bool& lhs) override {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs)) {
            m_result = std::make_shared<CValue_int>(std::pow(lhs.value() , pVal->value()));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs)) {
            m_result = std::make_shared<CValue_double>(std::pow(lhs.value() , pVal->value()));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs)) {
            m_result = std::make_shared<CValue_int>(std::pow(lhs.value() , pVal->value()));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs)) {
            m_result = std::make_shared<CValue_string>("");
        }
    }

    void visit(const CValue_array& lhs) override {
        Q_UNUSED(lhs)
    }

    void visit(const CValue_map& lhs) override {
        Q_UNUSED(lhs)
    }

private:
    std::shared_ptr<CRawValueBase> m_result{nullptr};
    CRawValueBase* mp_rhs = nullptr;  // The second operand (factor)
};




CMathPower::CMathPower ( int newBlueBox_xPos, int newBlueBox_yPos , QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth , blueBoxHeight , parent }
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigPictureOperator ;
    m_blueBox_HeaderIcon = "qrc:/Images/power.png";
    m_blueBox_HeadColor = QColor(120 , 50 , 110 ) ;
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("n");
    auto inputNode2 = new CInputTerminal(1, this);
    inputNode2->setTerminalName("X");
    m_listOfInputTerminals.push_back(inputNode1 );
    m_listOfInputTerminals.push_back(inputNode2 );

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("Out");
    m_listOfOutputTerminals.push_back( outPutNode );

    m_blueBox_keyWords = "Math Power ^";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_MathOperation ;
}





void CMathPower::evaluateOperation()
{
    auto lhs = m_listOfInputTerminals.at(0)->terminalCurrentData().get();
    auto rhs = m_listOfInputTerminals.at(1)->terminalCurrentData().get();
    if(!lhs || !rhs)
        return ;
     CMathPowerVisitor visitor(rhs);
    lhs->accept(visitor);
    sendValueOnAllOutputTerminals( visitor.result() );


}

