#ifndef CUNIVERSALTYPECONVERTOR_H
#define CUNIVERSALTYPECONVERTOR_H

#include <QObject>
#include "../OperationBox.h"

class CUniversalTypeConvertor : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(QString selectedOutputType READ selectedOutputType WRITE setSelectedOutputType NOTIFY selectedOutputTypeChanged)
    friend class CUniversalTypeConvertorFactory ;
    Q_DISABLE_COPY_MOVE(CUniversalTypeConvertor)
    explicit CUniversalTypeConvertor(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;
    GETUNIQUENAMEFUNC;



    const QString &selectedOutputType() const;
    void setSelectedOutputType(const QString &newSelectedOutputType);

    virtual void serializeBoxInfoIntoJson( QJsonObject & jsonObj ) override ;
    virtual void deserializeBoxInfoFromJson( const QJsonObject & jsonObj ) override ;
signals:
    void selectedOutputTypeChanged();

private:
    inline const static QString    m_uniqueBoxName  = "Universal Convertor" ;
    QString                        m_selectedOutputType = "int";
};



#endif // CUNIVERSALTYPECONVERTOR_H
