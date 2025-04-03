#include "BluePrintPage.h"

#include "BPBoxManager.h"
#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "src/CBPBoxFactory/BPBoxFactory.h"




#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QGuiApplication>
#include <QDir>
#include <QTimer>



CBluePrintPage::CBluePrintPage(QObject *parent)
    : QObject{parent}
{

}


CBluePrintPage::~CBluePrintPage()
{
    clearCurrentBluePrintSession();
}



QQmlListProperty<COperationBox> CBluePrintPage::listOfBlueBoxes()
{
    return QQmlListProperty<COperationBox>(this, &m_listOfBlueBoxes);
}


QQmlListProperty<CFlowConnectionLine> CBluePrintPage::listOfFlowConnectionLines()
{
    return QQmlListProperty<CFlowConnectionLine>(this, &m_listOfFlowConnectionLines);
}


void CBluePrintPage::lineFlowStartedFromConnectionPoint(  QObject * startTerminal)
{
    // just in case: make sure last connection has a valid end point
    if(m_listOfFlowConnectionLines.length() >= 1 ){
        if( m_listOfFlowConnectionLines.last()->endPoint() == nullptr ){
            DEBUG_MSG_PRINT << "end point not valid and removed" ; // this is rare but it happens sometimes bcz of propagateevent in qml
            // lets remove the line from the start Terminals list of connected lines
            m_listOfFlowConnectionLines.last()->startPoint()->removeFlowLineFromConnectedList( m_listOfFlowConnectionLines.last() );
            // we have to release the flowLine
            delete m_listOfFlowConnectionLines.last();
            m_listOfFlowConnectionLines.pop_back();
            emit listOfFlowConnectionLinesChanged();
        }
    }

    auto outputTerminal  = dynamic_cast<COutputTerminal*>(startTerminal);
    ASSERTWITHMSG(outputTerminal , " unknown Terminal type clicked ");
    m_listOfFlowConnectionLines.push_back(new CFlowConnectionLine(outputTerminal  ));
    // lets add the lineflow  to the list of start point
    CFlowConnectionLine::bindFlowLineToOutputTerminal( m_listOfFlowConnectionLines.last() , outputTerminal );
    emit listOfFlowConnectionLinesChanged();
}


/*!
 * \brief CBluePrintPage::lineFlowPosChagnedFromConnectionPoint
 * xpos and ypos are differential and they dont show absolute position int he screen
 * \param posX
 * \param posY
 */
void CBluePrintPage::lineFlowPosChagnedFromConnectionPoint( const int & relPosX , const int & relPosY, const int & absPosX , const int & absPosY )
{
    // this is always last item in the list that has already been creted
    if(m_listOfFlowConnectionLines.length() >= 1 ){
        m_listOfFlowConnectionLines.last()->setFlowLine_endX(relPosX);
        m_listOfFlowConnectionLines.last()->setFlowLine_endY(relPosY);

        // better to be removed
        COperationBox * pBox  = checkIntersectionsWithBoxes(absPosX , absPosY ) ;
        CIOTerminal * pTerminal  = nullptr ;
        if( pBox  ){
            // lets find intersection with innerTerminals in the box
            pTerminal = checkIntersectionsWithTerminals( pBox  , absPosX , absPosY );
            if( pTerminal  ){
                pTerminal->setIsTerminalHovered(true);
            }
        }
        if(mp_lastGlowingTerminal && mp_lastGlowingTerminal != pTerminal )
            mp_lastGlowingTerminal->setIsTerminalHovered(false);
        mp_lastGlowingTerminal = pTerminal;
    }
}

COperationBox *CBluePrintPage::getBPBoxFromUniqueID(const int &BPBoxID)
{
    for(auto pCurrentBox : m_listOfBlueBoxes ){
        if(pCurrentBox->getBoxUniqueIDNumber() == BPBoxID)
            return pCurrentBox;
    }
    return nullptr;
}


/*!
 * \brief CBluePrintPage::lineFlowReleased
 * xpos and ypos are differential and they dont show absolute position int he screen
 * \param relPosX
 * \param relPosY
 * \param absPosX
 * \param absPosY
 */
