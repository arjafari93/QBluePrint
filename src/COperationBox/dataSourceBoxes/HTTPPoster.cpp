#include "HTTPPoster.h"

#include <memory>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CRawValueBase/RawValueBase.h"


CHTTPPoster::CHTTPPoster ( int newBlueBox_xPos, int newBlueBox_yPos, QObject *parent)
    : CHTTPBase{ newBlueBox_xPos  , newBlueBox_yPos  , m_uniqueBoxName , parent }
{
    m_blueBox_HeaderIcon = "qrc:/Images/httpPost.png";
    m_blueBox_HeadColor = QColor(75 , 120 , 140 );
    m_blueBox_keyWords = "http web request post get restful send  ";

    auto inputNode1 = new CInputTerminal(1, this);
    inputNode1->setTerminalName("Data");
    // we put a zero in input terminal by default
    inputNode1->setTerminalCurrentData(std::make_shared<CValue_string>(""));
    m_listOfInputTerminals.push_back(inputNode1 );
}

void CHTTPPoster::evaluateOperation()
{
    auto pUrlIn = m_listOfInputTerminals.at(0)->terminalCurrentData().get() ;
    auto pDataIn= m_listOfInputTerminals.at(1)->terminalCurrentData().get() ;
    if(!pUrlIn || !pDataIn)
        return ;
    auto* pURLVal = dynamic_cast<CValue_string*>(pUrlIn);
    auto* pDataVal = dynamic_cast<CValue_string*>(pDataIn);
    if(!pURLVal || !pDataVal ) // only accept string
        return ;
    QUrl url(pURLVal->value());
    QNetworkRequest request(url);
    for( auto iter : m_listOfRawHeaders  ){
        request.setRawHeader( iter->headerName().toUtf8() , iter->headerValue().toUtf8() );
    }
    mp_networkMngr->post(request , pDataVal->value().toUtf8() );
}

CHTTPPoster::~CHTTPPoster()
{

}

