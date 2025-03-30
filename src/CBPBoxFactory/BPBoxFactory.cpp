#include "BPBoxFactory.h"

#include "src/COperationBox/MathOperationBoxes/MathMultiplication.h"
#include "src/COperationBox/MathOperationBoxes/MathAddition.h"
#include "src/COperationBox/MathOperationBoxes/MathDivision.h"
#include "src/COperationBox/MathOperationBoxes/MathModulus.h"
#include "src/COperationBox/MathOperationBoxes/MathSubtraction.h"
#include "src/COperationBox/MathOperationBoxes/MathPower.h"
#include "src/COperationBox/MathOperationBoxes/MathAbsolute.h"
#include "src/COperationBox/dataSourceBoxes/TimerSendValSrc.h"
#include "src/COperationBox/dataSinkBoxes/StringOutputSink.h"
#include "src/COperationBox/dataSinkBoxes/CSocketClientSink.h"
#include "src/COperationBox/LogicalOperationBoxes/LogicalAND.h"
#include "src/COperationBox/LogicalOperationBoxes/LogicalOR.h"
#include "src/COperationBox/LogicalOperationBoxes/LogicalNOT.h"
#include "src/COperationBox/BitwiseOperationBoxes/BitWiseAND.h"
#include "src/COperationBox/BitwiseOperationBoxes/BitWiseOR.h"
#include "src/COperationBox/BitwiseOperationBoxes/BitWiseLeftShift.h"
#include "src/COperationBox/BitwiseOperationBoxes/BitWiseRightShift.h"
#include "src/COperationBox/BitwiseOperationBoxes/BitWiseComplement.h"
#include "src/COperationBox/BitwiseOperationBoxes/BitWiseXOR.h"
#include "src/COperationBox/Miscellaneous/ConditionalBranch.h"
#include "src/COperationBox/DataComparisonOperations/DataComparisonEqual.h"
#include "src/COperationBox/DataComparisonOperations/DataComparisonGreater.h"
#include "src/COperationBox/DataComparisonOperations/DataComparisonLess.h"
#include "src/COperationBox/dataSourceBoxes/TCPSocketServerSource.h"
#include "src/COperationBox/dataSourceBoxes/UDPSocketServerSource.h"
#include "src/COperationBox/Miscellaneous/UniversalTypeConvertor.h"
#include "src/COperationBox/dataSinkBoxes/LineSeriesChartBox.h"
#include "src/COperationBox/Miscellaneous/DataCounter.h"
#include "src/COperationBox/dataSourceBoxes/ButtonSource.h"
#include "src/COperationBox/Miscellaneous/StopWatch.h"
#include "src/COperationBox/Miscellaneous/BlueScriptBox.h"
#include "src/COperationBox/Miscellaneous/DelayMakerBox.h"


class CBPBoxFactoryInterface
{
public :
    virtual COperationBox *  make(const int & posX , const int & posY) = 0 ;
};


