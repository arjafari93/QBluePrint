#ifndef CDATACOUNTER_H
#define CDATACOUNTER_H


#include <QObject>
#include "../OperationBox.h"



class CDataCounter : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(QString operatorSymbol MEMBER m_operatorSymbol NOTIFY operatorSymbolChanged )
    friend class CDataCounterFactory ;
    Q_DISABLE_COPY_MOVE(CDataCounter)
    explicit CDataCounter(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:
    ~CDataCounter();
    virtual void  evaluateOperation(  ) override ;
    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName  = "Data Counter" ;
    QString    m_operatorSymbol = "#";
    long long m_initialValue = 0 ;
    long long m_dataCounter = 0;
    long long m_stepSize = 1;

signals:
    void operatorSymbolChanged();
};



#endif // CDATACOUNTER_H
