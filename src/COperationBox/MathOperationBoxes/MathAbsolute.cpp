#include "MathAbsolute.h"


#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "../../CRawValueBase/RawValueBase.h"



CMathAbsolute::CMathAbsolute ( int newBlueBox_xPos, int newBlueBox_yPos , QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth , blueBoxHeight - 20  , parent }
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigPictureOperator ;
    m_blueBox_HeadColor = QColor(148, 0, 255);
    m_blueBox_HeaderIcon = "qrc:/Images/absolute.png";
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Input");

    m_listOfInputTerminals.push_back(inputNode1 );

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("out");
    m_listOfOutputTerminals.push_back( outPutNode );

    m_blueBox_keyWords = "Math Abstract | |";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_MathOperation ;
}



void CMathAbsolute::evaluateOperation()
{
    auto pCurrentData = m_listOfInputTerminals.at(0)->terminalCurrentData().get() ;
    if(!pCurrentData)
        return ;

    using recFuncType = std::function<void ( QList<std::shared_ptr<CRawValueBase>> &, CRawValueBase * )> ;
    recFuncType recursiveInsertor;
    recursiveInsertor = [&]( QList<std::shared_ptr<CRawValueBase>> & listOfVals ,  CRawValueBase * valToFindAbs){
        if(!valToFindAbs)
            return ;
        if (auto* pVal = dynamic_cast<CValue_int*>(valToFindAbs)) {
           listOfVals.push_back( std::make_shared<CValue_int>( abs(pVal->value()) ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(valToFindAbs)) {
            listOfVals.push_back(  std::make_shared<CValue_double>(abs( pVal->value())));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(valToFindAbs)) {
            listOfVals.push_back(  std::make_shared<CValue_bool>(pVal->value()));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(valToFindAbs)) {
            bool ok = false ;
            pVal->value().toLongLong(&ok);
            if(ok)
                listOfVals.push_back(  std::make_shared<CValue_int>(abs(pVal->value().toLongLong())));
            else
                listOfVals.push_back(  std::make_shared<CValue_int>(pVal->value().length()));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(valToFindAbs)) {
            QList<std::shared_ptr<CRawValueBase>> innerListOfRawVals ;
            for(const auto & inIter : pVal->value()){
                recursiveInsertor(innerListOfRawVals , inIter.get());
            }
            listOfVals.push_back( std::make_shared<CValue_array>( std::move( innerListOfRawVals ) ));
        }
    };



    QList<std::shared_ptr<CRawValueBase>> listOfRawVals ;
    if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentData)) {
        for(const auto & iter : pVal->value()){
            recursiveInsertor( listOfRawVals , iter.get());
        }
        sendValueOnAllOutputTerminals( std::make_shared<CValue_array>( std::move( listOfRawVals )) );
    }else{
        recursiveInsertor( listOfRawVals , pCurrentData );
        ASSERTWITHINFO(listOfRawVals.length() == 1 );
        sendValueOnAllOutputTerminals( listOfRawVals.at(0) );
    }

}
