#ifndef CLOGICALNOT_H
#define CLOGICALNOT_H


#include <QObject>
#include "../OperationBox.h"


class CLogicalNOT : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(QString operatorSymbol MEMBER m_operatorSymbol CONSTANT)
    friend class CLogicalNOTFactory ;
    Q_DISABLE_COPY_MOVE(CLogicalNOT)
    explicit CLogicalNOT(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;
    static Q_INVOKABLE  QString getOperatorSymbol() {return m_operatorSymbol;}
    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName  = "Logical NOT" ;
    inline const static QString    m_operatorSymbol = "!";
};



#endif // CLOGICALNOT_H
