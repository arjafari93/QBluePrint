#ifndef CJSONPARSER_H
#define CJSONPARSER_H


#include <QObject>
#include "../OperationBox.h"


class CJsonParser : public COperationBox
{
    Q_OBJECT
    friend class CJsonParserFactory ;
    Q_DISABLE_COPY_MOVE(CJsonParser)
    explicit CJsonParser(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;

    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName  = "Json Parser" ;
};


#endif // CJSONPARSER_H
