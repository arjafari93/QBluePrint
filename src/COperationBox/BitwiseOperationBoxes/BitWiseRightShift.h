#ifndef CBITWISERIGHTSHIFT_H
#define CBITWISERIGHTSHIFT_H

#include "../OperationBox.h"
#include <QObject>

class CBitWiseRightShift : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(QString operatorSymbol MEMBER m_operatorSymbol CONSTANT)
  public:
    Q_DISABLE_COPY_MOVE(CBitWiseRightShift)
    explicit CBitWiseRightShift(QObject* parent = nullptr) = delete;
    explicit CBitWiseRightShift(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent = nullptr);

    virtual void evaluateOperation() override;

    GETUNIQUENAMEFUNC;

  private:
    inline const static QString m_uniqueBoxName = "BitWise Right Shift";
    inline const static QString m_operatorSymbol = ">>";
};

#endif // CBITWISERIGHTSHIFT_H
