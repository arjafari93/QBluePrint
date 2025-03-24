#ifndef CLINESERIESCHARTBOX_H
#define CLINESERIESCHARTBOX_H

#include <QObject>
#include <QLineSeries>
#include "../OperationBox.h"
class CLiveDataXYModel ;
namespace QtCharts{
class QVXYModelMapper;
}

class CLineSeriesChartBox :  public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(CLiveDataXYModel* dataListModelInstace READ getDataListModelInstace CONSTANT)
    friend class CLineSeriesChartBoxFactory ;
    Q_DISABLE_COPY_MOVE(CLineSeriesChartBox)
    explicit CLineSeriesChartBox(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:
    ~CLineSeriesChartBox();
    virtual void  evaluateOperation(  ) override ;
    Q_INVOKABLE  void setModelMapperLineSeries( QtCharts::QLineSeries * newLineSeries  ) ;
    Q_INVOKABLE  CLiveDataXYModel* getDataListModelInstace(  ) const {return mp_dataListModelInstace.get(); } ;
    GETUNIQUENAMEFUNC;

    virtual void serializeBoxInfoIntoJson( QJsonObject & jsonObj ) override ;
    virtual void deserializeBoxInfoFromJson( const QJsonObject & jsonObj ) override ;

private:
    inline const static QString    m_uniqueBoxName  = "Line Series Chart" ;
    std::unique_ptr<QtCharts::QVXYModelMapper>      mp_modelXYMapperLiveData {nullptr};
    std::unique_ptr<CLiveDataXYModel>               mp_dataListModelInstace {nullptr};
};

#endif // CLINESERIESCHARTBOX_H
