#ifndef CARRAYLENGTH_H
#define CARRAYLENGTH_H


#include <QObject>
#include "../OperationBox.h"

class CArrayLength : public COperationBox
{
    Q_OBJECT
    friend class CArrayLengthFactory ;
    Q_DISABLE_COPY_MOVE(CArrayLength)
    explicit CArrayLength(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:
    ~CArrayLength();
    virtual void  evaluateOperation(  ) override ;
    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName  = "Array Length" ;

};

#endif // CARRAYLENGTH_H
