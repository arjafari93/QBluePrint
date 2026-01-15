#ifndef CPARSEINTOARRAY_H
#define CPARSEINTOARRAY_H

#include "../OperationBox.h"
#include <QObject>

class CParseIntoArray : public COperationBox
{
    Q_OBJECT
    friend class CParseIntoArrayFactory;
    Q_DISABLE_COPY_MOVE(CParseIntoArray)
    explicit CParseIntoArray(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent = nullptr);

  public:
    virtual void evaluateOperation() override;

    GETUNIQUENAMEFUNC;

  private:
    inline const static QString m_uniqueBoxName = "Parse Into Array";
};

#endif // CPARSEINTOARRAY_H
