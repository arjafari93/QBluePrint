#ifndef CBITWISEAND_H
#define CBITWISEAND_H


#include <QObject>
#include "../OperationBox.h"


class CBitWiseAND : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(QString operatorSymbol MEMBER m_operatorSymbol CONSTANT)

    friend class CBitWiseANDFactory ;
    Q_DISABLE_COPY_MOVE(CBitWiseAND)
    explicit CBitWiseAND(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;
    static Q_INVOKABLE  QString getOperatorSymbol() {return m_operatorSymbol;}
    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName  = "BitWise AND" ;
    inline const static QString    m_operatorSymbol = "&";
};




#endif // CBITWISEAND_H