class CTimerSendValSrcFactory             : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CTimerSendValSrc        ( posX , posY   )                      ;} ; };
class CStringOutputSinkFactory            : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CStringOutputSink       ( posX , posY   )                      ;} ; };
class CTCPSocketClientSinkFactory         : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CSocketClientSink       ( posX , posY , QAbstractSocket::TcpSocket   )           ;} ; };
class CUDPSocketClientSinkFactory         : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CSocketClientSink       ( posX , posY , QAbstractSocket::UdpSocket   )           ;} ; };
class CLogicalANDFactory                  : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CLogicalAND             ( posX , posY   )                      ;} ; };
class CLogicalORFactory                   : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CLogicalOR              ( posX , posY   )                      ;} ; };
class CLogicalNOTFactory                  : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CLogicalNOT             ( posX , posY   )                      ;} ; };
class CBitWiseANDFactory                  : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CBitWiseAND             ( posX , posY   )                      ;} ; };
class CBitWiseORFactory                   : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CBitWiseOR              ( posX , posY   )                      ;} ; };
class CBitWiseLeftShiftFactory            : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CBitWiseLeftShift       ( posX , posY   )                      ;} ; };
class CBitWiseRightShiftFactory           : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CBitWiseRightShift      ( posX , posY   )                      ;} ; };
class CBitWiseComplementFactory           : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CBitWiseComplement      ( posX , posY   )                      ;} ; };
class CBitWiseXORFactory                  : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CBitWiseXOR             ( posX , posY   )                      ;} ; };
class CDataComparisonEqualFactory         : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CDataComparisonEqual    ( posX , posY   )                      ;} ; };
class CDataComparisonGreaterFactory       : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CDataComparisonGreater  ( posX , posY   )                      ;} ; };
class CDataComparisonLessFactory          : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CDataComparisonLess     ( posX , posY   )                      ;} ; };
class CConditionalBranchFactory           : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CConditionalBranch      ( posX , posY   )                      ;} ; };
class CStopWatchFactory                   : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CStopWatch              ( posX , posY   )                      ;} ; };
class CBlueScriptBoxFactory               : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CBlueScriptBox          ( posX , posY   )                      ;} ; };
class CDelayMakerBoxFactory               : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CDelayMakerBox           ( posX , posY   )                      ;} ; };
class CMathMultiplicationFactory          : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CMathMultiplication     ( posX , posY   )                      ;} ; };
class CMathAdditionFactory                : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CMathAddition           ( posX , posY   )                      ;} ; };
class CMathDivisionFactory                : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CMathDivision           ( posX , posY   )                      ;} ; };
class CMathSubtractionFactory             : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CMathSubtraction        ( posX , posY   )                      ;} ; };
class CMathModulusFactory                 : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CMathModulus            ( posX , posY   )                      ;} ; };
class CMathAbsoluteFactory                : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CMathAbsolute           ( posX , posY   )                      ;} ; };
class CMathPowerFactory                   : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CMathPower              ( posX , posY   )                      ;} ; };
class CTCPSocketServerSourceFactory       : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CTCPSocketServerSource  ( posX , posY   )                      ;} ; };
class CUDPSocketServerSourceFactory       : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CUDPSocketServerSource  ( posX , posY   )                      ;} ; };
class CButtonSourceFactory                : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CButtonSource           ( posX , posY   )                      ;} ; };
class CUniversalTypeConvertorFactory      : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CUniversalTypeConvertor ( posX , posY   )                      ;} ; };
class CLineSeriesChartBoxFactory          : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CLineSeriesChartBox     ( posX , posY   )                      ;} ; };
class CDataCounterFactory                 : public CBPBoxFactoryInterface { public :  virtual COperationBox *  make( const int & posX , const int & posY ) override { return new CDataCounter            ( posX , posY   )                      ;} ; };




CBPBoxFactory::CBPBoxFactory()
{
    m_mapOfBPBoxToFactory[ CTimerSendValSrc        ::getUniqueName()          ] = new CTimerSendValSrcFactory        () ;
    m_mapOfBPBoxToFactory[ CTCPSocketServerSource  ::getUniqueName()          ] = new CTCPSocketServerSourceFactory  () ;
    m_mapOfBPBoxToFactory[ CUDPSocketServerSource  ::getUniqueName()          ] = new CUDPSocketServerSourceFactory  () ;
    m_mapOfBPBoxToFactory[ CButtonSource           ::getUniqueName()          ] = new CButtonSourceFactory           () ;
    m_mapOfBPBoxToFactory[ CLineSeriesChartBox     ::getUniqueName()          ] = new CLineSeriesChartBoxFactory     () ;
    m_mapOfBPBoxToFactory[ CStringOutputSink       ::getUniqueName()          ] = new CStringOutputSinkFactory       () ;
    m_mapOfBPBoxToFactory[ "TCP Client"                                       ] = new CTCPSocketClientSinkFactory    () ;
    m_mapOfBPBoxToFactory[ "UDP Client"                                       ] = new CUDPSocketClientSinkFactory    () ;
    m_mapOfBPBoxToFactory[ CDataCounter            ::getUniqueName()          ] = new CDataCounterFactory            () ;
    m_mapOfBPBoxToFactory[ CUniversalTypeConvertor ::getUniqueName()          ] = new CUniversalTypeConvertorFactory () ;
    m_mapOfBPBoxToFactory[ CConditionalBranch      ::getUniqueName()          ] = new CConditionalBranchFactory      () ;
    m_mapOfBPBoxToFactory[ CStopWatch              ::getUniqueName()          ] = new CStopWatchFactory              () ;
    m_mapOfBPBoxToFactory[ CBlueScriptBox          ::getUniqueName()          ] = new CBlueScriptBoxFactory          () ;
    m_mapOfBPBoxToFactory[ CDelayMakerBox          ::getUniqueName()          ] = new CDelayMakerBoxFactory          () ;
    m_mapOfBPBoxToFactory[ CLogicalAND             ::getUniqueName()          ] = new CLogicalANDFactory             () ;
    m_mapOfBPBoxToFactory[ CLogicalOR              ::getUniqueName()          ] = new CLogicalORFactory              () ;
    m_mapOfBPBoxToFactory[ CLogicalNOT             ::getUniqueName()          ] = new CLogicalNOTFactory             () ;
    m_mapOfBPBoxToFactory[ CBitWiseAND             ::getUniqueName()          ] = new CBitWiseANDFactory             () ;
    m_mapOfBPBoxToFactory[ CBitWiseOR              ::getUniqueName()          ] = new CBitWiseORFactory              () ;
    m_mapOfBPBoxToFactory[ CBitWiseLeftShift       ::getUniqueName()          ] = new CBitWiseLeftShiftFactory       () ;
    m_mapOfBPBoxToFactory[ CBitWiseRightShift      ::getUniqueName()          ] = new CBitWiseRightShiftFactory      () ;
    m_mapOfBPBoxToFactory[ CBitWiseComplement      ::getUniqueName()          ] = new CBitWiseComplementFactory      () ;
    m_mapOfBPBoxToFactory[ CBitWiseXOR             ::getUniqueName()          ] = new CBitWiseXORFactory             () ;
    m_mapOfBPBoxToFactory[ CDataComparisonEqual    ::getUniqueName()          ] = new CDataComparisonEqualFactory    () ;
    m_mapOfBPBoxToFactory[ CDataComparisonGreater  ::getUniqueName()          ] = new CDataComparisonGreaterFactory  () ;
    m_mapOfBPBoxToFactory[ CDataComparisonLess     ::getUniqueName()          ] = new CDataComparisonLessFactory     () ;
    m_mapOfBPBoxToFactory[ CMathMultiplication     ::getUniqueName()          ] = new CMathMultiplicationFactory     () ;
    m_mapOfBPBoxToFactory[ CMathAddition           ::getUniqueName()          ] = new CMathAdditionFactory           () ;
    m_mapOfBPBoxToFactory[ CMathDivision           ::getUniqueName()          ] = new CMathDivisionFactory           () ;
    m_mapOfBPBoxToFactory[ CMathSubtraction        ::getUniqueName()          ] = new CMathSubtractionFactory        () ;
    m_mapOfBPBoxToFactory[ CMathModulus            ::getUniqueName()          ] = new CMathModulusFactory            () ;
    m_mapOfBPBoxToFactory[ CMathAbsolute           ::getUniqueName()          ] = new CMathAbsoluteFactory           () ;
    m_mapOfBPBoxToFactory[ CMathPower              ::getUniqueName()          ] = new CMathPowerFactory              () ;


}

