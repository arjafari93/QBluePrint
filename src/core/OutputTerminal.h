#ifndef COUTPUTTERMINAL_H
#define COUTPUTTERMINAL_H

#include "IOTerminal.h"
#include <QObject>
#include <QtQml>

class COutputTerminal : public CIOTerminal
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Provided in C++ only; it cannot be created in QML")
  public:
    explicit COutputTerminal(const int& terminalIndexInBox, COperationBox* parent);
    virtual ~COutputTerminal(){};

    void sendValueToFlowLine(const std::shared_ptr<CRawValueBase>& valueToBeSent);
};

#endif // COUTPUTTERMINAL_H
