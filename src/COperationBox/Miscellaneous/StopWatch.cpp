#include "StopWatch.h"


#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "../../CRawValueBase/RawValueBase.h"
#include <memory>
#include <QTimer>
#include <QDateTime>


using namespace std::literals ;
using namespace std::chrono;

CStopWatch::CStopWatch ( int newBlueBox_xPos, int newBlueBox_yPos , QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth + 30  , blueBoxHeight - 30  , parent }
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_StopWatch ;
    m_blueBox_HeadColor = QColor(70, 110, 160);
    m_blueBox_HeaderIcon = "qrc:/Images/stopWatch.png";
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Run");
    m_listOfInputTerminals.push_back(inputNode1 );

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("us");
    m_listOfOutputTerminals.push_back( outPutNode );

    m_blueBox_keyWords = "stop watch stopwatch timer measure elapse";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_Miscellaneous;

    mp_internalTimer = new QTimer(this);
    connect(mp_internalTimer, &QTimer::timeout , this , [this](){
        // Compute duration in microseconds
        microseconds duration = duration_cast<microseconds>( high_resolution_clock::now() - m_startTime);
        setElapsedTime(duration.count() );
        sendValueOnAllOutputTerminals( std::make_shared<CValue_int>( m_elapsedTime) );
    });
}

CStopWatch::~CStopWatch()
{
    mp_internalTimer->stop();
}



void CStopWatch::evaluateOperation()
{
    if(!m_listOfInputTerminals.at(0)->terminalCurrentData().get() )
        return ;

    bool newRunningVal = false ;
    auto pRunVal = m_listOfInputTerminals.at(0)->terminalCurrentData().get() ;
    if (auto* pVal = dynamic_cast<CValue_int*>(pRunVal)) {
        newRunningVal =  (bool)pVal->value()   ;
    } else if (auto* pVal = dynamic_cast<CValue_double*>(pRunVal)) {
        newRunningVal = (bool)pVal->value();
    }else if (auto* pVal = dynamic_cast<CValue_bool*>(pRunVal)) {
        newRunningVal = pVal->value();
    } else if (auto* pVal = dynamic_cast<CValue_string*>(pRunVal)) {
        bool ok = false ;
        pVal->value().toLongLong(&ok);
        if(ok)
            newRunningVal =  pVal->value().toLongLong();
        else
            newRunningVal = pVal->value().length() ;
    } else if (auto* pVal = dynamic_cast<CValue_string*>(pRunVal)) {
        newRunningVal = pVal->value().length();
    }else{
        DEBUG_MSG_PRINT << "inavlid daata type " ;
        return ;
    }

    if( m_stopWatchRunning == newRunningVal )
        return ;
    // if we are here it means the Running value has changed by user
    setStopWatchRunning(!m_stopWatchRunning);
    if(m_stopWatchRunning){
        m_startTime = std::chrono::high_resolution_clock::now();
        mp_internalTimer->start(100);
    }
    else{
        mp_internalTimer->stop();
        microseconds duration = duration_cast<microseconds>( high_resolution_clock::now() - m_startTime);
        setElapsedTime(duration.count() );
        sendValueOnAllOutputTerminals( std::make_shared<CValue_int>( m_elapsedTime) );
    }
}

bool CStopWatch::stopWatchRunning() const
{
    return m_stopWatchRunning;
}

void CStopWatch::setStopWatchRunning(bool newStopWatchRunning)
{
    if (m_stopWatchRunning == newStopWatchRunning)
        return;
    m_stopWatchRunning = newStopWatchRunning;
    emit stopWatchRunningChanged();
}

int CStopWatch::elapsedTime() const
{
    return m_elapsedTime;
}

void CStopWatch::setElapsedTime(int newElapsedTime)
{
    if (m_elapsedTime == newElapsedTime)
        return;
    m_elapsedTime = newElapsedTime;
    emit elapsedTimeChanged();
}





