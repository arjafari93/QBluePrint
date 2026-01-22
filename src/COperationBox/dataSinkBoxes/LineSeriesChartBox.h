#ifndef CLINESERIESCHARTBOX_H
#define CLINESERIESCHARTBOX_H

#include "../OperationBox.h"
#include "LiveDataXYModel.h"
#include <QLineSeries>
#include <QObject>
#include <QtQml>

class QVXYModelMapper;

class CLineSeriesChartBox : public COperationBox
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Provided in C++ only; it cannot be created in QML")
    Q_PROPERTY(CLiveDataXYModel* dataListModelInstace READ getDataListModelInstace CONSTANT)
    friend class CLineSeriesChartBoxFactory;
    Q_DISABLE_COPY_MOVE(CLineSeriesChartBox)
    explicit CLineSeriesChartBox(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent = nullptr);

  public:
    ~CLineSeriesChartBox();
    virtual void evaluateOperation() override;
    Q_INVOKABLE void setModelMapperLineSeries(QLineSeries* newLineSeries);
    Q_INVOKABLE CLiveDataXYModel* getDataListModelInstace() const { return mp_dataListModelInstace.get(); };
    GETUNIQUENAMEFUNC;

    virtual void serializeBoxInfoIntoJson(QJsonObject& jsonObj) override;
    virtual void deserializeBoxInfoFromJson(const QJsonObject& jsonObj) override;

  private:
    inline const static QString m_uniqueBoxName = "Line Series Chart";
    std::unique_ptr<QVXYModelMapper> mp_modelXYMapperLiveData;
    std::unique_ptr<CLiveDataXYModel> mp_dataListModelInstace;
};

#endif // CLINESERIESCHARTBOX_H
