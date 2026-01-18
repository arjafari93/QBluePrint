#include "CSocketClientSink.h"

#include <QJsonObject>
#include <QTcpSocket>
#include <QUdpSocket>

#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"

#include "src/CRawValueBase/RawValueBase.h"

CSocketClientSink::CSocketClientSink(int newBlueBox_xPos, int newBlueBox_yPos, QAbstractSocket::SocketType sockType, QObject* parent)
    : COperationBox{sockType == QAbstractSocket::TcpSocket ? "TCP Client" : "UDP Client", newBlueBox_xPos, newBlueBox_yPos, blueBoxWidth + 80, blueBoxHeight + 110, parent}
{
    m_socketType = sockType;
    if (m_socketType == QAbstractSocket::TcpSocket)
    {
        m_blueBox_HeadColor = QColor(140, 200, 200);
        mp_clientSocket = std::make_unique<QTcpSocket>(this);
        connect(mp_clientSocket.get(), &QTcpSocket::readyRead, this, [this]() {
            QByteArray data = mp_clientSocket->readAll();
            m_listOfOutputTerminals.at(0)->sendValueToFlowLine(std::make_shared<CValue_string>(QString::fromUtf8(data)));
        });
    }
    else if (m_socketType == QAbstractSocket::UdpSocket)
    {
        m_blueBox_HeadColor = QColor(60, 60, 240);
        mp_clientSocket = std::make_unique<QUdpSocket>(this);
        auto pUdpSock = dynamic_cast<QUdpSocket*>(mp_clientSocket.get());
        connect(pUdpSock, &QUdpSocket::readyRead, this, [this, pUdpSock]() {
            while (pUdpSock->hasPendingDatagrams())
            {
                QByteArray dataBuffer;
                dataBuffer.resize(pUdpSock->pendingDatagramSize());
                pUdpSock->readDatagram(dataBuffer.data(), dataBuffer.size());
                m_listOfOutputTerminals.at(0)->sendValueToFlowLine(std::make_shared<CValue_string>(QString::fromUtf8(dataBuffer)));
            }
        });
    }
    else
    {
        DEBUG_MSG_PRINT << " invalid socket type " << sockType;
    }

    connect(mp_clientSocket.get(), SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(setClientSocketState(QAbstractSocket::SocketState)));

    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_OutputSinkNetworkClient;
    m_blueBox_HeaderIcon = "qrc:/Images/network.png";
    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("Input");
    m_listOfInputTerminals.push_back(inputNode1);
    auto outPutNode = new COutputTerminal(0, this);
    outPutNode->setTerminalName("Out");
    m_listOfOutputTerminals.push_back(outPutNode);
    m_blueBox_keyWords = "output, out put, sink, tcp, udp,  client ";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_OutPutSink;
}

void CSocketClientSink::evaluateOperation()
{
    if (!mp_clientSocket)
        return;
    if (m_socketType == QAbstractSocket::TcpSocket && mp_clientSocket->state() != QTcpSocket::ConnectedState)
    {
        return;
    }
    auto inputData = m_listOfInputTerminals.at(0)->terminalCurrentData().get();
    QString resultString = "";
    if (auto* pVal = dynamic_cast<CValue_int*>(inputData))
    {
        resultString = QString::number(pVal->value());
    }
    else if (auto* pVal = dynamic_cast<CValue_double*>(inputData))
    {
        resultString = QString::number(pVal->value(), 'f', MAX_DOUBLE_PRECISION);
    }
    else if (auto* pVal = dynamic_cast<CValue_string*>(inputData))
    {
        resultString = pVal->value();
    }
    else if (auto* pVal = dynamic_cast<CValue_bool*>(inputData))
    {
        resultString = QString::number(pVal->value());
    }
    else if (auto* pVal = dynamic_cast<CValue_array*>(inputData))
    {
        resultString = pVal->convertToString();
    }
    if (m_socketType == QAbstractSocket::TcpSocket)
    {
        mp_clientSocket->write(resultString.toUtf8());
    }
    else if (m_socketType == QAbstractSocket::UdpSocket)
    {
        auto pUdpSock = dynamic_cast<QUdpSocket*>(mp_clientSocket.get());
        pUdpSock->writeDatagram(resultString.toUtf8(), QHostAddress(m_remoteServerIPAddress), m_remotePortNum);
    }
}

int CSocketClientSink::remotePortNum() const { return m_remotePortNum; }

void CSocketClientSink::setRemotePortNum(int newremotePortNum)
{
    if (m_remotePortNum == newremotePortNum)
        return;
    m_remotePortNum = newremotePortNum;
    emit remotePortNumChanged();
    if (mp_clientSocket->state() == QTcpSocket::ConnectedState)
    {
        mp_clientSocket->abort();
    }
}

const QAbstractSocket::SocketState& CSocketClientSink::clientSocketState() const { return m_clientSocketState; }

void CSocketClientSink::setClientSocketState(const QAbstractSocket::SocketState& newClientSockState)
{
    if (m_clientSocketState == newClientSockState)
        return;
    m_clientSocketState = newClientSockState;
    emit clientSocketStateChanged();
}

const QAbstractSocket::SocketType& CSocketClientSink::socketType() const { return m_socketType; }

void CSocketClientSink::serializeBoxInfoIntoJson(QJsonObject& jsonObj)
{
    COperationBox::serializeBoxInfoIntoJson(jsonObj);
    jsonObj["remotePort"] = QString::number(m_remotePortNum);
    jsonObj["remoteIP"] = m_remoteServerIPAddress;
    jsonObj["socketType"] = QString::number(static_cast<int>(m_socketType));
}

void CSocketClientSink::deserializeBoxInfoFromJson(const QJsonObject& jsonObj)
{
    COperationBox::deserializeBoxInfoFromJson(jsonObj);
    m_remotePortNum = jsonObj["remotePort"].toString().toInt();
    m_remoteServerIPAddress = jsonObj["remoteIP"].toString();
    m_socketType = static_cast<QAbstractSocket::SocketType>(jsonObj["socketType"].toString().toInt());
}

void CSocketClientSink::clientConnectionBtnClicked()
{
    ASSERTWITHINFO(mp_clientSocket);
    if (mp_clientSocket->state() == QTcpSocket::ConnectedState)
    {
        mp_clientSocket->abort();
    }
    else if (mp_clientSocket->state() == QTcpSocket::UnconnectedState)
    {
        mp_clientSocket->connectToHost(m_remoteServerIPAddress, m_remotePortNum);
    }
}

const QString& CSocketClientSink::remoteServerIPAddress() const { return m_remoteServerIPAddress; }

void CSocketClientSink::setRemoteServerIPAddress(const QString& newremoteServerIPAddress)
{
    if (m_remoteServerIPAddress == newremoteServerIPAddress)
        return;
    m_remoteServerIPAddress = newremoteServerIPAddress;
    emit remoteServerIPAddressChanged();
    if (mp_clientSocket->state() == QTcpSocket::ConnectedState)
    {
        mp_clientSocket->abort();
    }
}
