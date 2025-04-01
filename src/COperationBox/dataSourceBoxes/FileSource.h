#ifndef CFILESOURCE_H
#define CFILESOURCE_H


#include <QObject>
#include "../OperationBox.h"


class CFileSource : public COperationBox
{
    Q_OBJECT
    friend class CFileSourceFactory ;
    Q_DISABLE_COPY_MOVE(CFileSource);
    explicit CFileSource(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation( ) override  ;
    ~CFileSource();
    GETUNIQUENAMEFUNC;

private:
    inline const static QString    m_uniqueBoxName = "File Source" ;

};


#endif // CFILESOURCE_H
