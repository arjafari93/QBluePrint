#ifndef CTCPSOCKETSERVERSOURCE_H
#define CTCPSOCKETSERVERSOURCE_H

#include "../OperationBox.h"
#include <QObject>

#include <QAbstractSocket>
#include <QtQml>
struct QAbstractSocketQml
{
    Q_GADGET
    QML_FOREIGN(QAbstractSocket)
    QML_NAMED_ELEMENT(QAbstractSocket)
    QML_UNCREATABLE("Provided in C++ only; it cannot be created in QML")
};

class QTcpServer;

class CTCPSocketServerSource : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(int serverPortNum READ serverPortNum WRITE setServerPortNum NOTIFY serverPortNumChanged)

    friend class CTCPSocketServerSourceFactory;
    Q_DISABLE_COPY_MOVE(CTCPSocketServerSource);
    explicit CTCPSocketServerSource(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent = nullptr);

  public:
    virtual void evaluateOperation() override{};
    ~CTCPSocketServerSource();
    GETUNIQUENAMEFUNC;

    int serverPortNum() const;
    void setServerPortNum(int newServerPortNum);
    virtual void serializeBoxInfoIntoJson(QJsonObject& jsonObj) override;
    virtual void deserializeBoxInfoFromJson(const QJsonObject& jsonObj) override;

  private:
    int m_serverPortNum = 0;
    inline const static QString m_uniqueBoxName = "TCP Server";
    std::unique_ptr<QTcpServer> mp_tcpServer;

  signals:
    void serverPortNumChanged();
};

#endif // CTCPSOCKETSERVERSOURCE_H
