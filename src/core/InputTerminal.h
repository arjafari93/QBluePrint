#ifndef CINPUTTERMINAL_H
#define CINPUTTERMINAL_H

#include "IOTerminal.h"
#include <QObject>
#include <QtQml>

class CInputTerminal : public CIOTerminal
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Provided in C++ only; it cannot be created in QML")
  public:
    explicit CInputTerminal(const int& terminalIndexInBox, COperationBox* parent);
    virtual ~CInputTerminal(){};
    void receivedValueFromFlowLine(const std::shared_ptr<CRawValueBase>& newValue);
};

#endif // CINPUTTERMINAL_H
