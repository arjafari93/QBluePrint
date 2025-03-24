#ifndef CSOCKETCLIENTSINK_H
#define CSOCKETCLIENTSINK_H


#include <QObject>
#include <QAbstractSocket>
#include "../OperationBox.h"



class CSocketClientSink : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(int remotePortNum READ remotePortNum WRITE setRemotePortNum NOTIFY remotePortNumChanged)
    Q_PROPERTY(QAbstractSocket::SocketType socketType READ socketType CONSTANT)
    Q_PROPERTY(QAbstractSocket::SocketState clientSocketState READ clientSocketState WRITE setClientSocketState NOTIFY clientSocketStateChanged)
    Q_PROPERTY(QString remoteServerIPAddress READ remoteServerIPAddress WRITE setRemoteServerIPAddress NOTIFY remoteServerIPAddressChanged)

    friend class CTCPSocketClientSinkFactory ;
    friend class CUDPSocketClientSinkFactory ;
    Q_DISABLE_COPY_MOVE(CSocketClientSink)
    explicit CSocketClientSink(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QAbstractSocket::SocketType sockType ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation(  ) override ;

    int remotePortNum() const;
    void setRemotePortNum(int newremotePortNum);

    const QAbstractSocket::SocketState &clientSocketState() const;

    Q_INVOKABLE void clientConnectionBtnClicked();
    const QString &remoteServerIPAddress() const;
    void setRemoteServerIPAddress(const QString &newremoteServerIPAddress);

    const QAbstractSocket::SocketType &socketType() const;

    virtual void serializeBoxInfoIntoJson( QJsonObject & jsonObj ) override ;
    virtual void deserializeBoxInfoFromJson( const QJsonObject & jsonObj ) override ;

public slots:
    void setClientSocketState(const QAbstractSocket::SocketState &newClientSockState);

private:
    int                                 m_remotePortNum = 4321;
    std::unique_ptr<QAbstractSocket>    mp_clientSocket {nullptr};
    QAbstractSocket::SocketType         m_socketType = QAbstractSocket::UnknownSocketType;
    QAbstractSocket::SocketState        m_clientSocketState;
    QString                             m_remoteServerIPAddress = "127.0.1.1";



signals:

    void remotePortNumChanged();
    void clientSocketStateChanged();
    void remoteServerIPAddressChanged();
};




#endif // CSOCKETCLIENTSINK_H
