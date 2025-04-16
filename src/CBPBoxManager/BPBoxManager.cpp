#include "BPBoxManager.h"

#include "src/CBPBoxFactory/BPBoxFactory.h"
#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CRawValueBase/RawValueBase.h"
#include <QTimer>

CBPBoxManager::CBPBoxManager(QObject *parent)
    : QObject{parent}
{
    m_bpBoxBrowserList = CBPBoxFactory::getInstance()->getListOfAllBPBoxes();
    m_listOfBluePrintPages.push_back(new CBluePrintPage());
    QTimer::singleShot(2000, this , [this](){
        const int numNodes = 10000;
        auto pPage =  m_listOfBluePrintPages.last() ;
        for(int iter = 0 ; iter < numNodes ; iter++){
            auto pBox = CBPBoxFactory::getInstance()->createBPBoxInstance( "Math Addition" , 350 + 240 * iter , 150 );
            pBox->setParentBluePrintPage(pPage);
            pPage->m_listOfBlueBoxes.push_back(pBox);
            pBox->getListOfInputTerminals().at(1)->setTerminalCurrentData( std::make_shared<CValue_int>(1));
            if(iter < 1 )
                continue;
            auto pPreviousBox = pPage->m_listOfBlueBoxes.at(pPage->m_listOfBlueBoxes.size() - 2 );
            auto pFlowLine = new CFlowConnectionLine( pPreviousBox->getListOfOutputTerminals().at(0)  );
            pPage->m_listOfFlowConnectionLines.push_back(pFlowLine);
            CFlowConnectionLine::bindFlowLineToOutputTerminal( pFlowLine , pPreviousBox->getListOfOutputTerminals().at(0));
            CFlowConnectionLine::bindFlowLineToInputTerminal(  pFlowLine , pBox->getListOfInputTerminals().at(0));
        }

        /// add other nodes
        {
            auto pBox = CBPBoxFactory::getInstance()->createBPBoxInstance( "String Sink OutPut" ,  400 + 240 * numNodes , 25 );
            pBox->setParentBluePrintPage(pPage);
            auto pLastBox =  pPage->m_listOfBlueBoxes.at( numNodes - 1  );
            pPage->m_listOfBlueBoxes.push_back(pBox);
            auto pFlowLine = new CFlowConnectionLine( pLastBox->getListOfOutputTerminals().at(0)  );
            pPage->m_listOfFlowConnectionLines.push_back(pFlowLine);
            CFlowConnectionLine::bindFlowLineToOutputTerminal( pFlowLine , pLastBox->getListOfOutputTerminals().at(0));
            CFlowConnectionLine::bindFlowLineToInputTerminal(  pFlowLine , pBox->getListOfInputTerminals().at(0));
        }
        {
            auto pBox = CBPBoxFactory::getInstance()->createBPBoxInstance( "Logical NOT" ,  375 + 240 * numNodes , 390 );
            pBox->setParentBluePrintPage(pPage);
            auto pLastBox =  pPage->m_listOfBlueBoxes.at( numNodes - 1 );
            pPage->m_listOfBlueBoxes.push_back(pBox);
            auto pFlowLine = new CFlowConnectionLine( pLastBox->getListOfOutputTerminals().at(0)  );
            pPage->m_listOfFlowConnectionLines.push_back(pFlowLine);
            CFlowConnectionLine::bindFlowLineToOutputTerminal( pFlowLine , pLastBox->getListOfOutputTerminals().at(0));
            CFlowConnectionLine::bindFlowLineToInputTerminal(  pFlowLine , pBox->getListOfInputTerminals().at(0));
        }
        {
            auto pBox = CBPBoxFactory::getInstance()->createBPBoxInstance( "Stop Watch" ,  350  , 500 );
            pBox->setParentBluePrintPage(pPage);
            auto pLastBox =  pPage->m_listOfBlueBoxes.at( numNodes + 1  );
            pPage->m_listOfBlueBoxes.push_back(pBox);
            auto pFlowLine = new CFlowConnectionLine( pLastBox->getListOfOutputTerminals().at(0)  );
            pPage->m_listOfFlowConnectionLines.push_back(pFlowLine);
            CFlowConnectionLine::bindFlowLineToOutputTerminal( pFlowLine , pLastBox->getListOfOutputTerminals().at(0));
            CFlowConnectionLine::bindFlowLineToInputTerminal(  pFlowLine , pBox->getListOfInputTerminals().at(0));
        }

        {
            auto pBox = CBPBoxFactory::getInstance()->createBPBoxInstance( "Button" , 50 , 300 );
            pBox->setParentBluePrintPage(pPage);
            pPage->m_listOfBlueBoxes.push_back(pBox);
            pBox->getListOfInputTerminals().at(0)->setTerminalCurrentData( std::make_shared<CValue_int>(1));

            auto pFlowLine = new CFlowConnectionLine( pBox->getListOfOutputTerminals().at(0)  );
            pPage->m_listOfFlowConnectionLines.push_back(pFlowLine);
            CFlowConnectionLine::bindFlowLineToOutputTerminal( pFlowLine , pBox->getListOfOutputTerminals().at(0));
            CFlowConnectionLine::bindFlowLineToInputTerminal(  pFlowLine , pPage->m_listOfBlueBoxes.at(numNodes+2)->getListOfInputTerminals().at(0));

            auto pFlowLine1 = new CFlowConnectionLine( pBox->getListOfOutputTerminals().at(0)  );
            pPage->m_listOfFlowConnectionLines.push_back(pFlowLine1);
            CFlowConnectionLine::bindFlowLineToOutputTerminal( pFlowLine1 , pBox->getListOfOutputTerminals().at(0));
            CFlowConnectionLine::bindFlowLineToInputTerminal(  pFlowLine1 , pPage->m_listOfBlueBoxes.at(0)->getListOfInputTerminals().at(0));
        }

        emit pPage->listOfFlowConnectionLinesChanged();
        emit pPage->listOfBlueBoxesChanged();
    });
}


