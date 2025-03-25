#ifndef CDATACOMPARISONLESS_H
#define CDATACOMPARISONLESS_H


#include <QObject>
#include "../OperationBox.h"


class CDataComparisonLess : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(QString operatorSymbol MEMBER m_operatorSymbol CONSTANT)
    friend class CDataComparisonLessFactory ;
    Q_DISABLE_COPY_MOVE(CDataComparisonLess)
    explicit CDataComparisonLess(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;
    
    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName  = "Less Than" ;
    inline const static QString    m_operatorSymbol = "<";
};




#endif // CDATACOMPARISONLESS_H
