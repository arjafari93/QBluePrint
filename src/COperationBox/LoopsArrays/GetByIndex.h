#ifndef CGETBYINDEX_H
#define CGETBYINDEX_H

#include "../OperationBox.h"
#include <QObject>

class CGetByIndex : public COperationBox
{
    Q_OBJECT
    friend class CGetByIndexFactory;
    Q_DISABLE_COPY_MOVE(CGetByIndex)
    explicit CGetByIndex(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent = nullptr);

  public:
    ~CGetByIndex();
    virtual void evaluateOperation() override;
    GETUNIQUENAMEFUNC;

  private:
    inline const static QString m_uniqueBoxName = "Get By Index";
};

#endif // CGETBYINDEX_H
