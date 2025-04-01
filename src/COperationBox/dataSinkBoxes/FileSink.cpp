#include "FileSink.h"

#include <QTimer>
#include <QDir>
#include <QFile>
#include <QDateTime>
#include <QCoreApplication>

#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CRawValueBase/RawValueBase.h"


inline const static int blueBoxWidth  =  220  ;
inline const static int blueBoxHeight =  120  ;


CFileSink::CFileSink ( int newBlueBox_xPos, int newBlueBox_yPos,  QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth , blueBoxHeight , parent }
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigPictureOperator ;
    m_blueBox_HeadColor = QColor(230, 150, 240);
    m_blueBox_HeaderIcon = "qrc:/Images/fileIn.png";
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Input");
    m_listOfInputTerminals.push_back(inputNode1 );

    auto inputNode2 = new CInputTerminal(1, this);
    inputNode2->setTerminalName("Path");
    m_listOfInputTerminals.push_back(inputNode2 );
    m_pathToFile =  QCoreApplication::applicationDirPath() + "/fileSinkOutputs/" +
                QString::number( QDateTime::currentMSecsSinceEpoch() ) + ".txt" ;
    inputNode2->setTerminalCurrentData(   std::make_shared<CValue_string>(m_pathToFile) );


    // find path has changed through popup
    connect(inputNode2 , &CIOTerminal::nodeIsPassingNewValue , this , [this, inputNode2](){
        auto pNewPath =  dynamic_cast<CValue_string*>(inputNode2->terminalCurrentData().get());
        if( pNewPath &&  pNewPath->value() != m_pathToFile){
            m_pathToFile = pNewPath->value() ;
            if(m_blueBox_warningMsg == "FilePath Can Not Be Empty" && m_pathToFile.isEmpty() == false  )
                setBlueBox_warningMsg("");
            else if(m_pathToFile.isEmpty())
                setBlueBox_warningMsg ( "FilePath Can Not Be Empty");
        }
    });

    m_blueBox_keyWords = "input sink  file string folder output text write";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_OutPutSink ;

    mp_flushTimer = new QTimer(this);
    connect(mp_flushTimer , &QTimer::timeout , this ,  &CFileSink::flushStringsIntoFile);
    mp_flushTimer->setInterval(m_flushTimerIntervalMS);
    mp_flushTimer->start();
}

CFileSink::~CFileSink()
{
    flushStringsIntoFile();
}



void CFileSink::evaluateOperation()
{
    auto inputVal = m_listOfInputTerminals.at(0)->terminalCurrentData().get() ;
    QString stringVal ;
    if (auto* pVal = dynamic_cast<CValue_int*>(inputVal)) {
        stringVal = QString::number(pVal->value()) ;
    } else if (auto* pVal = dynamic_cast<CValue_double*>(inputVal)) {
        stringVal = QString::number(pVal->value() , 'f' , MAX_DOUBLE_PRECISION ) ;
    }else if (auto* pVal = dynamic_cast<CValue_string*>(inputVal)) {
        stringVal = pVal->value() ;
    }else if (auto* pVal = dynamic_cast<CValue_bool*>(inputVal)) {
        stringVal =  QString::number(pVal->value()) ;
    }
    m_bufferOfStrings.push_back(stringVal);
    if(m_bufferOfStrings.length() > m_maxBufferSize)
        flushStringsIntoFile();
}

static void ensureDirectoryExists(const QString & filePath) {
    QDir dir = QFileInfo(filePath).absoluteDir();
    if (!dir.exists()) {
        dir.mkpath(".");  // Create all necessary parent directories
    }
}

void CFileSink::flushStringsIntoFile()
{
    if (m_bufferOfStrings.isEmpty()) return; // Nothing to write
    if (m_pathToFile.isEmpty()) { setBlueBox_warningMsg ( "FilePath Can Not Be Empty"); return; }// no path

    ensureDirectoryExists(m_pathToFile); // Ensure directories exist before opening the file

    QFile fileInstance(m_pathToFile);
    if (!fileInstance.open(QIODevice::Append | QIODevice::Text)) { // open in apppend mode
        setBlueBox_warningMsg("failed to open the file at " + m_pathToFile);
        DEBUG_MSG_PRINT << " Cannot open file";
        return ;
    }

    QTextStream outStrm(&fileInstance);
    for ( auto& currentText : m_bufferOfStrings) {
        currentText.replace("\\r\\n", "\r\n"); // Replace literal "\n" with actual newlines
        outStrm << currentText ;
    }
    fileInstance.close();  // Explicitly close after each writing
    m_bufferOfStrings.clear();  // reeset the buffer
    setBlueBox_warningMsg("");
}


