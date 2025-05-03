#include "BlueScriptBox.h"


#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "../../CRawValueBase/RawValueBase.h"
#include <memory>
#include <QJSEngine>
#include <QJsonObject>


CBlueScriptBox::CBlueScriptBox ( int newBlueBox_xPos, int newBlueBox_yPos , QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth + 280 , blueBoxHeight + 230 , parent }
{
    m_blueBox_settingQMLPath = "qrc:/QML/BluePrintBoxes/ScriptRunnerBox/ScriptRunnerSettingsPopup.qml";
    mp_jsEngine = new QJSEngine(this);
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_ScriptRunner ;
    m_blueBox_HeaderIcon = "qrc:/Images/codeIcon.png" ;
    m_blueBox_HeadColor = QColor(114, 102, 200);
    // by default we add on input and one output
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("in0");
    inputNode1->setTerminalCurrentData(std::make_shared<CValue_string>(""));
    m_listOfInputTerminals.push_back(inputNode1 );

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("out0");
    outPutNode->setTerminalCurrentData(std::make_shared<CValue_string>(""));
    m_listOfOutputTerminals.push_back( outPutNode );

    m_blueBox_keyWords = "javascript code script runner running ";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_Miscellaneous;

    mp_jsEngine->evaluate(m_scriptFunctionBody);  // Load the function
    m_functionBlock = mp_jsEngine->globalObject().property("functionBlock");  // Get function by name
}

CBlueScriptBox::~CBlueScriptBox()
{

}



void CBlueScriptBox::evaluateOperation()
{
    if (!m_functionBlock.isCallable()) {
        if(m_blueBox_warningMsg.length() == 0 ) // otherwise let the last error message to exist
            setBlueBox_warningMsg("function is not callable") ;
        return ;
    }
    // following should never happen
    ASSERTWITHINFO(m_listOfInputTerminals.length()  == m_numInputs   );
    ASSERTWITHINFO(m_listOfOutputTerminals.length() == m_numOutputs  );

    QJSValueList args;
    for(int iter=0 ; iter < m_numInputs ; iter++ ){
        auto pInputData = m_listOfInputTerminals.at(iter)->terminalCurrentData().get() ;
        if(!pInputData){
            args << "";
            continue;
        }
        args << pInputData->convertToString();
    }

    QJSValue result = m_functionBlock.call(args);
    if (result.isError()) {
        setBlueBox_warningMsg("Error At Line " + result.property("lineNumber").toString() + " :" + result.toString());
        return  ;
    }
    QStringList outputList;
    if (result.isArray()) {
        int length = result.property("length").toInt();
        for (int i = 0; i < length; ++i) {
            outputList.append(result.property(i).toString());
        }
    } else {
        setBlueBox_warningMsg("JS function is not returning an array");
        return  ;
    }
    if(outputList.length() > m_listOfOutputTerminals.length() ){ // TODO: show warning to user
        setBlueBox_warningMsg("JS function is supposed to return an array of " +
                          QString::number( m_listOfOutputTerminals.length()) +
                          " elements, but it returns " + QString::number(outputList.length()) + " elements" );
        return ;
    }

    for(int iter=0; iter < outputList.length() ; iter++){
        m_listOfOutputTerminals.at(iter)->sendValueToFlowLine( std::make_shared<CValue_string>( outputList.at(iter)) );
    }
    setBlueBox_warningMsg("");
}

const QString &CBlueScriptBox::scriptFunctionBody() const
{
    return m_scriptFunctionBody;
}

void CBlueScriptBox::setScriptFunctionBody(const QString &newScriptFunctionBody)
{
    if (m_scriptFunctionBody == newScriptFunctionBody)
        return;
    m_scriptFunctionBody = newScriptFunctionBody;
    emit scriptFunctionBodyChanged();
    QJSValue result = mp_jsEngine->evaluate(m_scriptFunctionBody);  // Load the function
    // Check for syntax errors in JS code
    if (result.isError()) {
        setBlueBox_warningMsg("Error At Line " + result.property("lineNumber").toString() + " :" + result.toString());
        return  ;
    }
    m_functionBlock = mp_jsEngine->globalObject().property("functionBlock");  // Get function by name
    setBlueBox_warningMsg("");
}

