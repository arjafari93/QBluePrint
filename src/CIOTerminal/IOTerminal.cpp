#include "IOTerminal.h"

#include <QGuiApplication>
#include <QFont>
#include <QFontMetrics>

#include "src/CBPBoxManager/BPBoxManager.h"
#include "src/CFlowConnectionLine/FlowConnectionLine.h"
#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "src/CRawValueBase/RawValueBase.h"

CIOTerminal::CIOTerminal(const int &terminalIndexInBox, COperationBox *parent): m_terminalIndexInBox{terminalIndexInBox}
{
    ASSERTWITHINFO(parent);
    mp_containerBPBox = parent;
    QFont appFont =  qApp->font();
    QFontMetrics fontMetrics(appFont);
    // Get the default font height
    int defaultFontHeight = fontMetrics.height();
    m_terminalSize = defaultFontHeight  * 2 * 0.65 ;
    m_terminalYPos =  ( defaultFontHeight  * 2 * m_terminalIndexInBox ) +   defaultFontHeight  * 2 ;
}

void CIOTerminal::setTerminalCurrentData(const std::shared_ptr<CRawValueBase> &newValue){
    if(!newValue.get())
        return ;
    m_terminalCurrentData = newValue ;
    setTerminalColor(CBPStatic::getColorByType(newValue.get()) );
}

void CIOTerminal::changeTerminalCurrentData(const QVariant &newValue)
{
    switch (newValue.type()) {
    case QVariant::Int:
        setTerminalCurrentData( std::make_shared<CValue_int>(newValue.toInt()));
        break;
    case QVariant::Double:
        setTerminalCurrentData( std::make_shared<CValue_double>(newValue.toDouble()));
        break;
    case QVariant::Bool:
        setTerminalCurrentData( std::make_shared<CValue_bool>(newValue.toBool()));
        break;
    case QVariant::String:
        setTerminalCurrentData( std::make_shared<CValue_string>(newValue.toString()));
        break;
    default:
        DEBUG_MSG_PRINT << " type doesnt exist " ;
        break;
    }
    emit nodeIsPassingNewValue(); // this can be helpful for signal/slots and finding the data has changed though GUI popup

}

QVariant CIOTerminal::getTerminalCurrentData()
{

    if (auto* pVal = dynamic_cast<CValue_int*>(m_terminalCurrentData.get())) {
        return pVal->value();
    } else if (auto* pVal = dynamic_cast<CValue_double*>(m_terminalCurrentData.get())) {
        return (float)pVal->value();
    }else if (auto* pVal = dynamic_cast<CValue_bool*>(m_terminalCurrentData.get())) {
        return pVal->value();
    }else if (auto* pVal = dynamic_cast<CValue_string*>(m_terminalCurrentData.get())) {
        return pVal->value();
    }
    //DEBUG_MSG_PRINT << " type doesnt exist " ;
    return QVariant();
}

QQmlListProperty<CFlowConnectionLine> CIOTerminal::listOfConnectedLines()
{
    return QQmlListProperty<CFlowConnectionLine>(this, &m_listOfConnectedLines);
}





void CIOTerminal::addFlowLineToConnectedList(CFlowConnectionLine *lineToBeAdded)
{
    if(m_listOfConnectedLines.indexOf( lineToBeAdded ) != -1  ){
        DEBUG_MSG_PRINT << " adding line to the list failed since line exists" ;
        return ;
    }
    m_listOfConnectedLines.push_back(lineToBeAdded);
    emit listOfConnectedLinesChanged();
}













void CIOTerminal::removeFlowLineFromConnectedList(CFlowConnectionLine *lineToBeRemoved)
{
    ASSERTWITHINFO(m_listOfConnectedLines.length());
    int indexOfLine = m_listOfConnectedLines.indexOf( lineToBeRemoved ) ;
    if( indexOfLine == -1  ){
        DEBUG_MSG_PRINT << " removing line from list failed since line dosnt exists" ;
        return ;
    }
    m_listOfConnectedLines.removeAt(indexOfLine);
    emit listOfConnectedLinesChanged();
    // this function is NOT responsible for releasing the memory of line
}










void CIOTerminal::setIsTerminalHovered(const bool &newValue )
{
    if(m_isTerminalHovered == newValue )
        return ;
    m_isTerminalHovered = newValue;
    emit isTerminalHoveredChanged();
}

bool CIOTerminal::isTerminalHovered() const
{
    return m_isTerminalHovered;
}







void CIOTerminal::highlightLineFlowAtIndex(const int &lineFlowIndex, const bool &highLightOrNot)
{
    bool isIndexInRange = lineFlowIndex < m_listOfConnectedLines.length() ;
    // TODO: following will trigger a messagae on flow line removal which is unnecessary, we can remove it and just retunr if isIndexInRange is false
    ASSERTWITHMSG( isIndexInRange ,  " Index Out Of Range, length: " + QString::number( m_listOfConnectedLines.length())  + " index: " + QString::number( lineFlowIndex )  ) ;
    if(highLightOrNot == true )
        m_listOfConnectedLines.at( lineFlowIndex )->setFlowLine_strokeWidth( 3 ) ;
    else
        m_listOfConnectedLines.at( lineFlowIndex )->setFlowLine_strokeWidth( 1 ) ;
}










void CIOTerminal::removeLineFlowAtIndex(const int &lineFlowIndex)
{
    bool isIndexInRange = lineFlowIndex < m_listOfConnectedLines.length() ;
    ASSERTWITHMSG( isIndexInRange ,  " Index Out Of Range, length: " + QString::number( m_listOfConnectedLines.length())  + " index: " + QString::number( lineFlowIndex )  ) ;
    // lets remove the line from start Terminal
    auto lineToBeRemoved = m_listOfConnectedLines.at( lineFlowIndex ) ;
    lineToBeRemoved->startPoint()->removeFlowLineFromConnectedList(lineToBeRemoved);
    // lets remove the line from end Terminal
    lineToBeRemoved->endPoint()->removeFlowLineFromConnectedList(lineToBeRemoved);
    // lets remove the line from list model in CBPBoxManager
    CBPBoxManager::getInstance()->removeLineFromListModel(lineToBeRemoved);
    // lets free the memoery of flow line
    delete lineToBeRemoved ;
}










void CIOTerminal::removeAllFlowLines()
{
    while (m_listOfConnectedLines.length()) {
        removeLineFlowAtIndex( m_listOfConnectedLines.length() - 1  );
    }
}

QColor CIOTerminal::terminalColor() const
{
    return m_terminalColor;
}

void CIOTerminal::setTerminalColor(const QColor &newTerminalColor)
{
    if (m_terminalColor == newTerminalColor)
        return;
    m_terminalColor = newTerminalColor;
    emit terminalColorChanged();
}


















