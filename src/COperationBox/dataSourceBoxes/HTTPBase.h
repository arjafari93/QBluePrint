#ifndef CHTTPBASE_H
#define CHTTPBASE_H

#include "../OperationBox.h"
#include <QMap>
#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class CHTTPRawHeaderFormat : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString headerName READ headerName WRITE setHeaderName NOTIFY headerNameChanged)
    Q_PROPERTY(QString headerValue READ headerValue WRITE setHeaderValue NOTIFY headerValueChanged)
    Q_DISABLE_COPY_MOVE(CHTTPRawHeaderFormat);

  public:
    explicit CHTTPRawHeaderFormat(const QString& hdrKey, const QString& hdrVal) : m_headerName{hdrKey}, m_headerValue{hdrVal} {};
    const QString& headerName() const;
    void setHeaderName(const QString& newHeaderName);
    const QString& headerValue() const;
    void setHeaderValue(const QString& newHeaderValue);

  private:
    QString m_headerName = "";
    QString m_headerValue = "";

  signals:
    void headerNameChanged();
    void headerValueChanged();
};

class CHTTPBase : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<CHTTPRawHeaderFormat> listOfRawHeaders READ listOfRawHeaders NOTIFY listOfRawHeadersChanged)

    friend class CHTTPBaseFactory;
    Q_DISABLE_COPY_MOVE(CHTTPBase);

  protected:
    explicit CHTTPBase(int newBlueBox_xPos, int newBlueBox_yPos, const QString& uniqueBoxName, QObject* parent = nullptr);
  protected slots:
    virtual void httpReceptionFinished(QNetworkReply* reply);

  public:
    ~CHTTPBase();
    Q_INVOKABLE void addNewPairToRawHeaderList();                         // called from qml side and adds empty pair
    Q_INVOKABLE void removePairFromRawHeaderList(const int& indexOfItem); // called from qml side and removes the pair

    virtual void serializeBoxInfoIntoJson(QJsonObject& jsonObj) override;
    virtual void deserializeBoxInfoFromJson(const QJsonObject& jsonObj) override;
    QQmlListProperty<CHTTPRawHeaderFormat> listOfRawHeaders();

  protected:
    QNetworkAccessManager* mp_networkMngr = nullptr;
    QList<CHTTPRawHeaderFormat*> m_listOfRawHeaders;

  signals:
    void listOfRawHeadersChanged();
};

#endif // CHTTPBASE_H
