#ifndef CBITWISEOR_H
#define CBITWISEOR_H



#include <QObject>
#include "../OperationBox.h"


class CBitWiseOR : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(QString operatorSymbol MEMBER m_operatorSymbol CONSTANT)

    friend class CBitWiseORFactory ;
    Q_DISABLE_COPY_MOVE(CBitWiseOR)
    explicit CBitWiseOR(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;
    static Q_INVOKABLE  QString getOperatorSymbol() {return m_operatorSymbol;}
    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName  = "BitWise OR" ;
    inline const static QString    m_operatorSymbol = "|";
};


#endif // CBITWISEOR_H
