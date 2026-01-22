#ifndef CBPSTATIC_H
#define CBPSTATIC_H

#include "CommonHeader.h"
#include <QColor>
#include <QMap>
#include <QMetaEnum>
#include <QObject>
#include <QtQml>

class CIOTerminal;
Q_DECLARE_OPAQUE_POINTER(CIOTerminal*)
class CRawValueBase;
Q_DECLARE_OPAQUE_POINTER(CRawValueBase*)

/*!
 * \brief The CBPStatic class
 * blue print static and constants class
 */
class CBPStatic : public QObject
{
    Q_OBJECT
    QML_ELEMENT
  public:
    Q_DISABLE_COPY_MOVE(CBPStatic);
    explicit CBPStatic(){};

    enum class EBPDelegateGUIType
    {
        E_InvalidGUIType,
        E_SimpleBluePrint,
        E_OutputSinkWithString,
        E_OutputSinkNetworkClient,
        E_InputSpinBoxWithTimer,
        E_InputNetworkServer,
        E_InputButtonSource,
        E_BigTextOperator,
        E_BigPictureOperator,
        E_TypeConvrtrOperator,
        E_StopWatch,
        E_ScriptRunner,
        E_ChartBoxLineSeries
    };
    Q_ENUM(EBPDelegateGUIType)

    enum class EBPBoxCategoryType
    {
        E_BP_INVALIDTYPE,
        E_BP_MathOperation,
        E_BP_DataComparison,
        E_BP_LogicalOperation,
        E_BP_OutPutSink,
        E_BP_InputSource,
        E_BP_LoopsAndArrays,
        E_BP_Miscellaneous,
        E_BP_BigPictureOperator
    };
    Q_ENUM(EBPBoxCategoryType)

    inline static const QMap<CBPStatic::EBPBoxCategoryType, QString> BPBoxCategoryName = {
        {EBPBoxCategoryType::E_BP_INVALIDTYPE, "Invalid"},         {EBPBoxCategoryType::E_BP_MathOperation, "Math"},          {EBPBoxCategoryType::E_BP_DataComparison, "Data Comparison/Conversion"},
        {EBPBoxCategoryType::E_BP_LogicalOperation, "Logical"},    {EBPBoxCategoryType::E_BP_OutPutSink, "Data Sink"},        {EBPBoxCategoryType::E_BP_InputSource, "Data Source"},
        {EBPBoxCategoryType::E_BP_Miscellaneous, "Miscellaneous"}, {EBPBoxCategoryType::E_BP_LoopsAndArrays, "Loops/Arrays"}, {EBPBoxCategoryType::E_BP_BigPictureOperator, "Conditional Branch"}};

    inline static const QStringList listOfSupportedTypes{"int", "double", "bool", "string", "array"};

  public slots:
    static QColor getColorOfNodeByType(CIOTerminal* pNode);
    static QColor getColorByType(CRawValueBase* pValue);

    static QString getNameOfCategory(const QString& categoryType)
    {
        bool ok = false;
        QMetaEnum metaEnum = QMetaEnum::fromType<EBPBoxCategoryType>();
        auto value = static_cast<EBPBoxCategoryType>(metaEnum.keyToValue(categoryType.toLatin1().constData(), &ok));
        if (!ok)
        {
            DEBUG_MSG_PRINT << "ERROR " << categoryType;
            return "ERROR";
        }
        if (BPBoxCategoryName.contains(value) == true)
            return BPBoxCategoryName[value];
        DEBUG_MSG_PRINT << "ERROR " << categoryType;
        return "ERROR";
    }

    static QString getNameOfTypeAsString(CIOTerminal* pNode);
    static QString getNameOfTypeAsString(CRawValueBase* pValue);
    static QStringList getListOfSupportedTypes() { return listOfSupportedTypes; };
    static QString getFileNameFromPath(const QString& filePath);

    static void copyTextToClipboard(const QString& textToCopy);

    /*!
     * \brief dataTerminalSize
     * returns the terminal size on blueprint boxes
     * each terminal has width=height=dataTerminalSize
     * there is a padding for each terminal, so the total size of a
     * terminal box is twice this number
     * \return
     */
    static int dataTerminalSize();
    constexpr static int defaultFontPointSize() { return 8; };
    static int bluePrintBoxHeaderHeight();
};

#endif //  CBPSTATIC_H