void CBluePrintPage::lineFlowReleased(  const int & absPosX , const int & absPosY )
{
    ASSERTWITHMSG(m_listOfFlowConnectionLines.length() , ": ERROR" );

    if(mp_lastGlowingTerminal  )
        mp_lastGlowingTerminal->setIsTerminalHovered(false);
    mp_lastGlowingTerminal = nullptr;
    // lets find intersections with m_listOfBlueBoxes
    COperationBox * pBox  = checkIntersectionsWithBoxes(absPosX , absPosY ) ;
    CIOTerminal * pTerminal  = nullptr ;
    CInputTerminal * pInpTerminal = nullptr ;
    auto  lastLineFlow = m_listOfFlowConnectionLines.last() ;
    if( pBox  ){
        // lets find intersection with innerTerminals in the box
        pTerminal = checkIntersectionsWithTerminals( pBox  , absPosX , absPosY );
    }else{
        goto invalidReleasePoint ;
    }

    if( pTerminal == nullptr ){
        goto invalidReleasePoint ;
    }
    // if we are here it means mouse was released on a CInputTerminal , now we have to
    // fill related data in CInputTerminal and lineflow
    pInpTerminal = dynamic_cast<CInputTerminal*>(pTerminal);
    if( pInpTerminal == nullptr ){
        goto invalidReleasePoint ;
    }



    CFlowConnectionLine::bindFlowLineToInputTerminal( lastLineFlow , pInpTerminal);
    return ;

invalidReleasePoint:
    // lets remove the line from the start Terminals list of connected lines
    m_listOfFlowConnectionLines.last()->startPoint()->removeFlowLineFromConnectedList( m_listOfFlowConnectionLines.last() );
    // we have to release the flowLine
    delete m_listOfFlowConnectionLines.last();
    if( m_listOfFlowConnectionLines.length() )
        m_listOfFlowConnectionLines.pop_back();
    emit listOfFlowConnectionLinesChanged();

}


void CBluePrintPage::removeLineFromListModel(CFlowConnectionLine *lineToBeRemoved)
{
    ASSERTWITHINFO(m_listOfFlowConnectionLines.length());
    int indexOfLine = m_listOfFlowConnectionLines.indexOf( lineToBeRemoved ) ;
    if( indexOfLine == -1  ){
        DEBUG_MSG_PRINT << " removing line from list failed since line dosnt exists" ;
        return ;
    }
    m_listOfFlowConnectionLines.removeAt(indexOfLine);
    emit listOfFlowConnectionLinesChanged();
}


void CBluePrintPage::removeBPBoxFromListModel(QObject *boxToBeRemoved)
{
    auto pBPBox = dynamic_cast<COperationBox*>(boxToBeRemoved);
    ASSERTWITHINFO(pBPBox);
    // lets remove connected lines from the Terminals
    for(auto currentTerminal : pBPBox->getListOfInputTerminals()){
        currentTerminal->removeAllFlowLines();
    }
    for(auto currentTerminal : pBPBox->getListOfOutputTerminals()){
        currentTerminal->removeAllFlowLines();
    }

    int indexInList = m_listOfBlueBoxes.indexOf(pBPBox);
    //qDebug() << "indexInList" << indexInList ;
    if(indexInList >= 0 && indexInList <  m_listOfBlueBoxes.length() ){
        m_listOfBlueBoxes.removeAt( indexInList);
        QTimer::singleShot(0, this, [this , pBPBox ](){ // call in next event loop
            emit listOfBlueBoxesChanged();
            delete pBPBox ;
        });
    }else{
        DEBUG_MSG_PRINT << "box doesnt exist " << indexInList << boxToBeRemoved << pBPBox << m_listOfBlueBoxes.length() ;
    }
}


bool CBluePrintPage::createNewBoxFromGivenType( const QString &boxName , const int &posX, const int &posY ,  const bool & emitSignal )
{
    try{
        auto pBox = CBPBoxFactory::getInstance()->createBPBoxInstance( boxName , posX , posY );
        ASSERTWITHRETURN(pBox , false );
        pBox->setParentBluePrintPage(this);
        m_listOfBlueBoxes.push_back(pBox);
        if(emitSignal)
            emit listOfBlueBoxesChanged();
        return true;
    }catch (const std::exception & e){
        DEBUG_MSG_PRINT << " exception: " << e.what();
    }catch(...){
        DEBUG_MSG_PRINT << " exception: ";
    }
    return false ;
}


