#include "BPBoxFactory.h"

#include "BitWiseAND.h"
#include "BitWiseComplement.h"
#include "BitWiseLeftShift.h"
#include "BitWiseOR.h"
#include "BitWiseRightShift.h"
#include "BitWiseXOR.h"
#include "DataComparisonEqual.h"
#include "DataComparisonGreater.h"
#include "DataComparisonLess.h"
#include "JsonParser.h"
#include "LogicalAND.h"
#include "LogicalNOT.h"
#include "LogicalOR.h"
#include "ArrayLength.h"
#include "FineInArray.h"
#include "ForEachLoop.h"
#include "GetByIndex.h"
#include "ParseIntoArray.h"
#include "MathAbsolute.h"
#include "MathAddition.h"
#include "MathDivision.h"
#include "MathModulo.h"
#include "MathMultiplication.h"
#include "MathPower.h"
#include "MathSubtraction.h"
#include "BlueScriptBox.h"
#include "ConditionalBranch.h"
#include "DataCounter.h"
#include "DelayMakerBox.h"
#include "StopWatch.h"
#include "UniversalTypeConvertor.h"
#include "CSocketClientSink.h"
#include "FileSink.h"
#include "LineSeriesChartBox.h"
#include "StringOutputSink.h"
#include "ButtonSource.h"
#include "FileSource.h"
#include "HTTPGetter.h"
#include "HTTPPoster.h"
#include "TCPSocketServerSource.h"
#include "TimerSendValSrc.h"
#include "UDPSocketServerSource.h"

class CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) = 0;
};

class CTimerSendValSrcFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CTimerSendValSrc(posX, posY); };
};
class CStringOutputSinkFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CStringOutputSink(posX, posY); };
};
class CFileSinkFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CFileSink(posX, posY); };
};
class CTCPSocketClientSinkFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CSocketClientSink(posX, posY, QAbstractSocket::TcpSocket); };
};
class CUDPSocketClientSinkFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CSocketClientSink(posX, posY, QAbstractSocket::UdpSocket); };
};
class CLogicalANDFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CLogicalAND(posX, posY); };
};
class CLogicalORFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CLogicalOR(posX, posY); };
};
class CLogicalNOTFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CLogicalNOT(posX, posY); };
};
class CBitWiseANDFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CBitWiseAND(posX, posY); };
};
class CBitWiseORFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CBitWiseOR(posX, posY); };
};
class CBitWiseLeftShiftFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CBitWiseLeftShift(posX, posY); };
};
class CBitWiseRightShiftFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CBitWiseRightShift(posX, posY); };
};
class CBitWiseComplementFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CBitWiseComplement(posX, posY); };
};
class CBitWiseXORFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CBitWiseXOR(posX, posY); };
};
class CDataComparisonEqualFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CDataComparisonEqual(posX, posY); };
};
class CDataComparisonGreaterFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CDataComparisonGreater(posX, posY); };
};
class CDataComparisonLessFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CDataComparisonLess(posX, posY); };
};
class CJsonParserFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CJsonParser(posX, posY); };
};
class CParseIntoArrayFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CParseIntoArray(posX, posY); };
};
class CConditionalBranchFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CConditionalBranch(posX, posY); };
};
class CStopWatchFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CStopWatch(posX, posY); };
};
class CBlueScriptBoxFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CBlueScriptBox(posX, posY); };
};
class CDelayMakerBoxFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CDelayMakerBox(posX, posY); };
};
class CForEachLoopFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CForEachLoop(posX, posY); };
};
class CGetByIndexFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CGetByIndex(posX, posY); };
};
class CArrayLengthFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CArrayLength(posX, posY); };
};
class CFineInArrayFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CFineInArray(posX, posY); };
};
class CMathMultiplicationFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CMathMultiplication(posX, posY); };
};
class CMathAdditionFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CMathAddition(posX, posY); };
};
class CMathDivisionFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CMathDivision(posX, posY); };
};
class CMathSubtractionFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CMathSubtraction(posX, posY); };
};
class CMathModuloFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CMathModulo(posX, posY); };
};
class CMathAbsoluteFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CMathAbsolute(posX, posY); };
};
class CMathPowerFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CMathPower(posX, posY); };
};
class CTCPSocketServerSourceFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CTCPSocketServerSource(posX, posY); };
};
class CUDPSocketServerSourceFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CUDPSocketServerSource(posX, posY); };
};
class CButtonSourceFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CButtonSource(posX, posY); };
};
class CHTTPGetterFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CHTTPGetter(posX, posY); };
};
class CHTTPPosterFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CHTTPPoster(posX, posY); };
};
class CFileSourceFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CFileSource(posX, posY); };
};
class CUniversalTypeConvertorFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CUniversalTypeConvertor(posX, posY); };
};
class CLineSeriesChartBoxFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CLineSeriesChartBox(posX, posY); };
};
class CDataCounterFactory : public CBPBoxFactoryInterface
{
  public:
    virtual COperationBox* make(const int& posX, const int& posY) override { return new CDataCounter(posX, posY); };
};

