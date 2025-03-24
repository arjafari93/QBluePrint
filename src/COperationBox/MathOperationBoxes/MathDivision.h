#ifndef CMATHDIVISION_H
#define CMATHDIVISION_H



#include <QObject>
#include "../OperationBox.h"


class CMathDivision : public COperationBox
{
    Q_OBJECT
    friend class CMathDivisionFactory ;
    Q_DISABLE_COPY_MOVE(CMathDivision)
    explicit CMathDivision(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;

    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName = "Math Devision" ;

};


#endif // CMATHDIVISION_H
