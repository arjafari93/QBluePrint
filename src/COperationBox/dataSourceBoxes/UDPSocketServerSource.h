#ifndef CUDPSOCKETSERVERSOURCE_H
#define CUDPSOCKETSERVERSOURCE_H


#include <QObject>
#include "../OperationBox.h"


class QUdpSocket;

class CUDPSocketServerSource : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(int serverPortNum READ serverPortNum WRITE setServerPortNum NOTIFY serverPortNumChanged)

    friend class CUDPSocketServerSourceFactory ;
    Q_DISABLE_COPY_MOVE(CUDPSocketServerSource);
    explicit CUDPSocketServerSource(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:

    virtual void  evaluateOperation( ) override {} ;
    ~CUDPSocketServerSource();
    GETUNIQUENAMEFUNC;

    int serverPortNum() const;
    void setServerPortNum(int newServerPortNum);
    virtual void serializeBoxInfoIntoJson( QJsonObject & jsonObj ) override ;
    virtual void deserializeBoxInfoFromJson( const QJsonObject & jsonObj ) override ;

private:
    int  m_serverPortNum = 0 ;
    inline const static QString    m_uniqueBoxName = "UDP Server" ;
    std::unique_ptr< QUdpSocket>   mp_udpServer{nullptr};

signals:
    void  serverPortNumChanged       () ;
};


#endif // CUDPSOCKETSERVERSOURCE_H