CBPBoxFactory::CBPBoxFactory()
{
    m_mapOfBPBoxToFactory[CTimerSendValSrc ::getUniqueName()] = new CTimerSendValSrcFactory();
    m_mapOfBPBoxToFactory[CTCPSocketServerSource ::getUniqueName()] = new CTCPSocketServerSourceFactory();
    m_mapOfBPBoxToFactory[CUDPSocketServerSource ::getUniqueName()] = new CUDPSocketServerSourceFactory();
    m_mapOfBPBoxToFactory[CButtonSource ::getUniqueName()] = new CButtonSourceFactory();
    m_mapOfBPBoxToFactory[CHTTPGetter ::getUniqueName()] = new CHTTPGetterFactory();
    m_mapOfBPBoxToFactory[CHTTPPoster ::getUniqueName()] = new CHTTPPosterFactory();
    m_mapOfBPBoxToFactory[CFileSource ::getUniqueName()] = new CFileSourceFactory();
    m_mapOfBPBoxToFactory[CLineSeriesChartBox ::getUniqueName()] = new CLineSeriesChartBoxFactory();
    m_mapOfBPBoxToFactory[CStringOutputSink ::getUniqueName()] = new CStringOutputSinkFactory();
    m_mapOfBPBoxToFactory[CFileSink ::getUniqueName()] = new CFileSinkFactory();
    m_mapOfBPBoxToFactory["TCP Client"] = new CTCPSocketClientSinkFactory();
    m_mapOfBPBoxToFactory["UDP Client"] = new CUDPSocketClientSinkFactory();
    m_mapOfBPBoxToFactory[CDataCounter ::getUniqueName()] = new CDataCounterFactory();
    m_mapOfBPBoxToFactory[CUniversalTypeConvertor ::getUniqueName()] = new CUniversalTypeConvertorFactory();
    m_mapOfBPBoxToFactory[CConditionalBranch ::getUniqueName()] = new CConditionalBranchFactory();
    m_mapOfBPBoxToFactory[CStopWatch ::getUniqueName()] = new CStopWatchFactory();
    m_mapOfBPBoxToFactory[CBlueScriptBox ::getUniqueName()] = new CBlueScriptBoxFactory();
    m_mapOfBPBoxToFactory[CDelayMakerBox ::getUniqueName()] = new CDelayMakerBoxFactory();
    m_mapOfBPBoxToFactory[CForEachLoop ::getUniqueName()] = new CForEachLoopFactory();
    m_mapOfBPBoxToFactory[CGetByIndex ::getUniqueName()] = new CGetByIndexFactory();
    m_mapOfBPBoxToFactory[CArrayLength ::getUniqueName()] = new CArrayLengthFactory();
    m_mapOfBPBoxToFactory[CFineInArray ::getUniqueName()] = new CFineInArrayFactory();
    m_mapOfBPBoxToFactory[CLogicalAND ::getUniqueName()] = new CLogicalANDFactory();
    m_mapOfBPBoxToFactory[CLogicalOR ::getUniqueName()] = new CLogicalORFactory();
    m_mapOfBPBoxToFactory[CLogicalNOT ::getUniqueName()] = new CLogicalNOTFactory();
    m_mapOfBPBoxToFactory[CBitWiseAND ::getUniqueName()] = new CBitWiseANDFactory();
    m_mapOfBPBoxToFactory[CBitWiseOR ::getUniqueName()] = new CBitWiseORFactory();
    m_mapOfBPBoxToFactory[CBitWiseLeftShift ::getUniqueName()] = new CBitWiseLeftShiftFactory();
    m_mapOfBPBoxToFactory[CBitWiseRightShift ::getUniqueName()] = new CBitWiseRightShiftFactory();
    m_mapOfBPBoxToFactory[CBitWiseComplement ::getUniqueName()] = new CBitWiseComplementFactory();
    m_mapOfBPBoxToFactory[CBitWiseXOR ::getUniqueName()] = new CBitWiseXORFactory();
    m_mapOfBPBoxToFactory[CDataComparisonEqual ::getUniqueName()] = new CDataComparisonEqualFactory();
    m_mapOfBPBoxToFactory[CDataComparisonGreater ::getUniqueName()] = new CDataComparisonGreaterFactory();
    m_mapOfBPBoxToFactory[CDataComparisonLess ::getUniqueName()] = new CDataComparisonLessFactory();
    m_mapOfBPBoxToFactory[CJsonParser ::getUniqueName()] = new CJsonParserFactory();
    m_mapOfBPBoxToFactory[CParseIntoArray ::getUniqueName()] = new CParseIntoArrayFactory();
    m_mapOfBPBoxToFactory[CMathMultiplication ::getUniqueName()] = new CMathMultiplicationFactory();
    m_mapOfBPBoxToFactory[CMathAddition ::getUniqueName()] = new CMathAdditionFactory();
    m_mapOfBPBoxToFactory[CMathDivision ::getUniqueName()] = new CMathDivisionFactory();
    m_mapOfBPBoxToFactory[CMathSubtraction ::getUniqueName()] = new CMathSubtractionFactory();
    m_mapOfBPBoxToFactory[CMathModulo ::getUniqueName()] = new CMathModuloFactory();
    m_mapOfBPBoxToFactory[CMathAbsolute ::getUniqueName()] = new CMathAbsoluteFactory();
    m_mapOfBPBoxToFactory[CMathPower ::getUniqueName()] = new CMathPowerFactory();
}

