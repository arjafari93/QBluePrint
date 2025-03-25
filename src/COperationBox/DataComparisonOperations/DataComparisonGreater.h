#ifndef CDATACOMPARISONGREATER_H
#define CDATACOMPARISONGREATER_H

#include <QObject>
#include "../OperationBox.h"


class CDataComparisonGreater : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(QString operatorSymbol MEMBER m_operatorSymbol CONSTANT)
    friend class CDataComparisonGreaterFactory ;
    Q_DISABLE_COPY_MOVE(CDataComparisonGreater)
    explicit CDataComparisonGreater(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;
    
    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName  = "Greater Than" ;
    inline const static QString    m_operatorSymbol = ">";
};




#endif // CDATACOMPARISONGREATER_H
