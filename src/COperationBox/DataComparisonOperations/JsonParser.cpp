#include "JsonParser.h"

#include <QJsonDocument>
#include <QJsonObject>


#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "../../CRawValueBase/RawValueBase.h"

inline const static int blueBoxWidth  = 220 ;
inline const static int blueBoxHeight = 100 ;


CJsonParser::CJsonParser ( int newBlueBox_xPos, int newBlueBox_yPos , QObject *parent)
    : COperationBox{ m_uniqueBoxName  , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth , blueBoxHeight , parent }
{
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigPictureOperator ;
    m_blueBox_HeaderIcon = "qrc:/Images/jsonIcon.png";
    m_blueBox_HeadColor = QColor(155, 176, 128);
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("json");
    m_listOfInputTerminals.push_back(inputNode1 );

    auto inputNode2 = new CInputTerminal(1, this);
    inputNode2->setTerminalName("key");
    m_listOfInputTerminals.push_back(inputNode2 );

    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("value");
    m_listOfOutputTerminals.push_back( outPutNode );

    m_blueBox_keyWords = "json parser convertor interpretor ";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_DataComparison ;
}





void CJsonParser::evaluateOperation()
{
    auto pJsonStr = m_listOfInputTerminals.at(0)->terminalCurrentData().get() ;
    if(!pJsonStr)
        return ;
    auto pKeyStr = m_listOfInputTerminals.at(1)->terminalCurrentData().get() ;
    if(!pKeyStr)
        return ;
    auto* pJsonData = dynamic_cast<CValue_string*>(pJsonStr);
    if(!pJsonData  ) // only accept string for json data itself
        return ;

    QString userKey = ""; // accept all types for the key
    if (auto* pVal = dynamic_cast<CValue_int*>(pKeyStr)) {
        userKey = QString::number( pVal->value());
    } else if (auto* pVal = dynamic_cast<CValue_double*>(pKeyStr)) {
        userKey = QString::number(pVal->value(), 'f' , MAX_DOUBLE_PRECISION) ;
    }else if (auto* pVal = dynamic_cast<CValue_bool*>(pKeyStr)) {
        userKey =  QString::number( pVal->value());
    }else if (auto* pVal = dynamic_cast<CValue_string*>(pKeyStr)) {
        userKey = pVal->value();
    }

    // Parse the JSON

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(pJsonData->value().toUtf8() , &parseError );

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON Parse Error:" << pJsonData->value() <<  parseError.errorString();
        return;
    }

    if (!jsonDoc.isObject()) {
        qDebug() << "Invalid JSON format";
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();
    // Get the value
    if (jsonObj.contains(userKey)) {
        QJsonValue jsonVal = jsonObj.value(userKey);
        // Convert the value to a QString
        QString dataString;
        if (jsonVal.isObject()) {
            QJsonDocument tempDoc(jsonVal.toObject());
            dataString = QString(tempDoc.toJson(QJsonDocument::Compact));  // Convert JSON object to string
        } else {
            dataString = jsonVal.toString();  // If "data" is a primitive type
        }

        m_listOfOutputTerminals.at(0)->sendValueToFlowLine( std::make_shared<CValue_string>(dataString) );
    } else {
        qDebug() << "userKey not found";
    }

    //sendValueOnAllOutputTerminals( result );
}

