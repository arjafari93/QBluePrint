#include "BPBoxManager.h"

#include "src/CBPBoxFactory/BPBoxFactory.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

CBPBoxManager::CBPBoxManager(QObject* parent) : QObject{parent}
{
    m_bpBoxBrowserList = CBPBoxFactory::getInstance()->getListOfAllBPBoxes();
    m_listOfBluePrintPages.push_back(new CBluePrintPage());
    QJSEngine::setObjectOwnership(this, QJSEngine::CppOwnership);
}

CBPBoxManager::~CBPBoxManager() {}

CBPBoxManager* CBPBoxManager::getInstance()
{
    static auto pInstance = std::unique_ptr<CBPBoxManager>(new CBPBoxManager());
    return pInstance.get();
}

QQmlListProperty<CBluePrintPage> CBPBoxManager::listOfBluePrintPages() { return QQmlListProperty<CBluePrintPage>(this, &m_listOfBluePrintPages); }

QQmlListProperty<COperationBox> CBPBoxManager::bpBoxBrowserList() { return QQmlListProperty<COperationBox>(this, &m_bpBoxBrowserList); }
QQmlListProperty<COperationBox> CBPBoxManager::bpBoxBrowserListProxy() { return QQmlListProperty<COperationBox>(this, &m_bpBoxBrowserListProxy); }

bool CBPBoxManager::darkThemeEnabled() const { return m_darkThemeEnabled; }

void CBPBoxManager::setDarkThemeEnabled(const bool& newValue)
{
    if (m_darkThemeEnabled == newValue)
        return;
    m_darkThemeEnabled = newValue;
    emit darkThemeEnabledChanged();
}

bool CBPBoxManager::isArchiveSearchActive() const { return m_isArchiveSearchActive; }

void CBPBoxManager::setIsArchiveSearchActive(const bool& newValue)
{
    if (m_isArchiveSearchActive == newValue)
        return;
    m_isArchiveSearchActive = newValue;
    emit isArchiveSearchActiveChanged();
}

int CBPBoxManager::activePageIndex() const { return m_activePageIndex; }

void CBPBoxManager::setActivePageIndex(const int& newValue)
{
    if (m_activePageIndex == newValue)
        return;
    ASSERTWITHINFO(newValue < m_listOfBluePrintPages.length());
    m_activePageIndex = newValue;
    emit activePageIndexChanged();
}

bool CBPBoxManager::terminalGlowEnable() const { return m_terminalGlowEnable; }

void CBPBoxManager::setTerminalGlowEnable(bool newTerminalGlowEnable)
{
    if (m_terminalGlowEnable == newTerminalGlowEnable)
        return;
    m_terminalGlowEnable = newTerminalGlowEnable;
    emit terminalGlowEnableChanged();
}

void CBPBoxManager::boxListSearchBoxTextChanged(const QString& newSearch)
{
    m_bpBoxBrowserListProxy = CBPBoxFactory::getInstance()->findMatchingNodesWithStringQuery(newSearch);
    emit bpBoxBrowserListProxyChanged();
}

void CBPBoxManager::addNewBluePrintPage()
{
    m_listOfBluePrintPages.push_back(new CBluePrintPage());
    emit listOfBluePrintPagesChanged();
    setActivePageIndex(m_listOfBluePrintPages.length() - 1); // activated newly created page
}

void CBPBoxManager::removeBluePrintPage(const int& pageIndex)
{
    ASSERTWITHINFO(pageIndex < m_listOfBluePrintPages.length());
    int newIndex = pageIndex - 1 >= 0 ? pageIndex - 1 : 0;
    setActivePageIndex(newIndex);
    auto pTargetPage = m_listOfBluePrintPages.at(pageIndex);
    m_listOfBluePrintPages.removeAt(pageIndex);
    if (m_listOfBluePrintPages.length() == 0)
        m_listOfBluePrintPages.push_back(new CBluePrintPage());
    emit listOfBluePrintPagesChanged();
    delete pTargetPage;
}