int CBlueScriptBox::numInputs() const
{
    return m_numInputs;
}

void CBlueScriptBox::setNumInputs(int newNumInputs)
{
    if (m_numInputs == newNumInputs || newNumInputs <= 0 )
        return;
    // in case user is removing input termnial , we have to remove flow lines first
    while (m_listOfInputTerminals.length() > newNumInputs ) {
        m_listOfInputTerminals.back()->removeAllFlowLines();
        auto pTermnl = m_listOfInputTerminals.back();
        m_listOfInputTerminals.pop_back();
        emit listOfInputTerminalsChanged();
        delete pTermnl;
    }
    // in case user is adding new input termnial
    while (m_listOfInputTerminals.length() < newNumInputs ) {
        auto inputNode1 = new CInputTerminal(m_listOfInputTerminals.length(), this);
        inputNode1->setTerminalName("in" + QString::number( m_listOfInputTerminals.length()));
        inputNode1->setTerminalCurrentData(std::make_shared<CValue_string>(""));
        m_listOfInputTerminals.push_back(inputNode1 );
        emit listOfInputTerminalsChanged();
    }
    m_numInputs = newNumInputs;
    emit numInputsChanged();
}

int CBlueScriptBox::numOutputs() const
{
    return m_numOutputs;
}

void CBlueScriptBox::setNumOutputs(int newNumOutputs)
{
    if (m_numOutputs == newNumOutputs)
        return;

    while (m_listOfOutputTerminals.length() > newNumOutputs ) {
        m_listOfOutputTerminals.back()->removeAllFlowLines();
        auto pTermnl = m_listOfOutputTerminals.back();
        m_listOfOutputTerminals.pop_back();
        emit listOfOutputTerminalsChanged();
        delete pTermnl;
    }

    while (m_listOfOutputTerminals.length() < newNumOutputs ) {
        auto outPutNode = new COutputTerminal(m_listOfOutputTerminals.length(), this);
        outPutNode->setTerminalName("out" + QString::number( m_listOfOutputTerminals.length()));
        outPutNode->setTerminalCurrentData(std::make_shared<CValue_string>(""));
        m_listOfOutputTerminals.push_back(outPutNode );
        emit listOfOutputTerminalsChanged();
    }
    m_numOutputs = newNumOutputs;
    emit numOutputsChanged();
}



void CBlueScriptBox::serializeBoxInfoIntoJson(QJsonObject &jsonObj)
{
    COperationBox::serializeBoxInfoIntoJson(jsonObj);
    jsonObj["numInputs"]  = QString::number( m_numInputs  ) ;
    jsonObj["numOutputs"] = QString::number( m_numOutputs ) ;
    jsonObj["funcBody"] = m_scriptFunctionBody ;
}

void CBlueScriptBox::deserializeBoxInfoFromJson(const QJsonObject &jsonObj)
{
    m_numInputs  = jsonObj["numInputs"].toString().toInt()   ;
    m_numOutputs = jsonObj["numOutputs"].toString().toInt()   ;
    setScriptFunctionBody( jsonObj["funcBody"].toString() ) ;
    while (m_listOfInputTerminals.length() < m_numInputs ) {
        auto inputNode1 = new CInputTerminal(m_listOfInputTerminals.length(), this);
        inputNode1->setTerminalName("in" + QString::number( m_listOfInputTerminals.length()));
        inputNode1->setTerminalCurrentData(std::make_shared<CValue_string>(""));
        m_listOfInputTerminals.push_back(inputNode1 );
        emit listOfInputTerminalsChanged();
    }
    while (m_listOfOutputTerminals.length() < m_numOutputs ) {
        auto outPutNode = new COutputTerminal(m_listOfOutputTerminals.length(), this);
        outPutNode->setTerminalName("out" + QString::number( m_listOfOutputTerminals.length()));
        outPutNode->setTerminalCurrentData(std::make_shared<CValue_string>(""));
        m_listOfOutputTerminals.push_back(outPutNode );
        emit listOfOutputTerminalsChanged();
    }
    // in this specific box we call the base deserialize method after the derived body, bcz teminals will change in derived body
    COperationBox::deserializeBoxInfoFromJson(jsonObj);
}


