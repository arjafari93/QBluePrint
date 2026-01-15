#include "FileSource.h"

#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "src/CRawValueBase/RawValueBase.h"

CFileSource::CFileSource(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent) : COperationBox{m_uniqueBoxName, newBlueBox_xPos, newBlueBox_yPos, blueBoxWidth, blueBoxHeight - 30, parent}
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigPictureOperator;
    m_blueBox_HeadColor = QColor(150, 230, 240);
    m_blueBox_HeaderIcon = "qrc:/Images/fileOut.png";
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Input");
    m_listOfInputTerminals.push_back(inputNode1);

    auto outPutNodeString = new COutputTerminal(0, this);
    outPutNodeString->setTerminalName("Out");
    m_listOfOutputTerminals.push_back(outPutNodeString);

    m_blueBox_keyWords = "output source  file string folder output text read";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_InputSource;
    // find path has changed through popup
    connect(inputNode1, &CIOTerminal::nodeIsPassingNewValue, this, [this, inputNode1]() {
        auto pNewPath = dynamic_cast<CValue_string*>(inputNode1->terminalCurrentData().get());
        if (pNewPath)
        {
            evaluateOperation();
        }
        else
        {
            setBlueBox_warningMsg("invalid input as file path");
            return;
        }
    });
}

CFileSource::~CFileSource() {}

void CFileSource::evaluateOperation()
{
    auto inputVal = m_listOfInputTerminals.at(0)->terminalCurrentData().get();
    QString filePath;
    if (auto* pVal = dynamic_cast<CValue_string*>(inputVal))
    {
        filePath = pVal->value();
    }
    else
    {
        setBlueBox_warningMsg("invalid input as file path");
        return;
    }
    QFile file(filePath);
    // Check if the file exists
    if (!file.exists())
    {
        setBlueBox_warningMsg("File Doesnt Exist At " + filePath);
        return;
    }

    // Try to open the file
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        setBlueBox_warningMsg("Failed to open file:" + file.errorString());
        return;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();
    setBlueBox_warningMsg("");
    m_listOfOutputTerminals.at(0)->sendValueToFlowLine(std::make_shared<CValue_string>(fileContent));
}
