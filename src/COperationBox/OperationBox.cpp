#include "OperationBox.h"

#include <QJsonObject>
#include <QJsonArray>

#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "src/CFlowConnectionLine/FlowConnectionLine.h"
#include "src/CRawValueBase/RawValueBase.h"



static int uniqueIDCounter = 0 ;

COperationBox::COperationBox(QString newBlueBox_name, int newBlueBox_xPos, int newBlueBox_yPos, int newBlueBox_width, int newBlueBox_height ,  QObject *parent) :
    QObject{parent} , m_blueBox_name   { newBlueBox_name   } ,
    m_blueBox_xPos   { newBlueBox_xPos   } ,
    m_blueBox_yPos   { newBlueBox_yPos   } ,
    m_blueBox_width  { newBlueBox_width  } ,
    m_blueBox_height { newBlueBox_height }
{
    uniqueIDCounter++;
    m_boxUniqueIDNumber = uniqueIDCounter;
}

void COperationBox::setBoxUniqueIDNumber(const int &newValue)
{
    m_boxUniqueIDNumber = newValue;
    if(newValue > uniqueIDCounter)
        uniqueIDCounter = newValue ;
    uniqueIDCounter++;
}

QQmlListProperty<COutputTerminal> COperationBox::listOfOutputTerminals()
{
    return QQmlListProperty<COutputTerminal>(this, &m_listOfOutputTerminals);
}

QQmlListProperty<CInputTerminal> COperationBox::listOfInputTerminals()
{
    return QQmlListProperty<CInputTerminal>(this, &m_listOfInputTerminals);
}





QString COperationBox::blueBox_name      () const { return  m_blueBox_name       ; }
int     COperationBox::blueBox_xPos      () const { return  m_blueBox_xPos       ; }
int     COperationBox::blueBox_yPos      () const { return  m_blueBox_yPos       ; }
int     COperationBox::blueBox_width     () const { return  m_blueBox_width      ; }
int     COperationBox::blueBox_height    () const { return  m_blueBox_height     ; }



QString COperationBox::blueBox_keyWords() const
{
    return m_blueBox_keyWords ;
}

void COperationBox::setBlueBox_keyWords(const QString &newValue)
{
    if( m_blueBox_keyWords      == newValue )
        return ;
    m_blueBox_keyWords      = newValue ;
    emit blueBox_keyWordsChanged     ();
}






void COperationBox::setBlueBox_name       ( const QString & newValue ) {
    if( m_blueBox_name      == newValue )
        return ;
    m_blueBox_name      = newValue ;
    emit blueBox_nameChanged     ();
}



void COperationBox::setBlueBox_xPos       ( const int     & newValue ) {
    if( m_blueBox_xPos      == newValue )
        return ;
    m_blueBox_xPos      = newValue ;
    emit blueBox_xPosChanged     ();
    // now we have to deal with the connected lineflows
    reCalcOutGoingLineFlowPos();
    reCalcIncomingLineFlowPos();
}




void COperationBox::setBlueBox_yPos       ( const int     & newValue ) {
    if( m_blueBox_yPos      == newValue )
        return ;
    m_blueBox_yPos      = newValue ;
    emit blueBox_yPosChanged     ();
    reCalcOutGoingLineFlowPos();
    reCalcIncomingLineFlowPos();
}



void COperationBox::setBlueBox_width      ( const int     & newValue ) {
    if( m_blueBox_width     == newValue )
        return ;
    m_blueBox_width     = newValue ;
    emit blueBox_widthChanged    ();
}




void COperationBox::setBlueBox_height     ( const int     & newValue ) {
    if( m_blueBox_height    == newValue )
        return ;
    m_blueBox_height    = newValue ;
    emit blueBox_heightChanged   ();
}











void COperationBox::sendValueOnAllOutputTerminals(std::shared_ptr<CRawValueBase> valueToBeSent)
{
    for(auto currentOutTerminal : m_listOfOutputTerminals ){
       // if(!valueToBeSent.get())
            currentOutTerminal->sendValueToFlowLine( valueToBeSent );
    }
}









