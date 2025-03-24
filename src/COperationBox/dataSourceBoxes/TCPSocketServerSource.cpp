#include "TCPSocketServerSource.h"


#include <memory>
#include <QTcpSocket>
#include <QTcpServer>
#include <QJsonObject>

#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "src/CRawValueBase/RawValueBase.h"

inline const static int blueBoxWidth  = 300 ;
inline const static int blueBoxHeight = 150 ;




CTCPSocketServerSource::CTCPSocketServerSource ( int newBlueBox_xPos, int newBlueBox_yPos, QObject *parent)
    : COperationBox{m_uniqueBoxName , newBlueBox_xPos  , newBlueBox_yPos  , blueBoxWidth , blueBoxHeight , parent }
{
    mp_tcpServer = std::make_unique<QTcpServer>();
    if (!mp_tcpServer->listen(QHostAddress::Any, 0)) {  // Pass 0 to get a random available port
        qDebug() << "Could not start server:" << mp_tcpServer->errorString();
        return;
    }
    m_serverPortNum = mp_tcpServer->serverPort();

    QObject::connect(mp_tcpServer.get(), &QTcpServer::newConnection, this, [this]() {
        QTcpSocket *pNextConnection = mp_tcpServer->nextPendingConnection();

        QObject::connect(pNextConnection, &QAbstractSocket::disconnected, pNextConnection, [pNextConnection]() {
            pNextConnection->deleteLater();  // Safe cleanup
        });

        QObject::connect(pNextConnection, &QIODevice::readyRead, this, [this , pNextConnection]() {
            if (!pNextConnection) return;  // Extra safety check
            QByteArray data = pNextConnection->readAll();
            m_listOfOutputTerminals.at(0)->sendValueToFlowLine(  std::make_shared<CValue_string>  (QString::fromUtf8(data) ));
        });
    });


    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_InputNetworkServer ;
    m_blueBox_HeaderIcon = "qrc:/Images/network.png" ;
    m_blueBox_HeadColor = QColor(255 , 44 , 90 );

    auto outPutNodeString = new COutputTerminal(0, this);
    outPutNodeString->setTerminalName("Data(String)");
    m_listOfOutputTerminals.push_back( outPutNodeString );

    m_blueBox_keyWords = "tcp , network, source, input";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_InputSource ;
}

CTCPSocketServerSource::~CTCPSocketServerSource()
{

}



int CTCPSocketServerSource::serverPortNum() const
{
    return m_serverPortNum;
}

void CTCPSocketServerSource::setServerPortNum(int newServerPortNum)
{
    if (m_serverPortNum == newServerPortNum)
        return;
    m_serverPortNum = newServerPortNum;
    emit serverPortNumChanged();
    if (mp_tcpServer) {
        mp_tcpServer->close();  // Stop the server
    }

    if (mp_tcpServer && !mp_tcpServer->listen(QHostAddress::Any, newServerPortNum)) {  // Start on a new port
        qDebug() << "Failed to change port:" << mp_tcpServer->errorString();
        return;
    }
}

void CTCPSocketServerSource::serializeBoxInfoIntoJson(QJsonObject &jsonObj)
{
    COperationBox::serializeBoxInfoIntoJson(jsonObj);
    jsonObj["Port"] = QString::number( m_serverPortNum ) ;
}

void CTCPSocketServerSource::deserializeBoxInfoFromJson(const QJsonObject &jsonObj)
{
    COperationBox::deserializeBoxInfoFromJson(jsonObj);
    m_serverPortNum = jsonObj["Port"].toString().toInt();
}


