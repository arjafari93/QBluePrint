#ifndef CBITWISELEFTSHIFT_H
#define CBITWISELEFTSHIFT_H



#include <QObject>
#include "../OperationBox.h"


class CBitWiseLeftShift : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(QString operatorSymbol MEMBER m_operatorSymbol CONSTANT)

    friend class CBitWiseLeftShiftFactory ;
    Q_DISABLE_COPY_MOVE(CBitWiseLeftShift)
    explicit CBitWiseLeftShift(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );

public:

    virtual void  evaluateOperation(  ) override ;
    static Q_INVOKABLE  QString getOperatorSymbol() {return m_operatorSymbol;}
    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName  = "BitWise Left Shift" ;
    inline const static QString    m_operatorSymbol = "<<";
};

#endif // CBITWISELEFTSHIFT_H
