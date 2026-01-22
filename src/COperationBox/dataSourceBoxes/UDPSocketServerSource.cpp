#include "UDPSocketServerSource.h"

#include <QJsonObject>
#include <QUdpSocket>
#include <memory>

#include "OutputTerminal.h"
#include "RawValueBase.h"

CUDPSocketServerSource::CUDPSocketServerSource(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent)
    : COperationBox{m_uniqueBoxName, newBlueBox_xPos, newBlueBox_yPos, blueBoxWidth + 80, blueBoxHeight + 30, parent}, mp_udpServer{nullptr}
{
    mp_udpServer = std::make_unique<QUdpSocket>(this);
    mp_udpServer->bind(QHostAddress::Any, 0, QAbstractSocket::DefaultForPlatform);

    connect(mp_udpServer.get(), &QUdpSocket::readyRead, this, [this]() {
        while (mp_udpServer->hasPendingDatagrams())
        {
            QByteArray dataBuffer;
            dataBuffer.resize(mp_udpServer->pendingDatagramSize());
            mp_udpServer->readDatagram(dataBuffer.data(), dataBuffer.size());
            m_listOfOutputTerminals.at(0)->sendValueToFlowLine(std::make_shared<CValue_string>(QString::fromUtf8(dataBuffer)));
        }
    });

    m_serverPortNum = mp_udpServer->localPort();

    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_InputNetworkServer;
    m_blueBox_HeaderIcon = "qrc:/Images/network.png";
    m_blueBox_HeadColor = QColor(224, 45, 255);

    auto outPutNodeString = new COutputTerminal(0, this);
    outPutNodeString->setTerminalName("Data(String)");
    m_listOfOutputTerminals.push_back(outPutNodeString);

    m_blueBox_keyWords = "udp , network, source, input";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_InputSource;
}

CUDPSocketServerSource::~CUDPSocketServerSource() {}

int CUDPSocketServerSource::serverPortNum() const { return m_serverPortNum; }

void CUDPSocketServerSource::setServerPortNum(int newServerPortNum)
{
    if (m_serverPortNum == newServerPortNum)
        return;
    m_serverPortNum = newServerPortNum;
    emit serverPortNumChanged();
    if (mp_udpServer)
    {
        mp_udpServer->close(); // Stop the server
    }

    if (mp_udpServer && !mp_udpServer->bind(QHostAddress::Any, newServerPortNum, QAbstractSocket::DefaultForPlatform))
    { // Start on a new port
        qDebug() << "Failed to change port:" << mp_udpServer->errorString();
        return;
    }
}

void CUDPSocketServerSource::serializeBoxInfoIntoJson(QJsonObject& jsonObj)
{
    COperationBox::serializeBoxInfoIntoJson(jsonObj);
    jsonObj["Port"] = QString::number(m_serverPortNum);
}

void CUDPSocketServerSource::deserializeBoxInfoFromJson(const QJsonObject& jsonObj)
{
    COperationBox::deserializeBoxInfoFromJson(jsonObj);
    m_serverPortNum = jsonObj["Port"].toString().toInt();
}
