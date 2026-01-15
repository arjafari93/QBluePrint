#include "HTTPGetter.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <memory>

#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "src/CRawValueBase/RawValueBase.h"

CHTTPGetter::CHTTPGetter(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent) : CHTTPBase{newBlueBox_xPos, newBlueBox_yPos, m_uniqueBoxName, parent}
{
    m_blueBox_HeaderIcon = "qrc:/Images/httpGet.png";
    m_blueBox_HeadColor = QColor(75, 140, 120);
    m_blueBox_keyWords = "http web request post get restful send  ";
}

void CHTTPGetter::evaluateOperation()
{
    auto pUrlIn = m_listOfInputTerminals.at(0)->terminalCurrentData().get();
    if (!pUrlIn)
        return;
    auto* pVal = dynamic_cast<CValue_string*>(pUrlIn);
    if (!pVal) // only accept string
        return;

    QUrl url(pVal->value());
    QNetworkRequest request(url);
    for (auto iter : m_listOfRawHeaders)
    {
        request.setRawHeader(iter->headerName().toUtf8(), iter->headerValue().toUtf8());
    }
    mp_networkMngr->get(request);
}

CHTTPGetter::~CHTTPGetter() {}
