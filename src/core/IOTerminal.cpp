#include "IOTerminal.h"

#include "BPStatic.h"

#include "src/CBPBoxManager/BPBoxManager.h"
#include "FlowConnectionLine.h"
#include "InputTerminal.h"
#include "OutputTerminal.h"
#include "RawValueBase.h"

CIOTerminal::CIOTerminal(const int& terminalIndexInBox, COperationBox* parent) : m_terminalIndexInBox{terminalIndexInBox}
{
    ASSERTWITHINFO(parent);
    mp_containerBPBox = parent;
    m_terminalSize = CBPStatic::dataTerminalSize();
    m_terminalYPos = (m_terminalSize * 2 * m_terminalIndexInBox) + CBPStatic::bluePrintBoxHeaderHeight();
}

void CIOTerminal::setTerminalCurrentData(const std::shared_ptr<CRawValueBase>& newValue)
{
    if (!newValue.get())
        return;
    m_terminalCurrentData = newValue;
    setTerminalColor(CBPStatic::getColorByType(newValue.get()));
}

void CIOTerminal::changeTerminalCurrentData(const QVariant& newValue)
{
    switch (newValue.type())
    {
    case QVariant::Int:
        setTerminalCurrentData(std::make_shared<CValue_int>(newValue.toInt()));
        break;
    case QVariant::Double:
        setTerminalCurrentData(std::make_shared<CValue_double>(newValue.toDouble()));
        break;
    case QVariant::Bool:
        setTerminalCurrentData(std::make_shared<CValue_bool>(newValue.toBool()));
        break;
    case QVariant::String:
        setTerminalCurrentData(std::make_shared<CValue_string>(newValue.toString()));
        break;
    default:
        DEBUG_MSG_PRINT << " type doesnt exist " << newValue.type();
        break;
    }
    emit nodeIsPassingNewValue(); // this can be helpful for signal/slots and finding the data has changed though GUI popup
}

void CIOTerminal::changeTerminalCurrentDataArray(const QVariant& newValue)
{
    using recFuncType = std::function<void(QList<std::shared_ptr<CRawValueBase>>&, const QVariant&)>;
    recFuncType recursiveInsertor;
    recursiveInsertor = [&](QList<std::shared_ptr<CRawValueBase>>& listOfRawVals, const QVariant& recVal) {
        switch (recVal.type())
        {
        case QVariant::Int:
            listOfRawVals.push_back(std::make_shared<CValue_int>(recVal.toInt()));
            break;
        case QVariant::Double:
            listOfRawVals.push_back(std::make_shared<CValue_double>(recVal.toDouble()));
            break;
        case QVariant::Bool:
            listOfRawVals.push_back(std::make_shared<CValue_bool>(recVal.toBool()));
            break;
        case QVariant::String:
            listOfRawVals.push_back(std::make_shared<CValue_string>(recVal.toString()));
            break;
        default:
            if (recVal.canConvert<QVariantList>())
            {
                auto listOfInnerVals = recVal.toList();
                QList<std::shared_ptr<CRawValueBase>> innerListOfRawVals;
                for (const auto& currentInnerVal : listOfInnerVals)
                {
                    recursiveInsertor(innerListOfRawVals, currentInnerVal);
                }
                listOfRawVals.push_back(std::make_shared<CValue_array>(std::move(innerListOfRawVals)));
            }
            else
            {
                DEBUG_MSG_PRINT << " type doesn't exist " << recVal.type();
            }
            break;
        }
    };

    // newValue is in fact an array
    ASSERTWITHINFO(newValue.canConvert<QVariantList>());
    auto listOfVals = newValue.toList();
    QList<std::shared_ptr<CRawValueBase>> listOfRawVals;
    for (auto const& currentVal : listOfVals)
    {
        recursiveInsertor(listOfRawVals, currentVal);
    }
    setTerminalCurrentData(std::make_shared<CValue_array>(std::move(listOfRawVals)));
    emit nodeIsPassingNewValue();
}

