#ifndef CFOREACHLOOP_H
#define CFOREACHLOOP_H

#include <QObject>
#include "../OperationBox.h"

class CForEachLoop : public COperationBox
{
    Q_OBJECT
    friend class CForEachLoopFactory ;
    Q_DISABLE_COPY_MOVE(CForEachLoop)
    explicit CForEachLoop(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:
    ~CForEachLoop();
    virtual void  evaluateOperation(  ) override ;
    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName  = "For Each Loop" ;

};

#endif // CFOREACHLOOP_H
