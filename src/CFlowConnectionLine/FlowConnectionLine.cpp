#include "FlowConnectionLine.h"

#include <QJsonObject>

#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "src/COperationBox/OperationBox.h"
#include "src/CBPStatic/BPStatic.h"

CFlowConnectionLine::CFlowConnectionLine(QObject *parent)
    : QObject{parent}
{

}

CFlowConnectionLine::CFlowConnectionLine(int newFlowLine_startX, int newflowLine_startY, int newFlowLine_endX, int newFlowLine_endY, /*int newFlowLine_ctrl1X, int newFlowLine_ctrl1Y, int newFlowLine_ctrl2X, int newFlowLine_ctrl2Y,*/ QObject *parent):
    QObject{parent} , m_flowLine_startX { newFlowLine_startX  } ,
    m_flowLine_startY { newflowLine_startY  } ,
    m_flowLine_endX   { newFlowLine_endX    } ,
    m_flowLine_endY   { newFlowLine_endY    }
{

}




CFlowConnectionLine::CFlowConnectionLine(COutputTerminal *pStartTerminal, QObject *parent):  QObject{parent}
{
    // we have to find start positions from COutputTerminal
    m_flowLine_startX = pStartTerminal->containerBPBox()->blueBox_xPos() + pStartTerminal->containerBPBox()->blueBox_width() ;
    m_flowLine_startY = pStartTerminal->containerBPBox()->blueBox_yPos() + pStartTerminal->terminalYPos() + pStartTerminal->terminalSize();
    m_flowLine_endX = 0 ;
    m_flowLine_endY = 0 ;
}



int  CFlowConnectionLine::flowLine_startX () const { return  m_flowLine_startX ; }
int  CFlowConnectionLine::flowLine_startY () const { return  m_flowLine_startY ; }
int  CFlowConnectionLine::flowLine_endX   () const { return  m_flowLine_endX   ; }
int  CFlowConnectionLine::flowLine_endY   () const { return  m_flowLine_endY   ; }

void CFlowConnectionLine::setStartPoint(COutputTerminal *newValue){
    mp_startPoint = newValue ;
    // find flow line color
    setFlowLine_color( CBPStatic::getColorOfNodeByType(newValue));

}

void CFlowConnectionLine::setFlowLine_strokeWidth(const int &newValue){ if(m_flowLine_strokeWidth == newValue) return;  m_flowLine_strokeWidth = newValue ; emit flowLine_strokeWidthChanged();}



void CFlowConnectionLine::setFlowLine_startX  ( const int     & newValue ) { if(  m_flowLine_startX == newValue ) return ;  m_flowLine_startX = newValue ; emit flowLine_startXChanged(); }
void CFlowConnectionLine::setFlowLine_startY  ( const int     & newValue ) { if(  m_flowLine_startY == newValue ) return ;  m_flowLine_startY = newValue ; emit flowLine_startYChanged(); }
void CFlowConnectionLine::setFlowLine_endX    ( const int     & newValue ) { if(  m_flowLine_endX   == newValue ) return ;  m_flowLine_endX   = newValue ; emit flowLine_endXChanged  (); }
void CFlowConnectionLine::setFlowLine_endY    ( const int     & newValue ) { if(  m_flowLine_endY   == newValue ) return ;  m_flowLine_endY   = newValue ; emit flowLine_endYChanged  (); }

const QColor &CFlowConnectionLine::flowLine_color() const
{
    return m_flowLine_color;
}

void CFlowConnectionLine::setFlowLine_color(const QColor &newValue)
{
    if (m_flowLine_color == newValue)
        return;
    m_flowLine_color = newValue;
    emit flowLine_colorChanged();
}


void CFlowConnectionLine::serializeFlowLineInfoIntoJson(QJsonObject &jsonObj)
{
    auto pStartContainerBox = mp_startPoint->containerBPBox();
    auto pEndContainerBox =  mp_endPoint->containerBPBox();
    jsonObj["startBoxID"] = QString::number( pStartContainerBox->getBoxUniqueIDNumber() );
    jsonObj["endBoxID"] = QString::number( pEndContainerBox->getBoxUniqueIDNumber() );
    jsonObj["startTerminalIndex"] = QString::number( pStartContainerBox->getListOfOutputTerminals().indexOf(startPoint()));
    jsonObj["endTerminalIndex"] = QString::number( pEndContainerBox->getListOfInputTerminals().indexOf(endPoint()));
}






void CFlowConnectionLine::passValueToEndPoint(const  std::shared_ptr<CRawValueBase> &  valueToBePassed)
{
    // value is coming from startPoint, we have to pass it to the end point
    if( mp_endPoint  == nullptr ){
        // this can happen when connecting nodes
        // DEBUG_MSG_PRINT << " ERROR !!! endpoint is not valid  " ;
        return ;
    }
    mp_endPoint->receivedValueFromFlowLine( valueToBePassed ) ;
}







void  CFlowConnectionLine::bindFlowLineToInputTerminal( CFlowConnectionLine * pFlowLine , CInputTerminal * pInputTerminal ){
    ASSERTWITHINFO(pFlowLine);
    ASSERTWITHINFO(pInputTerminal);
    auto pBox = pInputTerminal->containerBPBox();
    pInputTerminal->addFlowLineToConnectedList(pFlowLine);
    pFlowLine->setEndPoint( pInputTerminal ) ;
    // now lets fix the lineflow position since it is probably positioned in the middle of the Terminal
    // 1) set xPos to the box xPos
    pFlowLine->setFlowLine_endX( pBox->blueBox_xPos() - pFlowLine->flowLine_startX()  );
    // 2) set the yPos to the middle of the Terminal Y pos
    pFlowLine->setFlowLine_endY( pBox->blueBox_yPos() - pFlowLine->flowLine_startY() + pInputTerminal->terminalYPos() +  pInputTerminal->terminalSize()   );
}




void  CFlowConnectionLine::bindFlowLineToOutputTerminal( CFlowConnectionLine * pFlowLine , COutputTerminal * pOutputTerminal ){
    ASSERTWITHINFO(pFlowLine);
    ASSERTWITHINFO(pOutputTerminal);
    pOutputTerminal->addFlowLineToConnectedList( pFlowLine );
    pFlowLine->setStartPoint( pOutputTerminal ) ;
}






