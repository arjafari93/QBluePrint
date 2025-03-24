#include "BPStatic.h"

#include "src/CIOTerminal/IOTerminal.h"
#include "src/CRawValueBase/RawValueBase.h"

QColor CBPStatic::getColorOfNodeByType(  CIOTerminal * pNode ){
    auto pTerminalData = pNode->terminalCurrentData().get();
    if(!pTerminalData)
       return QColor(150,150,150);

    if (auto* pBox = dynamic_cast<CValue_int*>(pTerminalData)) {
        return QColor(252,0  ,211);
    } else if (auto* pBox = dynamic_cast<CValue_double*>(pTerminalData)) {
       return QColor(0  ,169,244);
    }else if (auto* pBox = dynamic_cast<CValue_bool*>(pTerminalData)) {
         return QColor(255,255,0);
    }else if (auto* pBox = dynamic_cast<CValue_string*>(pTerminalData)) {
         return QColor(100,255,100);
    }

    DEBUG_MSG_PRINT << " failed to find the color for Terminal ";
    return QColor(255,0,0);
}


QColor CBPStatic::getColorByType(  CRawValueBase * pValue ){
    if(!pValue)
       return QColor(150,150,150);

    if (auto* pBox = dynamic_cast<CValue_int*>(pValue)) {
        return QColor(252,0  ,211);
    } else if (auto* pBox = dynamic_cast<CValue_double*>(pValue)) {
       return QColor(0  ,169,244);
    }else if (auto* pBox = dynamic_cast<CValue_bool*>(pValue)) {
         return QColor(255,255,0);
    }else if (auto* pBox = dynamic_cast<CValue_string*>(pValue)) {
         return QColor(100,255,100);
    }

    DEBUG_MSG_PRINT << " failed to find the color for Terminal ";
    return QColor(255,0,0);
}



QString CBPStatic::getNameOfTypeAsString(CIOTerminal *pNode){
    auto pTerminalData = pNode->terminalCurrentData().get();
    if(!pTerminalData)
       return "INVALID";

    if (auto* pBox = dynamic_cast<CValue_int*>(pTerminalData)) {
        return "int";
    } else if (auto* pBox = dynamic_cast<CValue_double*>(pTerminalData)) {
       return "double";
    }else if (auto* pBox = dynamic_cast<CValue_bool*>(pTerminalData)) {
         return "bool";
    }else if (auto* pBox = dynamic_cast<CValue_string*>(pTerminalData)) {
         return "string";
    }

    DEBUG_MSG_PRINT << " failed to find the name for Terminal ";
    return "INVALID";
}
