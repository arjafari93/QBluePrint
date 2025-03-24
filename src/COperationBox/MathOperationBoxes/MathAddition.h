#ifndef CMATHADDITION_H
#define CMATHADDITION_H




#include <QObject>
#include "../OperationBox.h"


class CMathAddition : public COperationBox
{
    Q_OBJECT
    friend class CMathAdditionFactory ;
    Q_DISABLE_COPY_MOVE(CMathAddition)
    explicit CMathAddition(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;

    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName = "Math Addition" ;

};





#endif // CMATHADDITION_H
