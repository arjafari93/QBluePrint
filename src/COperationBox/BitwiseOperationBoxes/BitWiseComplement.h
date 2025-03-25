#ifndef CBITWISECOMPLEMENT_H
#define CBITWISECOMPLEMENT_H


#include <QObject>
#include "../OperationBox.h"


class CBitWiseComplement : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(QString operatorSymbol MEMBER m_operatorSymbol CONSTANT)

    friend class CBitWiseComplementFactory ;
    Q_DISABLE_COPY_MOVE(CBitWiseComplement)
    explicit CBitWiseComplement(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );

public:

    virtual void  evaluateOperation(  ) override ;
    
    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName  = "BitWise Complement" ;
    inline const static QString    m_operatorSymbol = "~";
};

#endif // CBITWISECOMPLEMENT_H
