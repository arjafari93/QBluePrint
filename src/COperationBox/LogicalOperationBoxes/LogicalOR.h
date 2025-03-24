#ifndef CLOGICALOR_H
#define CLOGICALOR_H



#include <QObject>
#include "../OperationBox.h"

#include <QString>

class CLogicalOR : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(QString operatorSymbol MEMBER m_operatorSymbol CONSTANT)
    friend class CLogicalORFactory ;
    Q_DISABLE_COPY_MOVE(CLogicalOR)
    explicit CLogicalOR(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;
    static Q_INVOKABLE  QString getOperatorSymbol() {return m_operatorSymbol;}
    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName  = "Logical OR" ;
    inline const static QString    m_operatorSymbol = "||";
};



#endif // CLOGICALOR_H
