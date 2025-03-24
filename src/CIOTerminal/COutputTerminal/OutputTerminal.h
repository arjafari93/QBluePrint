#ifndef COUTPUTTERMINAL_H
#define COUTPUTTERMINAL_H

#include <QObject>
#include "../IOTerminal.h"



class COutputTerminal : public CIOTerminal
{
    Q_OBJECT
public:
    explicit COutputTerminal( const int &terminalIndexInBox, COperationBox *parent );
    virtual ~COutputTerminal(){};

    void     sendValueToFlowLine( std::shared_ptr<CRawValueBase> valueToBeSent );

};

#endif // COUTPUTTERMINAL_H