void CBluePrintPage::setApplicationScaleFactor(const float  &newValue)
{
    if(m_applicationScaleFactor == newValue )
        return ;
    m_applicationScaleFactor = newValue ;
    emit applicationScaleFactorChanged();
    // update max postion of boxes in x and y axis
    recalculateMaxPositions();
}


const QString &CBluePrintPage::currentBluePrintFilePath() const
{
    return m_currentBluePrintFilePath;
}

void CBluePrintPage::setCurrentBluePrintFilePath(const QString &newCurrentBluePrintFilePath)
{
    if (m_currentBluePrintFilePath == newCurrentBluePrintFilePath)
        return;
    m_currentBluePrintFilePath = newCurrentBluePrintFilePath;
    emit currentBluePrintFilePathChanged();
}



COperationBox * CBluePrintPage::checkIntersectionsWithBoxes(const int &absPosX, const int &absPosY)
{
    for ( auto currentBox : m_listOfBlueBoxes )
    {
        if (absPosX >= currentBox->blueBox_xPos() && absPosX <= currentBox->blueBox_xPos() + currentBox->blueBox_width() &&
                absPosY >= currentBox->blueBox_yPos() && absPosY <= currentBox->blueBox_yPos() + currentBox->blueBox_height() )
        {
            return currentBox ;
        }
    }
    return nullptr ;
}


CIOTerminal *  CBluePrintPage::checkIntersectionsWithTerminals( COperationBox *boxToBeSearched, const int &absPosX, const int &absPosY)
{
    ASSERTWITHRETURN(boxToBeSearched , nullptr);
    // now we have to iterat through list of inputs of boxToBeSearched to find interserction, we assume user wants to connects a flowLine
    // to an input, not an outpout , according to our assumption lineFlow always starts from an input and ends in an output
    auto listOfInputTerminals = boxToBeSearched->getListOfInputTerminals();
    int boxXPos = boxToBeSearched->blueBox_xPos() ;
    int boxYPos = boxToBeSearched->blueBox_yPos() ;
    for( auto currentTerminal : listOfInputTerminals ){
        if (absPosX >= boxXPos + currentTerminal->terminalXPos() && absPosX <= boxXPos + currentTerminal->terminalXPos() + currentTerminal->terminalSize() &&
                absPosY >= boxYPos + currentTerminal->terminalYPos() && absPosY <= boxYPos + currentTerminal->terminalYPos() + currentTerminal->terminalSize())
        {
            return currentTerminal ;
        }
    }
    return nullptr ;
}



void CBluePrintPage::recalculateMaxPositions()
{
    for(auto currentBox : m_listOfBlueBoxes ){
        if( (currentBox->blueBox_width() + currentBox->blueBox_xPos()) > m_maxBPBoxXpos  ){
            m_maxBPBoxXpos = currentBox->blueBox_width() + currentBox->blueBox_xPos() ;
            emit maxBPBoxXposChanged();
            // qDebug() << "m_maxBPBoxXpos = " << m_maxBPBoxXpos;
        }
        if( (currentBox->blueBox_height() + currentBox->blueBox_yPos()) > m_maxBPBoxYpos  ){
            m_maxBPBoxYpos = currentBox->blueBox_height() + currentBox->blueBox_yPos() ;
            emit maxBPBoxYposChanged();
            //  qDebug() << "m_maxBPBoxXpos = " << m_maxBPBoxYpos;
        }
    }
}



bool CBluePrintPage::saveBluePrintInfo(const QString & pathToFile)
{
    setCurrentBluePrintFilePath(pathToFile);
    // Create JSON array for BPBoxesInfo
    QJsonArray bpBoxesArray;
    for(auto currentBox :m_listOfBlueBoxes){
        QJsonObject localJsonObj;
        currentBox->serializeBoxInfoIntoJson(localJsonObj);
        bpBoxesArray.append(localJsonObj);
    }
    // Create JSON array for FlowLinesInfo
    QJsonArray flowLinesArray;
    for(auto currentLine :m_listOfFlowConnectionLines){
        QJsonObject localJsonObj;
        currentLine->serializeFlowLineInfoIntoJson(localJsonObj);
        flowLinesArray.append(localJsonObj);
    }
    // Create the main JSON object
    QJsonObject mainObject;
    mainObject["BPBoxesInfo"] = bpBoxesArray;
    mainObject["BPFlowLinesInfo"] = flowLinesArray;
    // Convert the JSON object to a JSON document
    QJsonDocument jsonDocument(mainObject);
    // Save the JSON document to a file
    QFile file(m_currentBluePrintFilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << jsonDocument.toJson(QJsonDocument::Indented);
        file.close();
        return true;
    }
    return false;
}






