#ifndef CMATHABSOLUTE_H
#define CMATHABSOLUTE_H

#include "../OperationBox.h"
#include <QObject>

class CMathAbsolute : public COperationBox
{
    Q_OBJECT
    friend class CMathAbsoluteFactory;
    Q_DISABLE_COPY_MOVE(CMathAbsolute)
    explicit CMathAbsolute(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent = nullptr);

  public:
    virtual void evaluateOperation() override;
    GETUNIQUENAMEFUNC;

  private:
    inline const static QString m_uniqueBoxName = "Math Absolute";
};

#endif // CMATHABSOLUTE_H
