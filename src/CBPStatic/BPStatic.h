#ifndef CBPSTATIC_H
#define CBPSTATIC_H

#include <QObject>
#include <QMap>
#include <QColor>
#include "src/CommonHeader.h"

class CIOTerminal ;
class CRawValueBase ;


/*!
 * \brief The CBPStatic class
 * blue print static and constants class
 */
class CBPStatic : public QObject
{
    Q_OBJECT
public:
    Q_DISABLE_COPY_MOVE(CBPStatic);
    explicit CBPStatic() {} ;

    enum  class EBPDelegateGUIType {
        E_InvalidGUIType          ,
        E_SimpleBluePrint         ,
        E_OutputSinkWithString    ,
        E_OutputSinkNetworkClient ,
        E_InputSpinBoxWithTimer   ,
        E_InputNetworkServer      ,
        E_InputButtonSource       ,
        E_BigTextOperator         ,
        E_BigPictureOperator      ,
        E_TypeConvrtrOperator     ,
        E_StopWatch               ,
        E_ScriptRunner            ,
        E_ChartBoxLineSeries

    };
    Q_ENUM(EBPDelegateGUIType)


    enum  class EBPBoxCategoryType {
        E_BP_INVALIDTYPE          ,
        E_BP_MathOperation        ,
        E_BP_DataComparison       ,
        E_BP_LogicalOperation     ,
        E_BP_OutPutSink           ,
        E_BP_InputSource          ,
        E_BP_Miscellaneous        ,
        E_BP_BigPictureOperator
    };
    Q_ENUM(EBPBoxCategoryType)

    inline static const  QMap<CBPStatic::EBPBoxCategoryType, QString >  BPBoxCategoryName   = {
        { EBPBoxCategoryType::E_BP_INVALIDTYPE            , "Ivalid"              },
        { EBPBoxCategoryType::E_BP_MathOperation          , "Math"                },
        { EBPBoxCategoryType::E_BP_DataComparison         , "Data Comparison"     },
        { EBPBoxCategoryType::E_BP_LogicalOperation       , "Logical"             },
        { EBPBoxCategoryType::E_BP_OutPutSink             , "Output Sink"         },
        { EBPBoxCategoryType::E_BP_InputSource            , "Input Source"        },
        { EBPBoxCategoryType::E_BP_Miscellaneous          , "Miscellaneous"       },
        { EBPBoxCategoryType::E_BP_BigPictureOperator     , "Conditional Branch"  }
    };

    inline static const QStringList  listOfSupportedTypes {"int" , "double" , "bool" , "string"};

public slots:
    static QColor getColorOfNodeByType( CIOTerminal * pNode );
    static QColor getColorByType(CRawValueBase *pValue);


    static QString getNameOfCategory(const CBPStatic::EBPBoxCategoryType & categoryType ){
        if(BPBoxCategoryName.contains( categoryType ) == true )
            return BPBoxCategoryName[categoryType];
        qDebug()<< "ERROR " << FILEINFOMACRO ;
        return "ERROR";
    }

    static QString getNameOfTypeAsString( CIOTerminal * pNode);
    static QStringList  getListOfSupportedTypes  () {return listOfSupportedTypes ; };

};




#endif //  CBPSTATIC_H