bool CBluePrintPage::loadBluePrintInfo(const QString &pathToFile)
{

    // Read the JSON file
    QFile file(pathToFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        DEBUG_MSG_PRINT << "Failed to open JSON file" << pathToFile;
        return false;
    }

    QTextStream in(&file);
    QString jsonString = in.readAll();
    file.close();

    // Parse the JSON document
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());

    // Check if the JSON document is valid
    if (jsonDocument.isNull())
    {
        DEBUG_MSG_PRINT << "Failed to parse JSON document";
        return false ;
    }
    // lets clear current info if any
    clearCurrentBluePrintSession();
    setCurrentBluePrintFilePath(pathToFile);
    // Access the main JSON object
    QJsonObject mainObject = jsonDocument.object();

    // Access BPBoxesInfo array
    QJsonArray bpBoxesArray = mainObject["BPBoxesInfo"].toArray();

    // Iterate through BPBoxesInfo objects
    for (const QJsonValue& bpBoxValue : bpBoxesArray)
    {
        QJsonObject bpBoxObject = bpBoxValue.toObject();
        auto res = createNewBoxFromGivenType( bpBoxObject["BoxName"].toString() ,  bpBoxObject["xPos"].toString().toInt(),bpBoxObject["yPos"].toString().toInt() , false  );
        if(!res)
            continue;
        auto pBox = m_listOfBlueBoxes.last();
        pBox->deserializeBoxInfoFromJson(bpBoxObject);
    }

    emit listOfBlueBoxesChanged();

    // Access BPFlowLinesInfo array
    QJsonArray flowLinesArray = mainObject["BPFlowLinesInfo"].toArray();

    // Iterate through BPFlowLinesInfo objects
    for (const QJsonValue& flowLineValue : flowLinesArray)
    {
        bool isValid = false ;
        QJsonObject flowLineObject = flowLineValue.toObject();
        auto pStartBPBox = getBPBoxFromUniqueID( flowLineObject["startBoxID"].toString().toInt() );
        ASSERTWITHRETURN(pStartBPBox , false );
        auto pEndBPBox = getBPBoxFromUniqueID( flowLineObject["endBoxID"].toString().toInt() );
        ASSERTWITHRETURN(pEndBPBox, false );
        int startTerminalIndex = flowLineObject["startTerminalIndex"].toString().toInt();
        isValid = startTerminalIndex <= (pStartBPBox->getListOfOutputTerminals().length() -1)  ;
        ASSERTWITHRETURN(isValid, false );
        int endTerminalIndex = flowLineObject["endTerminalIndex"].toString().toInt();
        isValid = endTerminalIndex <= (pEndBPBox->getListOfInputTerminals().length() -1)  ;
        ASSERTWITHRETURN(isValid, false );
        // if we are here it means all data are valid and we are good to create the flow line
        m_listOfFlowConnectionLines.push_back(new CFlowConnectionLine (pStartBPBox->getListOfOutputTerminals().at(startTerminalIndex)  ));
        CFlowConnectionLine::bindFlowLineToOutputTerminal( m_listOfFlowConnectionLines.last() , pStartBPBox->getListOfOutputTerminals().at(startTerminalIndex) );
        CFlowConnectionLine::bindFlowLineToInputTerminal( m_listOfFlowConnectionLines.last() , pEndBPBox->getListOfInputTerminals().at(endTerminalIndex));
    }

    emit listOfBlueBoxesChanged();
    emit listOfFlowConnectionLinesChanged();
    recalculateMaxPositions();
    return true;
}


void CBluePrintPage::clearCurrentBluePrintSession()
{
    // lets clear current info if any
    auto listOBoxes = m_listOfBlueBoxes ;
    auto listOFConnections = m_listOfFlowConnectionLines ;
    m_listOfBlueBoxes.clear();
    m_listOfFlowConnectionLines.clear();
    emit listOfBlueBoxesChanged();
    emit listOfFlowConnectionLinesChanged();
    qDeleteAll(listOBoxes);
    qDeleteAll(listOFConnections);
    // clear the path so that we know every thing is new
    m_currentBluePrintFilePath = "";
    emit currentBluePrintFilePathChanged();

}






