#ifndef CFINEINARRAY_H
#define CFINEINARRAY_H



#include <QObject>
#include "../OperationBox.h"

class CFineInArray : public COperationBox
{
    Q_OBJECT
    friend class CFineInArrayFactory ;
    Q_DISABLE_COPY_MOVE(CFineInArray)
    explicit CFineInArray(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:
    ~CFineInArray();
    virtual void  evaluateOperation(  ) override ;
    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName  = "Find In Array" ;

};

#endif // CFINEINARRAY_H
