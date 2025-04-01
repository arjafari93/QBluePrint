#ifndef CMATHMODULUS_H
#define CMATHMODULUS_H

#include <QObject>
#include "../OperationBox.h"

class CMathModulus : public COperationBox
{
    Q_OBJECT
    friend class CMathModulusFactory ;
    Q_DISABLE_COPY_MOVE(CMathModulus)
    explicit CMathModulus(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;

    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName = "Math Modulus" ;

};

#endif // CMATHMODULUS_H
