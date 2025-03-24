#include "OutputTerminal.h"

#include "src/CFlowConnectionLine/FlowConnectionLine.h"



COutputTerminal::COutputTerminal(const int &terminalIndexInBox, COperationBox *parent)
    : CIOTerminal{ terminalIndexInBox , parent}
{
    connect(this , &COutputTerminal::terminalColorChanged , this , [this](){
        for( auto iter : m_listOfConnectedLines ){
            iter->setFlowLine_color(m_terminalColor);
        }
    });
}

void COutputTerminal::sendValueToFlowLine(std::shared_ptr<CRawValueBase> valueToBeSent)
{
    emit nodeIsPassingNewValue();
    setTerminalCurrentData(valueToBeSent );
    // we have to find conncted flow lines and pass the value to those flow lines
    for(int iter = 0 ; iter < m_listOfConnectedLines.length() ; iter++ ){
        m_listOfConnectedLines.at(iter)->passValueToEndPoint( valueToBeSent ) ;
    }
}