void COperationBox::reCalcOutGoingLineFlowPos()
{
    // start point of the lineflow has changed in output Terminals
    for( auto currentOutTerminal : m_listOfOutputTerminals ){
        for( auto currentLineFlow :  currentOutTerminal->getListOfConnectedLines() ){
            int lineFlowEndXPos = currentLineFlow->flowLine_startX() + currentLineFlow->flowLine_endX() ;
            int lineFlowEndYPos = currentLineFlow->flowLine_startY() + currentLineFlow->flowLine_endY() ;

            currentLineFlow->setFlowLine_startX( m_blueBox_xPos + m_blueBox_width );
            currentLineFlow->setFlowLine_startY( m_blueBox_yPos  + currentLineFlow->startPoint()->terminalYPos() + currentLineFlow->startPoint()->terminalSize()  );

            currentLineFlow->setFlowLine_endX( lineFlowEndXPos -  currentLineFlow->flowLine_startX()  ) ;
            currentLineFlow->setFlowLine_endY( lineFlowEndYPos -  currentLineFlow->flowLine_startY()  ) ;
        }
    }
}





void COperationBox::reCalcIncomingLineFlowPos()
{
    // end point of the lineflow has changed in input Terminals
    for( auto currentInputTerminal : m_listOfInputTerminals ){
        for( auto currentLineFlow :  currentInputTerminal->getListOfConnectedLines() ){
            currentLineFlow->setFlowLine_endX( m_blueBox_xPos  - currentLineFlow->flowLine_startX()  ) ;
            currentLineFlow->setFlowLine_endY( m_blueBox_yPos  + currentLineFlow->endPoint()->terminalYPos() + currentLineFlow->endPoint()->terminalSize()  - currentLineFlow->flowLine_startY()  ) ;
        }
    }
}

/*!
 * \brief COperationBox::serializeBoxInfoIntoJson
 * this method serializes box information into the given json object
 * this method is virtual, some boxes who have specific information that needs
 * to be menitoned into the json file will override this method, then they call
 * the base class's serializeBoxInfoIntoJson method and after that they add
 * their specific info into the json file
 * \param jsonObj
 */
void COperationBox::serializeBoxInfoIntoJson(QJsonObject &jsonObj)
{
    jsonObj["BoxName"] = m_blueBox_name;
    jsonObj["xPos"] = QString::number( m_blueBox_xPos ) ;
    jsonObj["yPos"] = QString::number( m_blueBox_yPos ) ;
    jsonObj["uniqueID"] = QString::number( m_boxUniqueIDNumber ) ;
    QJsonArray arrayOfInputValues;
    int iter = 0;
    for(auto pInTeminal : m_listOfInputTerminals ){
        if(pInTeminal->terminalCurrentData()){
            QJsonObject tempInTerminalObj;
            tempInTerminalObj["Type"] = CBPStatic::getNameOfTypeAsString(pInTeminal);
            tempInTerminalObj["TrmnlIndex"] = QString::number(iter) ;
            tempInTerminalObj["Value"] = pInTeminal->terminalCurrentData()->convertToString();
            arrayOfInputValues.append(tempInTerminalObj);
        }
        iter++;
    }
    jsonObj["inptTrmnls"] = arrayOfInputValues;
}



static inline bool setTerminalValuesForBox(const QJsonObject & jsonObj , COperationBox * pBox ){
    QString terminalType = jsonObj["Type"].toString();
    int terminalID = jsonObj["TrmnlIndex"].toString().toInt();
    ASSERTWITHRETURN(terminalID < pBox->getListOfInputTerminals().length() , false);

    std::shared_ptr<CRawValueBase> pDataVal {nullptr};
    if( terminalType == "int")
        pDataVal = std::make_shared<CValue_int>(jsonObj["Value"].toString().toInt());
    else if( terminalType == "double")
        pDataVal = std::make_shared<CValue_double>(jsonObj["Value"].toString().toDouble());
    else if( terminalType == "bool")
        pDataVal = std::make_shared<CValue_bool>((bool)(jsonObj["Value"].toString().toInt()));
    else if( terminalType == "string")
        pDataVal = std::make_shared<CValue_string>(jsonObj["Value"].toString());
    else {
        DEBUG_MSG_PRINT << "type is now known" << terminalType;
        return false ;
    }
    pBox->getListOfInputTerminals().at(terminalID)->setTerminalCurrentData(pDataVal);
    return true ;
}




void COperationBox::deserializeBoxInfoFromJson(const QJsonObject &jsonObj)
{
    setBoxUniqueIDNumber(jsonObj["uniqueID"].toString().toInt());
    // lets put the default values for input terminals
    QJsonArray inpTermnlsArray = jsonObj["inptTrmnls"].toArray();
    for (const QJsonValue& currentTermnl : inpTermnlsArray)
    {
        setTerminalValuesForBox(currentTermnl.toObject() , this );
    }
}



