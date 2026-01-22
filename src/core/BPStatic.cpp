#include "BPStatic.h"

#include "IOTerminal.h"
#include "RawValueBase.h"
#include <QClipboard>
#include <QFont>
#include <QFontMetrics>
#include <QGuiApplication>

// we define this one outside class because it is used in other libs too
QString getNameOfTypeAsString(CRawValueBase* pValue)
{
    if (!pValue)
        return "INVALID";

    if (auto* pBox = dynamic_cast<CValue_int*>(pValue))
    {
        return "int";
    }
    else if (auto* pBox = dynamic_cast<CValue_double*>(pValue))
    {
        return "double";
    }
    else if (auto* pBox = dynamic_cast<CValue_bool*>(pValue))
    {
        return "bool";
    }
    else if (auto* pBox = dynamic_cast<CValue_string*>(pValue))
    {
        return "string";
    }
    else if (auto* pBox = dynamic_cast<CValue_array*>(pValue))
    {
        return "array";
    }

    DEBUG_MSG_PRINT << " failed to find the name for pValue ";
    return "INVALID";
}

QColor CBPStatic::getColorOfNodeByType(CIOTerminal* pNode)
{
    auto pTerminalData = pNode->terminalCurrentData().get();
    if (!pTerminalData)
        return QColor(150, 150, 150);

    if (auto* pBox = dynamic_cast<CValue_int*>(pTerminalData))
    {
        return QColor(252, 0, 211);
    }
    else if (auto* pBox = dynamic_cast<CValue_double*>(pTerminalData))
    {
        return QColor(0, 169, 244);
    }
    else if (auto* pBox = dynamic_cast<CValue_bool*>(pTerminalData))
    {
        return QColor(255, 255, 0);
    }
    else if (auto* pBox = dynamic_cast<CValue_string*>(pTerminalData))
    {
        return QColor(100, 255, 100);
    }
    else if (auto* pBox = dynamic_cast<CValue_array*>(pTerminalData))
    {
        return QColor(200, 150, 250);
    }

    DEBUG_MSG_PRINT << " failed to find the color for Terminal ";
    return QColor(255, 0, 0);
}

QColor CBPStatic::getColorByType(CRawValueBase* pValue)
{
    if (!pValue)
        return QColor(150, 150, 150);

    if (auto* pBox = dynamic_cast<CValue_int*>(pValue))
    {
        return QColor(252, 0, 211);
    }
    else if (auto* pBox = dynamic_cast<CValue_double*>(pValue))
    {
        return QColor(0, 169, 244);
    }
    else if (auto* pBox = dynamic_cast<CValue_bool*>(pValue))
    {
        return QColor(255, 255, 0);
    }
    else if (auto* pBox = dynamic_cast<CValue_string*>(pValue))
    {
        return QColor(100, 255, 100);
    }
    else if (auto* pBox = dynamic_cast<CValue_array*>(pValue))
    {
        return QColor(200, 150, 250);
    }

    DEBUG_MSG_PRINT << " failed to find the color for Terminal ";
    return QColor(255, 0, 0);
}

QString CBPStatic::getNameOfTypeAsString(CIOTerminal* pNode)
{
    auto pTerminalData = pNode->terminalCurrentData().get();
    if (!pTerminalData)
        return "INVALID";

    if (auto* pBox = dynamic_cast<CValue_int*>(pTerminalData))
    {
        return "int";
    }
    else if (auto* pBox = dynamic_cast<CValue_double*>(pTerminalData))
    {
        return "double";
    }
    else if (auto* pBox = dynamic_cast<CValue_bool*>(pTerminalData))
    {
        return "bool";
    }
    else if (auto* pBox = dynamic_cast<CValue_string*>(pTerminalData))
    {
        return "string";
    }
    else if (auto* pBox = dynamic_cast<CValue_array*>(pTerminalData))
    {
        return "array";
    }

    DEBUG_MSG_PRINT << " failed to find the name for Terminal ";
    return "INVALID";
}

QString CBPStatic::getNameOfTypeAsString(CRawValueBase* pValue) { return ::getNameOfTypeAsString(pValue); }

QString CBPStatic::getFileNameFromPath(const QString& filePath)
{
    QFileInfo fileInfo(filePath);
    return fileInfo.fileName();
}

void CBPStatic::copyTextToClipboard(const QString& textToCopy)
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(textToCopy);
}

int CBPStatic::dataTerminalSize()
{
    QFont appFont = qApp->font();
    appFont.setPointSize(CBPStatic::defaultFontPointSize());
    QFontMetrics fontMetrics(appFont);
    return fontMetrics.height();
}

int CBPStatic::bluePrintBoxHeaderHeight()
{
    QFont appFont = qApp->font();
    appFont.setPointSize(CBPStatic::defaultFontPointSize());
    QFontMetrics fontMetrics(appFont);
    return fontMetrics.height() * 2;
}
