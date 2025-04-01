#ifndef CMATHMULTIPLICATION_H
#define CMATHMULTIPLICATION_H

#include <QObject>
#include "../OperationBox.h"

class CMathMultiplication : public COperationBox
{
    Q_OBJECT
    friend class CMathMultiplicationFactory ;
    Q_DISABLE_COPY_MOVE(CMathMultiplication)
    explicit CMathMultiplication(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(   ) override ;



    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName = "Math Multiplication" ;

};




#endif // CMATHMULTIPLICATION_H
