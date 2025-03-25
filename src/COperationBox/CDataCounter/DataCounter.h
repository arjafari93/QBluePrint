#ifndef CDATACOUNTER_H
#define CDATACOUNTER_H


#include <QObject>
#include "../OperationBox.h"

class CValue_int;

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

    virtual void  evaluateOperation(  ) override ;

    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName  = "Data Counter" ;
    QString    m_operatorSymbol = "#";
    std::unique_ptr<CValue_int> mp_resetValue {nullptr};
    long long m_dataCounter = 0;
    long long m_stepSize = 1;

signals:
    void operatorSymbolChanged();
};



#endif // CDATACOUNTER_H