QVariant CIOTerminal::getTerminalCurrentData()
{
    if (!m_terminalCurrentData)
        return QVariant();
    return m_terminalCurrentData->convertToVariant();
}

QQmlListProperty<CFlowConnectionLine> CIOTerminal::listOfConnectedLines() { return QQmlListProperty<CFlowConnectionLine>(this, &m_listOfConnectedLines); }

void CIOTerminal::addFlowLineToConnectedList(CFlowConnectionLine* lineToBeAdded)
{
    if (m_listOfConnectedLines.indexOf(lineToBeAdded) != -1)
    {
        DEBUG_MSG_PRINT << " adding line to the list failed since line exists";
        return;
    }
    m_listOfConnectedLines.push_back(lineToBeAdded);
    emit listOfConnectedLinesChanged();
}

void CIOTerminal::removeFlowLineFromConnectedList(CFlowConnectionLine* lineToBeRemoved)
{
    ASSERTWITHINFO(m_listOfConnectedLines.length());
    int indexOfLine = m_listOfConnectedLines.indexOf(lineToBeRemoved);
    if (indexOfLine == -1)
    {
        DEBUG_MSG_PRINT << " removing line from list failed since line dosnt exists";
        return;
    }
    m_listOfConnectedLines.removeAt(indexOfLine);
    emit listOfConnectedLinesChanged();
    // this function is NOT responsible for releasing the memory of line
}

void CIOTerminal::setIsTerminalHovered(const bool& newValue)
{
    if (m_isTerminalHovered == newValue)
        return;
    m_isTerminalHovered = newValue;
    emit isTerminalHoveredChanged();
}

bool CIOTerminal::isTerminalHovered() const { return m_isTerminalHovered; }

void CIOTerminal::highlightLineFlowAtIndex(const int& lineFlowIndex, const bool& highLightOrNot)
{
    if (lineFlowIndex >= m_listOfConnectedLines.length())
        return;
    if (highLightOrNot == true)
        m_listOfConnectedLines.at(lineFlowIndex)->setFlowLine_strokeWidth(3);
    else
        m_listOfConnectedLines.at(lineFlowIndex)->setFlowLine_strokeWidth(1);
}

void CIOTerminal::removeLineFlowAtIndex(const int& lineFlowIndex)
{
    bool isIndexInRange = lineFlowIndex < m_listOfConnectedLines.length();
    ASSERTWITHMSG(isIndexInRange, " Index Out Of Range, length: " + QString::number(m_listOfConnectedLines.length()) + " index: " + QString::number(lineFlowIndex));
    // lets remove the line from start Terminal
    auto lineToBeRemoved = m_listOfConnectedLines.at(lineFlowIndex);
    lineToBeRemoved->startPoint()->removeFlowLineFromConnectedList(lineToBeRemoved);
    // lets remove the line from end Terminal
    lineToBeRemoved->endPoint()->removeFlowLineFromConnectedList(lineToBeRemoved);
    // lets remove the line from list model in CBPBoxManager
    auto parentPage = mp_containerBPBox->getParentBluePrintPage();
    ASSERTWITHINFO(parentPage);
    parentPage->removeLineFromListModel(lineToBeRemoved);
    // lets free the memoery of flow line
    delete lineToBeRemoved;
}

void CIOTerminal::removeAllFlowLines()
{
    while (m_listOfConnectedLines.length())
    {
        removeLineFlowAtIndex(m_listOfConnectedLines.length() - 1);
    }
}

bool CIOTerminal::emissionEnabled() const { return m_emissionEnabled; }

void CIOTerminal::setEmissionEnabled(bool newEmissionEnabled)
{
    if (m_emissionEnabled == newEmissionEnabled)
        return;
    m_emissionEnabled = newEmissionEnabled;
    emit emissionEnabledChanged();
}

QColor CIOTerminal::terminalColor() const { return m_terminalColor; }

void CIOTerminal::setTerminalColor(const QColor& newTerminalColor)
{
    if (m_terminalColor == newTerminalColor)
        return;
    m_terminalColor = newTerminalColor;
    emit terminalColorChanged();
}
