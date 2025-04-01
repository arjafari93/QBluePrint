#ifndef CSTRINGOUTPUTSINK_H
#define CSTRINGOUTPUTSINK_H


#include <QObject>
#include "../OperationBox.h"

class CStringOutputSink : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(QString stringToBeDisplayed  MEMBER m_stringToBeDisplayed NOTIFY stringToBeDisplayedChanged)

    friend class CStringOutputSinkFactory ;
    Q_DISABLE_COPY_MOVE(CStringOutputSink)
    explicit CStringOutputSink(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;
    GETUNIQUENAMEFUNC;

private:
    QString                 m_stringToBeDisplayed = "";
    inline const static QString    m_uniqueBoxName = "String Sink OutPut" ;


signals:
    void stringToBeDisplayedChanged() ;
};

#endif // CSTRINGOUTPUTSINK_H
