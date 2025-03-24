#ifndef CMATHSUBTRACTION_H
#define CMATHSUBTRACTION_H



#include <QObject>
#include "../OperationBox.h"


class CMathSubtraction : public COperationBox
{
    Q_OBJECT
    friend class CMathSubtractionFactory ;
    Q_DISABLE_COPY_MOVE(CMathSubtraction)
    explicit CMathSubtraction(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;

    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName = "Math Subtraction" ;

};



#endif // CMATHSUBTRACTION_H
