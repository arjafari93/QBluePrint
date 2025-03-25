#ifndef CDATACOMPARATOR_H
#define CDATACOMPARATOR_H




#include <QObject>
#include "../OperationBox.h"


class CDataComparisonEqual : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(QString operatorSymbol MEMBER m_operatorSymbol CONSTANT)
    friend class CDataComparisonEqualFactory ;
    Q_DISABLE_COPY_MOVE(CDataComparisonEqual)
    explicit CDataComparisonEqual(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;
    
    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName  = "Equality" ;
    inline const static QString    m_operatorSymbol = "==";
};





#endif // CDATACOMPARATOR_H
