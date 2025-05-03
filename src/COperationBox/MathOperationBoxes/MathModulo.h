#ifndef CMATHMODULO_H
#define CMATHMODULO_H

#include <QObject>
#include "../OperationBox.h"

class CMathModulo : public COperationBox
{
    Q_OBJECT
    friend class CMathModuloFactory ;
    Q_DISABLE_COPY_MOVE(CMathModulo)
    explicit CMathModulo(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;

    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName = "Math Modulo" ;

};

#endif // CMATHMODULO_H
