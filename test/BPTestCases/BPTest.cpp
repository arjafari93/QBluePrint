
#include <memory>

#include "gtest/gtest.h"

#include "src/CBPBoxFactory/BPBoxFactory.h"
#include "src/COperationBox/OperationBox.h"
#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "src/CRawValueBase/RawValueBase.h"
using namespace ::testing;

TEST( BPOperationBoxTests, ArrayLenTest )
{
    auto pArrLen = CBPBoxFactory::getInstance()->createBPBoxInstance("Array Length" , 0 , 0 );
    QList<std::shared_ptr<CRawValueBase>> valueToBeSentlist ;

    valueToBeSentlist.push_back(std::make_shared<CValue_int>(12));
    valueToBeSentlist.push_back(std::make_shared<CValue_double>(12.5));
    valueToBeSentlist.push_back(std::make_shared<CValue_string>("test string in array"));
    valueToBeSentlist.push_back(std::make_shared<CValue_bool>(false));

    pArrLen->getListOfInputTerminals().at(0)->receivedValueFromFlowLine( std::make_shared<CValue_array>( valueToBeSentlist) );
    auto len = pArrLen->getListOfOutputTerminals().at(0)->terminalCurrentData();
    EXPECT_EQ(4 ,  dynamic_cast<CValue_int*>(len.get())->value() );
    delete pArrLen;
}

