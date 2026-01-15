#ifndef CBUTTONSOURCE_H
#define CBUTTONSOURCE_H

#include "../OperationBox.h"
#include <QObject>

class CButtonSource : public COperationBox
{
    Q_OBJECT

    friend class CButtonSourceFactory;
    Q_DISABLE_COPY_MOVE(CButtonSource);
    explicit CButtonSource(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent = nullptr);

  public:
    virtual void evaluateOperation() override;
    ~CButtonSource();
    GETUNIQUENAMEFUNC;

  private:
    inline const static QString m_uniqueBoxName = "Button";

  signals:
};

#endif // CBUTTONSOURCE_H
