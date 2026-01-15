#ifndef OPVISITOR_H
#define OPVISITOR_H

#include "src/CommonHeader.h"
#include <QVariant>

class CDataPassingArg;

class opVisitor
{
  public:
    opVisitor();
    virtual ~opVisitor(){};

    virtual CDataPassingArg* visit(const double&, const double&)
    {
        DEBUG_MSG_PRINT << " ERROR  abstract called";
        return nullptr;
    }
    virtual CDataPassingArg* visit(const double&, const qint64&)
    {
        DEBUG_MSG_PRINT << " ERROR  abstract called";
        return nullptr;
    }
    virtual CDataPassingArg* visit(const qint64&, const qint64&)
    {
        DEBUG_MSG_PRINT << " ERROR  abstract called";
        return nullptr;
    }
    virtual CDataPassingArg* visit(const QString&, const QString&)
    {
        DEBUG_MSG_PRINT << " ERROR  abstract called";
        return nullptr;
    }
    virtual CDataPassingArg* visit(const bool&, const bool&)
    {
        DEBUG_MSG_PRINT << " ERROR  abstract called";
        return nullptr;
    }
};

#endif // OPVISITOR_H