bool CBPBoxManager::createNewBoxFromGivenType(CBluePrintPage* pPage, const QString& boxName, const int& posX, const int& posY, const bool& emitSignal)
{
    try
    {
        auto pBox = CBPBoxFactory::getInstance()->createBPBoxInstance(boxName, posX, posY);
        ASSERTWITHRETURN(pBox, false);
        pBox->setParentBluePrintPage(pPage);
        pPage->m_listOfBlueBoxes.push_back(pBox);
        if (emitSignal)
            emit pPage->listOfBlueBoxesChanged();
        return true;
    }
    catch (const std::exception& e)
    {
        DEBUG_MSG_PRINT << " exception: " << e.what();
    }
    catch (...)
    {
        DEBUG_MSG_PRINT << " exception: ";
    }
    return false;
}

bool CBPBoxManager::loadBluePrintInfoIntoPage(CBluePrintPage* pPage, const QString& pathToFile)
{
    // Read the JSON file
    QFile file(pathToFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        DEBUG_MSG_PRINT << "Failed to open JSON file" << pathToFile;
        return false;
    }

    QTextStream in(&file);
    QString jsonString = in.readAll();
    file.close();

    // Parse the JSON document
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());

    // Check if the JSON document is valid
    if (jsonDocument.isNull())
    {
        DEBUG_MSG_PRINT << "Failed to parse JSON document";
        return false;
    }
    // lets clear current info if any
    pPage->clearCurrentBluePrintSession();
    pPage->setCurrentBluePrintFilePath(pathToFile);
    // Access the main JSON object
    QJsonObject mainObject = jsonDocument.object();

    // Access BPBoxesInfo array
    QJsonArray bpBoxesArray = mainObject["BPBoxesInfo"].toArray();

    // Iterate through BPBoxesInfo objects
    for (const QJsonValue& bpBoxValue : bpBoxesArray)
    {
        QJsonObject bpBoxObject = bpBoxValue.toObject();
        auto res = createNewBoxFromGivenType(pPage, bpBoxObject["BoxName"].toString(), bpBoxObject["xPos"].toString().toInt(), bpBoxObject["yPos"].toString().toInt(), false);
        if (!res)
            continue;
        auto pBox = pPage->m_listOfBlueBoxes.last();
        pBox->deserializeBoxInfoFromJson(bpBoxObject);
    }

    emit pPage->listOfBlueBoxesChanged();

    // Access BPFlowLinesInfo array
    QJsonArray flowLinesArray = mainObject["BPFlowLinesInfo"].toArray();

    // Iterate through BPFlowLinesInfo objects
    for (const QJsonValue& flowLineValue : flowLinesArray)
    {
        bool isValid = false;
        QJsonObject flowLineObject = flowLineValue.toObject();
        auto pStartBPBox = pPage->getBPBoxFromUniqueID(flowLineObject["startBoxID"].toString().toInt());
        ASSERTWITHRETURN(pStartBPBox, false);
        auto pEndBPBox = pPage->getBPBoxFromUniqueID(flowLineObject["endBoxID"].toString().toInt());
        ASSERTWITHRETURN(pEndBPBox, false);
        int startTerminalIndex = flowLineObject["startTerminalIndex"].toString().toInt();
        isValid = startTerminalIndex <= (pStartBPBox->getListOfOutputTerminals().length() - 1);
        ASSERTWITHRETURN(isValid, false);
        int endTerminalIndex = flowLineObject["endTerminalIndex"].toString().toInt();
        isValid = endTerminalIndex <= (pEndBPBox->getListOfInputTerminals().length() - 1);
        ASSERTWITHRETURN(isValid, false);
        // if we are here it means all data are valid and we are good to create the flow line
        pPage->m_listOfFlowConnectionLines.push_back(new CFlowConnectionLine(pStartBPBox->getListOfOutputTerminals().at(startTerminalIndex)));
        CFlowConnectionLine::bindFlowLineToOutputTerminal(pPage->m_listOfFlowConnectionLines.last(), pStartBPBox->getListOfOutputTerminals().at(startTerminalIndex));
        CFlowConnectionLine::bindFlowLineToInputTerminal(pPage->m_listOfFlowConnectionLines.last(), pEndBPBox->getListOfInputTerminals().at(endTerminalIndex));
    }

    emit pPage->listOfBlueBoxesChanged();
    emit pPage->listOfFlowConnectionLinesChanged();
    pPage->recalculateMaxPositions();
    return true;
}
