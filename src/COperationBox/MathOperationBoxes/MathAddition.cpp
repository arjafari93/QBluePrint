#include "MathAddition.h"



#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "../../CRawValueBase/RawValueBase.h"

inline const static int blueBoxWidth  = 220 ;
inline const static int blueBoxHeight = 120 ;



class CMathAdditionVisitor : public CValueVisitor {
public:

    explicit CMathAdditionVisitor(CRawValueBase* rhs) : mp_rhs(rhs) {}
    std::shared_ptr<CRawValueBase>  result()const { return m_result ;}

    void visit(const CValue_int& lhs) override {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs)) {
            m_result = std::make_shared<CValue_int>(lhs.value() + pVal->value());
        } else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs)) {
            m_result = std::make_shared<CValue_double>(lhs.value() + pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs)) {
            m_result = std::make_shared<CValue_int>(lhs.value() + (long long)pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs)) {
            m_result = std::make_shared<CValue_string>( QString::number(lhs.value()) + pVal->value() );
        }if (auto* pVal = dynamic_cast<CValue_list*>(mp_rhs)) {
            m_result = *pVal + lhs.value() ;
        }
    }

    void visit(const CValue_double& lhs) override {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs)) {
            m_result = std::make_shared<CValue_double>(lhs.value() + pVal->value());
        } else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs)) {
            m_result = std::make_shared<CValue_double>(lhs.value() + pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs)) {
            m_result = std::make_shared<CValue_double>(lhs.value() + pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs)) {
            m_result = std::make_shared<CValue_string>( QString::number(lhs.value(), 'f' , MAX_DOUBLE_PRECISION) + pVal->value() );
        }if (auto* pVal = dynamic_cast<CValue_list*>(mp_rhs)) {
            m_result = *pVal + lhs.value() ;
        }
    }

    void visit(const CValue_string& lhs) override {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs)) {
            m_result = std::make_shared<CValue_string>(lhs.value() + QString::number(pVal->value()));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs)) {
            m_result = std::make_shared<CValue_string>(lhs.value() + QString::number(pVal->value(), 'f' , MAX_DOUBLE_PRECISION));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs)) {
            m_result = std::make_shared<CValue_string>(lhs.value() + QString::number(pVal->value()));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs)) {
            m_result = std::make_shared<CValue_string>(lhs.value() + pVal->value());
        }if (auto* pVal = dynamic_cast<CValue_list*>(mp_rhs)) {
            m_result = lhs.value() + *pVal   ;
        }
    }

    void visit(const CValue_bool& lhs) override {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs)) {
            m_result = std::make_shared<CValue_int>((long long)lhs.value() + pVal->value());
        } else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs)) {
            m_result = std::make_shared<CValue_double>(lhs.value() +pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs)) {
            m_result = std::make_shared<CValue_bool>(lhs.value() + pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs)) {
            m_result = std::make_shared<CValue_string>(QString::number(lhs.value()) + pVal->value());
        }if (auto* pVal = dynamic_cast<CValue_list*>(mp_rhs)) {
            m_result =  *pVal + lhs.value() ;
        }
    }

    void visit(const CValue_list& lhs) override {
        if (auto* pVal = dynamic_cast<CValue_int*>(mp_rhs)) {
            m_result =  lhs + pVal->value() ;
        } else if (auto* pVal = dynamic_cast<CValue_double*>(mp_rhs)) {
            m_result = lhs + pVal->value();
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(mp_rhs)) {
            m_result =lhs + pVal->value();
        }else if (auto* pVal = dynamic_cast<CValue_string*>(mp_rhs)) {
            m_result = lhs  + pVal->value() ;
        }if (auto* pVal = dynamic_cast<CValue_list*>(mp_rhs)) {
            m_result = lhs +  *pVal  ;
        }
    }

    void visit(const CValue_map& lhs) override {
        Q_UNUSED(lhs)
    }

private:
    std::shared_ptr<CRawValueBase> m_result{nullptr};
    CRawValueBase* mp_rhs = nullptr;  // The second operand (factor)
};



CMathAddition::CMathAddition ( int newBlueBox_xPos, int newBlueBox_yPos , QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth , blueBoxHeight , parent }
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigPictureOperator ;
    m_blueBox_HeadColor = QColor(7 , 102 , 173 ) ;
    m_blueBox_HeaderIcon = "qrc:/Images/plus.png";
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Left");
    auto inputNode2 = new CInputTerminal(1, this);
    inputNode2->setTerminalName("Right");
    m_listOfInputTerminals.push_back(inputNode1 );
    m_listOfInputTerminals.push_back(inputNode2 );

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("Out");
    m_listOfOutputTerminals.push_back( outPutNode );

    m_blueBox_keyWords = "Math Addition, plus +";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_MathOperation ;
}





void CMathAddition::evaluateOperation()
{
    auto lhs = m_listOfInputTerminals.at(0)->terminalCurrentData().get();
    auto rhs = m_listOfInputTerminals.at(1)->terminalCurrentData().get();
    if(!lhs || !rhs)
        return ;
    CMathAdditionVisitor visitor(rhs);
    lhs->accept(visitor);
    sendValueOnAllOutputTerminals( visitor.result() );
}


