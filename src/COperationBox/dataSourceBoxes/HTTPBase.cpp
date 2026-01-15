#include "HTTPBase.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <memory>

#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "src/CRawValueBase/RawValueBase.h"

CHTTPBase::CHTTPBase(int newBlueBox_xPos, int newBlueBox_yPos, const QString& uniqueBoxName, QObject* parent)
    : COperationBox{uniqueBoxName, newBlueBox_xPos, newBlueBox_yPos, blueBoxWidth, blueBoxHeight - 20, parent}
{
    m_blueBox_settingQMLPath = "qrc:/QML/BluePrintBoxes/NetworkBoxes/HTTPHeaderSettingsPopup.qml";
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_BigPictureOperator;

    auto outPutNodeString = new COutputTerminal(0, this);
    outPutNodeString->setTerminalName("Out");
    m_listOfOutputTerminals.push_back(outPutNodeString);

    auto inputNode1 = new CInputTerminal(0, this);
    inputNode1->setTerminalName("url");
    // we put a zero in input terminal by default
    inputNode1->setTerminalCurrentData(std::make_shared<CValue_string>(""));
    m_listOfInputTerminals.push_back(inputNode1);
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_InputSource;

    mp_networkMngr = new QNetworkAccessManager(this);
    connect(mp_networkMngr, &QNetworkAccessManager::finished, this, &CHTTPBase::httpReceptionFinished);
}

void CHTTPBase::httpReceptionFinished(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData;
        while (reply->bytesAvailable() || reply->waitForReadyRead(3000))
        {
            responseData.append(reply->readAll());
        }
        m_listOfOutputTerminals.at(0)->sendValueToFlowLine(std::make_shared<CValue_string>(responseData));
    }
    else
    {
        qDebug() << "Error:" << reply->errorString();
    }
    reply->deleteLater();
}

CHTTPBase::~CHTTPBase() { qDeleteAll(m_listOfRawHeaders); }

void CHTTPBase::addNewPairToRawHeaderList()
{
    m_listOfRawHeaders.push_back(new CHTTPRawHeaderFormat("", ""));
    emit listOfRawHeadersChanged();
}

void CHTTPBase::removePairFromRawHeaderList(const int& indexOfItem)
{
    ASSERTWITHINFO(m_listOfRawHeaders.length() > indexOfItem);
    auto pToBeRemoved = m_listOfRawHeaders.at(indexOfItem);
    m_listOfRawHeaders.removeAt(indexOfItem);
    emit listOfRawHeadersChanged();
    delete pToBeRemoved;
}

void CHTTPBase::serializeBoxInfoIntoJson(QJsonObject& jsonObj)
{
    COperationBox::serializeBoxInfoIntoJson(jsonObj);
    QJsonObject headerObj;
    for (auto iter : m_listOfRawHeaders)
    {
        if (iter->headerName().isEmpty())
            continue;
        headerObj[iter->headerName()] = iter->headerValue();
    }
    QJsonArray headerArray;
    headerArray.append(headerObj);
    // Add the array to the main JSON object
    jsonObj["rawHeaderInfo"] = headerArray;
}

void CHTTPBase::deserializeBoxInfoFromJson(const QJsonObject& jsonObj)
{
    COperationBox::deserializeBoxInfoFromJson(jsonObj);
    // Extract the "headerInfo" array dynamically
    if (jsonObj.contains("rawHeaderInfo") && jsonObj["rawHeaderInfo"].isArray())
    {
        QJsonArray headerArray = jsonObj["rawHeaderInfo"].toArray();
        // Iterate through the array
        for (const QJsonValue& value : headerArray)
        {
            if (value.isObject())
            {
                QJsonObject header = value.toObject();
                // Iterate over all key-value pairs dynamically
                for (const QString& key : header.keys())
                {
                    m_listOfRawHeaders.push_back(new CHTTPRawHeaderFormat(key, header[key].toString()));
                }
            }
        }
    }
}

QQmlListProperty<CHTTPRawHeaderFormat> CHTTPBase::listOfRawHeaders() { return QQmlListProperty<CHTTPRawHeaderFormat>(this, &m_listOfRawHeaders); }

///////////////////// *************************     CHTTPRawHeaderFormat   *************************** ///////////////////

const QString& CHTTPRawHeaderFormat::headerName() const { return m_headerName; }

void CHTTPRawHeaderFormat::setHeaderName(const QString& newHeaderName)
{
    if (m_headerName == newHeaderName)
        return;
    m_headerName = newHeaderName;
    emit headerNameChanged();
}

const QString& CHTTPRawHeaderFormat::headerValue() const { return m_headerValue; }

void CHTTPRawHeaderFormat::setHeaderValue(const QString& newHeaderValue)
{
    if (m_headerValue == newHeaderValue)
        return;
    m_headerValue = newHeaderValue;
    emit headerValueChanged();
}
