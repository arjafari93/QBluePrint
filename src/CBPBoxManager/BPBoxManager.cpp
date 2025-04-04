#include "BPBoxManager.h"

#include "src/CBPBoxFactory/BPBoxFactory.h"


CBPBoxManager::CBPBoxManager(QObject *parent)
    : QObject{parent}
{
    m_bpBoxBrowserList = CBPBoxFactory::getInstance()->getListOfAllBPBoxes();
    m_listOfBluePrintPages.push_back(new CBluePrintPage());
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






