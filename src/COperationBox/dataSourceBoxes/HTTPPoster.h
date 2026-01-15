#ifndef CHTTPPOSTER_H
#define CHTTPPOSTER_H

#include "HTTPBase.h"

class CHTTPPoster : public CHTTPBase
{
    Q_OBJECT

    friend class CHTTPPosterFactory;
    Q_DISABLE_COPY_MOVE(CHTTPPoster);
    explicit CHTTPPoster(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent = nullptr);

  public:
    virtual void evaluateOperation() override;
    ~CHTTPPoster();
    GETUNIQUENAMEFUNC;

  private:
    inline const static QString m_uniqueBoxName = "HTTP Post";
};

#endif // CHTTPPOSTER_H
