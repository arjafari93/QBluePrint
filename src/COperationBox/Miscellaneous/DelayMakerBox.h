#ifndef CDELAYMAKERBOX_H
#define CDELAYMAKERBOX_H

#include "../OperationBox.h"
#include <QObject>
#include <deque>

class QTimer;
class CRawValueBase;
class CDelayMakerBox : public COperationBox
{
    Q_OBJECT
    friend class CDelayMakerBoxFactory;
    Q_DISABLE_COPY_MOVE(CDelayMakerBox)
    explicit CDelayMakerBox(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent = nullptr);

  public:
    ~CDelayMakerBox();
    virtual void evaluateOperation() override;
    GETUNIQUENAMEFUNC;

    virtual void deserializeBoxInfoFromJson(const QJsonObject& jsonObj) override;

  private:
    inline const static QString m_uniqueBoxName = "Delay/Queue";
    QTimer* mp_sendValueTimer = nullptr;
    int m_msDelay = 10;
    std::deque<std::shared_ptr<CRawValueBase>> m_valuesToBeSent;
};

#endif // CDELAYMAKERBOX_H
