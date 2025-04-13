#include "UniversalTypeConvertor.h"


#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "../../CRawValueBase/RawValueBase.h"


CUniversalTypeConvertor::CUniversalTypeConvertor ( int newBlueBox_xPos, int newBlueBox_yPos , QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth , blueBoxHeight + 40  , parent }
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_TypeConvrtrOperator;
    m_blueBox_HeaderIcon = "qrc:/Images/typeConvertor.png";
    m_blueBox_HeadColor = QColor(255 , 45 , 240 ) ;
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Input");
    m_listOfInputTerminals.push_back(inputNode1 );

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("Out");
    m_listOfOutputTerminals.push_back( outPutNode );

    m_blueBox_keyWords = "convertor type cast universal";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_DataComparison ;
}


void CUniversalTypeConvertor::evaluateOperation()
{
    auto pCurrentData = m_listOfInputTerminals.at(0)->terminalCurrentData().get() ;
    std::shared_ptr<CRawValueBase> result{nullptr};

    if(m_selectedOutputType == "int"){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentData)) {
            result = std::make_shared<CValue_int>( pVal->value() );
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentData)) {
            result = std::make_shared<CValue_int>((long long)pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentData)) {
            result = std::make_shared<CValue_int>((long long)pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentData)) {
            result = std::make_shared<CValue_int>(  pVal->value().toLongLong() );
        }
    }else if(m_selectedOutputType == "double"){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentData)) {
            result = std::make_shared<CValue_double>( (long double)pVal->value() );
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentData)) {
            result = std::make_shared<CValue_double>((long double)pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentData)) {
            result = std::make_shared<CValue_double>((long double)pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentData)) {
            result = std::make_shared<CValue_double>(  pVal->value().toDouble() );
        }
    }else if(m_selectedOutputType == "bool"){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentData)) {
            result = std::make_shared<CValue_bool>( (bool)pVal->value() );
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentData)) {
            result = std::make_shared<CValue_bool>((long double)pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentData)) {
            result = std::make_shared<CValue_bool>((long double)pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentData)) {
            bool res = false ;
            QString inpt = pVal->value();
            if(inpt == "true" || inpt == "True" || inpt == "TRUE" )
                res = true ;
            else if(inpt == "false" || inpt == "False" || inpt == "FALSE" )
                res = false ;
            else
                res = (bool)pVal->value().toDouble();
            result = std::make_shared<CValue_bool>(  res );
        }
    }else if(m_selectedOutputType == "string"){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentData)) {
            result = std::make_shared<CValue_string>( QString::number( pVal->value() ) );
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentData)) {
            result = std::make_shared<CValue_string>( QString::number( pVal->value() , 'f' , MAX_DOUBLE_PRECISION ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentData)) {
            result = std::make_shared<CValue_string>( QString::number((long long)pVal->value()));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentData)) {
            result = std::make_shared<CValue_string>(  pVal->value() );
        }
    }else{
        DEBUG_MSG_PRINT << "unknown data type is selected " << m_selectedOutputType ;
        return ;
    }

    sendValueOnAllOutputTerminals( result );

}



const QString &CUniversalTypeConvertor::selectedOutputType() const
{
    return m_selectedOutputType;
}

void CUniversalTypeConvertor::setSelectedOutputType(const QString &newSelectedOutputType)
{
    if (m_selectedOutputType == newSelectedOutputType)
        return;
    m_selectedOutputType = newSelectedOutputType;
    emit selectedOutputTypeChanged();
}


