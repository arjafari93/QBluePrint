#ifndef CBITWISEXOR_H
#define CBITWISEXOR_H


#include <QObject>
#include "../OperationBox.h"


class CBitWiseXOR : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(QString operatorSymbol MEMBER m_operatorSymbol CONSTANT)

    friend class CBitWiseXORFactory ;
    Q_DISABLE_COPY_MOVE(CBitWiseXOR)
    explicit CBitWiseXOR(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;
    
    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName  = "BitWise XOR" ;
    inline const static QString    m_operatorSymbol = "^";
};


#endif // CBITWISEXOR_H
