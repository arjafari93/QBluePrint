#ifndef CTIMERSENDVALSRC_H
#define CTIMERSENDVALSRC_H

#include <QObject>
#include "../OperationBox.h"

#include <QTimer>

class CTimerSendValSrc : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(int sendValueInterval  READ sendValueInterval WRITE setSendValueInterval NOTIFY sendValueIntervalChanged)
    Q_PROPERTY(int valueToBeSentInt      MEMBER m_valueToBeSentInt      NOTIFY valueToBeSentIntChanged      )
    Q_PROPERTY(double valueToBeSentDouble   MEMBER m_valueToBeSentDouble   NOTIFY valueToBeSentDoubleChanged   )
    Q_PROPERTY(QString valueToBeSentString   MEMBER m_valueToBeSentString   NOTIFY valueToBeSentStringChanged   )
    Q_PROPERTY(bool valueToBeSentBool     MEMBER m_valueToBeSentBool     NOTIFY valueToBeSentBoolChanged     )

    friend class CTimerSendValSrcFactory ;
    Q_DISABLE_COPY_MOVE(CTimerSendValSrc);
    explicit CTimerSendValSrc(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation( ) override  ;

    virtual void serializeBoxInfoIntoJson( QJsonObject & jsonObj ) override ;
    virtual void deserializeBoxInfoFromJson( const QJsonObject & jsonObj ) override ;
    int     sendValueInterval() const {return m_sendValueInterval;}
    void    setSendValueInterval(const int & newValue ) ;

    GETUNIQUENAMEFUNC;

public slots:
    void              sendValueTimerTimeOut();


private:
    QTimer *        mp_sendValueTimer     = nullptr ;
    int             m_sendValueInterval   = 1000 ;
    int             m_valueToBeSentInt         ;
    double          m_valueToBeSentDouble      ;
    QString         m_valueToBeSentString      ;
    bool            m_valueToBeSentBool        ;
    inline const static QString    m_uniqueBoxName = "Send Source Timer" ;

signals:
    void             sendValueIntervalChanged();
    void             valueToBeSentIntChanged   () ;
    void             valueToBeSentDoubleChanged() ;
    void             valueToBeSentStringChanged() ;
    void             valueToBeSentBoolChanged  () ;
};

#endif // CTIMERSENDVALSRC_H
