#ifndef CCONDITIONALBRANCH_H
#define CCONDITIONALBRANCH_H


#include <QObject>
#include "../OperationBox.h"


class CConditionalBranch : public COperationBox
{
    Q_OBJECT
    friend class CConditionalBranchFactory ;
    Q_DISABLE_COPY_MOVE(CConditionalBranch)
    explicit CConditionalBranch(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation( ) override ;
    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName  = "Conditional Branch" ;
};

#endif // CCONDITIONALBRANCH_H
