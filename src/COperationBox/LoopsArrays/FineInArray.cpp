#include "FineInArray.h"

#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "../../CRawValueBase/RawValueBase.h"
#include <memory>

inline const static int blueBoxWidth  = 220 ;
inline const static int blueBoxHeight = 110 ;


CFineInArray::CFineInArray ( int newBlueBox_xPos, int newBlueBox_yPos , QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth , blueBoxHeight , parent }
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigPictureOperator ;
    m_blueBox_HeadColor = QColor(170, 220, 150);
    m_blueBox_HeaderIcon = "qrc:/Images/arrayFind.png";
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Input");
    inputNode1->setTerminalCurrentData( std::make_shared<CValue_array>() );
    m_listOfInputTerminals.push_back(inputNode1 );

    auto inputNode2 = new CInputTerminal(1, this);
    inputNode2->setTerminalName("Elmnt");
    m_listOfInputTerminals.push_back(inputNode2 );

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("Index");
    m_listOfOutputTerminals.push_back( outPutNode );

    m_blueBox_keyWords = "array element find index search";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_LoopsAndArrays;
}

CFineInArray::~CFineInArray()
{

}



void CFineInArray::evaluateOperation()
{
    auto pArray = m_listOfInputTerminals.at(0)->terminalCurrentData().get() ;
    auto pElmnt = m_listOfInputTerminals.at(1)->terminalCurrentData().get() ;
    if( !pArray || !pElmnt)
        return ;

    int indexInArr = -1 ; ;
    if (auto* pElmntVal = dynamic_cast<CValue_int*>(pElmnt)) {
        indexInArr = pElmntVal->value() ;
    } else if (auto* pElmntVal = dynamic_cast<CValue_double*>(pElmnt)) {
        indexInArr =  (long long)pElmntVal->value()  ;
    }else if (auto* pElmntVal = dynamic_cast<CValue_string*>(pElmnt)) {
        indexInArr = pElmntVal->value().toLongLong() ;
    }else if (auto* pElmntVal = dynamic_cast<CValue_bool*>(pElmnt)) {
        indexInArr = (long long)pElmntVal->value();
    }else if (auto* pElmntVal = dynamic_cast<CValue_array*>(pElmnt)) {
        indexInArr =  pElmntVal->convertToString().toLongLong() ;
    }
    if(indexInArr < 0 )
        return ;

    if (auto* pVal = dynamic_cast<CValue_int*>(pArray)) {
        if (auto* pElmntVal = dynamic_cast<CValue_int*>(pElmnt)){
            if(pElmntVal->value() == pVal->value())
                m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_int>(0) );
            else
                m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_int>(-1) );
            return ;
        }
    } else if (auto* pVal = dynamic_cast<CValue_double*>(pArray)) {
        if (auto* pElmntVal = dynamic_cast<CValue_double*>(pElmnt)){
            if( qFuzzyCompare( (double)pElmntVal->value() , (double)pVal->value()))
                m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_int>(0) );
            else
                m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_int>(-1) );
            return ;
        }
    }else if (auto* pVal = dynamic_cast<CValue_string*>(pArray)) {
        if (auto* pElmntVal = dynamic_cast<CValue_string*>(pElmnt)){
            m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_int>(pVal->value().indexOf( pElmntVal->value())) );
            return ;
        }
    }else if (auto* pVal = dynamic_cast<CValue_bool*>(pArray)) {
        if (auto* pElmntVal = dynamic_cast<CValue_bool*>(pElmnt)){
            if(pElmntVal->value() == pVal->value())
                m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_int>(0) );
            else
                m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_int>(-1) );
            return ;
        }
    }else if (auto* pVal = dynamic_cast<CValue_array*>(pArray)) {
        int index =  pVal->findIndexOfElementInArray(m_listOfInputTerminals.at(1)->terminalCurrentData());
        ASSERTWITHINFO( index < pVal->value().length() );
        m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_int>(index) );
        return ;
    }else {
        DEBUG_MSG_PRINT << "unknown type ";
    }

    m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_int>(-1) );


}