CBPBoxFactory* CBPBoxFactory::getInstance()
{
    static auto pInstance =  std::unique_ptr<CBPBoxFactory> (new CBPBoxFactory());
    return  pInstance.get();
}



COperationBox *CBPBoxFactory::createBPBoxInstance(const QString & boxName , const int & posX , const int & posY )
{
    if( m_mapOfBPBoxToFactory.contains( boxName ) == false ){
        DEBUG_MSG_PRINT << " BPBox Type Doesnt Exist !! "<< boxName ;
        return nullptr ;
    }
    return m_mapOfBPBoxToFactory[boxName]->make(posX, posY) ;
}





QList<COperationBox *> CBPBoxFactory::getListOfAllBPBoxes()
{
    static QList<COperationBox *> sListOfAllBPBoxes {}; // static list of all boxes

    if(sListOfAllBPBoxes.length() )
        return sListOfAllBPBoxes;

    auto pFactory = CBPBoxFactory::getInstance() ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CTimerSendValSrc        ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CTCPSocketServerSource  ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CUDPSocketServerSource  ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CButtonSource           ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CLineSeriesChartBox     ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CStringOutputSink       ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  "UDP Client"                              , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  "TCP Client"                              , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CDataCounter            ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CUniversalTypeConvertor ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CConditionalBranch      ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CStopWatch              ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CBlueScriptBox          ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CDelayMakerBox          ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CLogicalAND             ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CLogicalOR              ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CLogicalNOT             ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CBitWiseAND             ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CBitWiseOR              ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CBitWiseLeftShift       ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CBitWiseRightShift      ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CBitWiseComplement      ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CBitWiseXOR             ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CDataComparisonEqual    ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CDataComparisonGreater  ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CDataComparisonLess     ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CMathMultiplication     ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CMathAddition           ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CMathDivision           ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CMathSubtraction        ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CMathModulus            ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CMathAbsolute           ::getUniqueName() , 600 , 100 )) ;
    sListOfAllBPBoxes.push_back( pFactory->createBPBoxInstance(  CMathPower              ::getUniqueName() , 600 , 100 )) ;

    return sListOfAllBPBoxes;
}

QList<COperationBox *> CBPBoxFactory::findMatchingNodesWithStringQuery(const QString &query)
{
    auto listOfAllBoxes = getListOfAllBPBoxes() ;
    QList<COperationBox *>  result ;
    for(auto pBox : listOfAllBoxes ){
        if(pBox->blueBox_keyWords().contains(query , Qt::CaseInsensitive  )){
            result.push_back(pBox);
        }
    }
    return result;
}






