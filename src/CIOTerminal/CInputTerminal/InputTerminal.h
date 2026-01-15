#ifndef CINPUTTERMINAL_H
#define CINPUTTERMINAL_H

#include "../IOTerminal.h"
#include <QObject>

class CInputTerminal : public CIOTerminal
{
    Q_OBJECT
  public:
    explicit CInputTerminal(const int& terminalIndexInBox, COperationBox* parent);
    virtual ~CInputTerminal(){};
    void receivedValueFromFlowLine(const std::shared_ptr<CRawValueBase>& newValue);
};

#endif // CINPUTTERMINAL_H