CBPBoxManager::~CBPBoxManager()
{
}


CBPBoxManager * CBPBoxManager::getInstance()
{
    static auto pInstance = std::unique_ptr<CBPBoxManager>(new CBPBoxManager());
    return  pInstance.get();
}

QQmlListProperty<CBluePrintPage> CBPBoxManager::listOfBluePrintPages()
{
    return QQmlListProperty<CBluePrintPage>(this, &m_listOfBluePrintPages);
}


QQmlListProperty<COperationBox> CBPBoxManager::bpBoxBrowserList()
{
    return QQmlListProperty<COperationBox>(this, &m_bpBoxBrowserList);
}
QQmlListProperty<COperationBox> CBPBoxManager::bpBoxBrowserListProxy()
{
    return QQmlListProperty<COperationBox>(this, &m_bpBoxBrowserListProxy);
}





bool CBPBoxManager::darkThemeEnabled() const
{
    return m_darkThemeEnabled;
}

void CBPBoxManager::setDarkThemeEnabled(const bool &newValue)
{
    if (m_darkThemeEnabled == newValue)
        return;
    m_darkThemeEnabled = newValue;
    emit darkThemeEnabledChanged();
}

bool CBPBoxManager::isArchiveSearchActive() const
{
    return m_isArchiveSearchActive;
}

void CBPBoxManager::setIsArchiveSearchActive(const bool &newValue)
{
    if (m_isArchiveSearchActive == newValue)
        return;
    m_isArchiveSearchActive = newValue;
    emit isArchiveSearchActiveChanged();
}

int CBPBoxManager::activePageIndex() const
{
    return m_activePageIndex;
}

void CBPBoxManager::setActivePageIndex(const int & newValue)
{
    if (m_activePageIndex == newValue)
        return;
    ASSERTWITHINFO(newValue < m_listOfBluePrintPages.length());
    m_activePageIndex = newValue;
    emit activePageIndexChanged();
}

bool CBPBoxManager::terminalGlowEnable() const
{
    return m_terminalGlowEnable;
}

void CBPBoxManager::setTerminalGlowEnable(bool newTerminalGlowEnable)
{
    if (m_terminalGlowEnable == newTerminalGlowEnable)
        return;
    m_terminalGlowEnable = newTerminalGlowEnable;
    emit terminalGlowEnableChanged();
}


void CBPBoxManager::boxListSearchBoxTextChanged(const QString &newSearch)
{
    m_bpBoxBrowserListProxy =  CBPBoxFactory::getInstance()->findMatchingNodesWithStringQuery(newSearch);
    emit bpBoxBrowserListProxyChanged();
}

void CBPBoxManager::addNewBluePrintPage()
{
    m_listOfBluePrintPages.push_back(new CBluePrintPage());
    emit listOfBluePrintPagesChanged();
    setActivePageIndex(m_listOfBluePrintPages.length() - 1 ); // activated newly created page
}

void CBPBoxManager::removeBluePrintPage(const int &pageIndex)
{
    qDebug() << "removing index " << pageIndex ;
    ASSERTWITHINFO(pageIndex < m_listOfBluePrintPages.length());
    int  newIndex = pageIndex - 1 >= 0 ?  pageIndex - 1 : 0 ;
    setActivePageIndex(newIndex);
    auto pTargetPage = m_listOfBluePrintPages.at(pageIndex);
    m_listOfBluePrintPages.removeAt(pageIndex);
    if(m_listOfBluePrintPages.length() == 0 )
        m_listOfBluePrintPages.push_back(new CBluePrintPage());
    emit listOfBluePrintPagesChanged();
    delete pTargetPage;
}






