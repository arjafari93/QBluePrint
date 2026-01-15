#ifndef CLOGICALAND_H
#define CLOGICALAND_H

#include "../OperationBox.h"
#include <QObject>

class CLogicalAND : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(QString operatorSymbol MEMBER m_operatorSymbol CONSTANT)
    friend class CLogicalANDFactory;
    Q_DISABLE_COPY_MOVE(CLogicalAND)
    explicit CLogicalAND(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent = nullptr);

  public:
    virtual void evaluateOperation() override;

    GETUNIQUENAMEFUNC;

  private:
    inline const static QString m_uniqueBoxName = "Logical AND";
    inline const static QString m_operatorSymbol = "&&";
};

#endif // CLOGICALAND_H
