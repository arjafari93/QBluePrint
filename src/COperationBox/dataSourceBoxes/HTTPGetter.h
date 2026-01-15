#ifndef CHTTPGetter_H
#define CHTTPGetter_H

#include "HTTPBase.h"

class CHTTPGetter : public CHTTPBase
{
    Q_OBJECT

    friend class CHTTPGetterFactory;
    Q_DISABLE_COPY_MOVE(CHTTPGetter);
    explicit CHTTPGetter(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent = nullptr);

  public:
    virtual void evaluateOperation() override;
    ~CHTTPGetter();
    GETUNIQUENAMEFUNC;

  private:
    inline const static QString m_uniqueBoxName = "HTTP Get";
};

#endif // CHTTPGetter_H
