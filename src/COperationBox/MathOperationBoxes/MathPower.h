#ifndef CMATHPOWER_H
#define CMATHPOWER_H



#include <QObject>
#include "../OperationBox.h"


class CMathPower : public COperationBox
{
    Q_OBJECT
    friend class CMathPowerFactory ;
    Q_DISABLE_COPY_MOVE(CMathPower)
    explicit CMathPower(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;

    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName = "Math Power" ;

};

#endif // CMATHPOWER_H