CBPBoxFactory* CBPBoxFactory::getInstance()
{
    static auto pInstance = std::unique_ptr<CBPBoxFactory>(new CBPBoxFactory());
    return pInstance.get();
}

COperationBox* CBPBoxFactory::createBPBoxInstance(const QString& boxName, const int& posX, const int& posY)
{
    if (m_mapOfBPBoxToFactory.contains(boxName) == false)
    {
        DEBUG_MSG_PRINT << " BPBox Type Doesnt Exist !! " << boxName;
        return nullptr;
    }
    return m_mapOfBPBoxToFactory[boxName]->make(posX, posY);
}

QList<COperationBox*> CBPBoxFactory::getListOfAllBPBoxes()
{
    static QList<COperationBox*> sListOfAllBPBoxes{}; // static list of all boxes

    if (sListOfAllBPBoxes.length())
        return sListOfAllBPBoxes;

    auto pFactory = CBPBoxFactory::getInstance();
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CTimerSendValSrc ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CTCPSocketServerSource ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CUDPSocketServerSource ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CButtonSource ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CHTTPGetter ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CHTTPPoster ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CFileSource ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CLineSeriesChartBox ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CStringOutputSink ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CFileSink ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance("UDP Client", 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance("TCP Client", 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CDataCounter ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CConditionalBranch ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CStopWatch ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CBlueScriptBox ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CDelayMakerBox ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CLogicalAND ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CLogicalOR ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CLogicalNOT ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CBitWiseAND ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CBitWiseOR ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CBitWiseLeftShift ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CBitWiseRightShift ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CBitWiseComplement ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CBitWiseXOR ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CDataComparisonEqual ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CDataComparisonGreater ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CDataComparisonLess ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CJsonParser ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CUniversalTypeConvertor ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CParseIntoArray ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CForEachLoop ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CGetByIndex ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CArrayLength ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CFineInArray ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CMathMultiplication ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CMathAddition ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CMathDivision ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CMathSubtraction ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CMathModulo ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CMathAbsolute ::getUniqueName(), 600, 100));
    sListOfAllBPBoxes.push_back(pFactory->createBPBoxInstance(CMathPower ::getUniqueName(), 600, 100));

    return sListOfAllBPBoxes;
}

QList<COperationBox*> CBPBoxFactory::findMatchingNodesWithStringQuery(const QString& query)
{
    auto listOfAllBoxes = getListOfAllBPBoxes();
    QList<COperationBox*> result;
    for (auto pBox : listOfAllBoxes)
    {
        if (pBox->blueBox_keyWords().contains(query, Qt::CaseInsensitive))
        {
            result.push_back(pBox);
        }
    }
    return result;
}
