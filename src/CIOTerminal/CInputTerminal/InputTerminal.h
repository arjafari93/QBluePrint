#ifndef CINPUTTERMINAL_H
#define CINPUTTERMINAL_H

#include <QObject>
#include "../IOTerminal.h"



class CInputTerminal : public CIOTerminal
{
    Q_OBJECT
public:
    explicit CInputTerminal( const int &terminalIndexInBox, COperationBox *parent );
    virtual ~CInputTerminal(){};
    void    receivedValueFromFlowLine( std::shared_ptr<CRawValueBase> newValue );

};

#endif // CINPUTTERMINAL_H
