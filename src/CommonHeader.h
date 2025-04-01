#ifndef COMMONHEADER_H
#define COMMONHEADER_H

#include <QDebug>
#include <QObject>
#include <QFileInfo>

#ifndef FILEINFOMACRO
#define FILEINFOMACRO   "file://" << QFileInfo(__FILE__).absoluteFilePath() << ":" << __LINE__ << " \033[33m function: " << __func__ << " \033[0m"
#endif


#ifndef DEBUG_MSG_PRINT
#define DEBUG_MSG_PRINT qDebug().noquote().nospace()   <<  FILEINFOMACRO
#endif

#ifndef ASSERTWITHINFO
#define ASSERTWITHINFO(toBeAsser ) if(!(toBeAsser)) {DEBUG_MSG_PRINT << "\033[31mAssertion failed \033[0m"; return; }
#endif

#ifndef ASSERTWITHMSG
#define ASSERTWITHMSG(toBeAsser , MsgToBePrinted ) if(!(toBeAsser)) {DEBUG_MSG_PRINT  << "\033[31mAssertion failed \033[0m" << (MsgToBePrinted) ; return; }
#endif

#ifndef ASSERTWITHRETURN
#define ASSERTWITHRETURN(toBeAsser , toBeReturn ) if(!(toBeAsser)) {DEBUG_MSG_PRINT<< "\033[31mAssertion failed \033[0m"; return (toBeReturn); }
#endif

#ifndef MAX_DOUBLE_PRECISION
#define MAX_DOUBLE_PRECISION  2
#endif

#ifndef GETUNIQUENAMEFUNC
#define GETUNIQUENAMEFUNC  public : static QString getUniqueName() {return m_uniqueBoxName; }
#endif




#endif // COMMONHEADER_H
