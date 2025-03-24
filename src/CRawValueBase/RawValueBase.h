#ifndef CRAWVALUEBASE_H
#define CRAWVALUEBASE_H

/*
 * Copyright (c) 2025 Alireza Jafari (https://github.com/arjafari93)
 *
 * This software is provided "as is", without warranty of any kind.
 * You may use, modify, and distribute this software, but you MUST keep
 * this copyright notice and credit the original author.
 *
 * Licensed under the BSD 3-Clause License
 */


#include <memory>
#include <QString>
#include <QObject>
#include <QMap>

#ifndef MAX_DOUBLE_PRECISION
#define MAX_DOUBLE_PRECISION  2
#endif


class CValueVisitor ;

class CRawValueBase
{
public:
    virtual ~CRawValueBase() = default;
    virtual QString convertToString() const = 0 ;
    virtual void accept(CValueVisitor& opBox ) = 0;
};


///////////**********************    concerete classes derived from CRawValueBase  BEGIN      **********************///////////


class CValue_int : public CRawValueBase {
public:
    long long value() const {return m_value; }
    explicit CValue_int(const long long & initVal) : m_value(initVal) {}
    void accept(CValueVisitor& visitor) override;
    virtual QString convertToString() const override {return QString::number(m_value); } ;
private:
    const long long m_value;
};

class CValue_double : public CRawValueBase {
public:
    long double value() const {return m_value; }
    explicit CValue_double(const long double & initVal) : m_value(initVal) {}
    void accept(CValueVisitor& visitor) override;
    virtual QString convertToString() const override {return QString::number( m_value , 'f' , MAX_DOUBLE_PRECISION  ); } ;
private:
    const long double m_value;
};

class CValue_string : public CRawValueBase {
public:
    QString value() const {return m_value; }
    explicit CValue_string(const QString & initVal) : m_value(std::move(initVal)) {}
    void accept(CValueVisitor& visitor) override;
    virtual QString convertToString() const override {return m_value; } ;
private:
    const QString m_value;
};

class CValue_bool : public CRawValueBase {
public:
    bool value() const {return m_value; }
    explicit CValue_bool(const bool & initVal) : m_value(initVal) {}
    void accept(CValueVisitor& visitor) override;
    virtual QString convertToString() const override {return QString::number((int)m_value); } ;
private:
    const bool m_value;
};

class CValue_list : public CRawValueBase {
public:
    QList<std::shared_ptr<CRawValueBase>> value() const {return m_value; }
    // Constructor accepting QList
    explicit CValue_list(const QList<std::shared_ptr<CRawValueBase>>& initVal)   : m_value(initVal) {}
    // Constructor accepting initializer list
    explicit CValue_list(std::initializer_list<std::shared_ptr<CRawValueBase>> initList)  : m_value(initList) {}
    void accept(CValueVisitor& visitor) override;
private:
    const QList<std::shared_ptr<CRawValueBase>> m_value;
};

class CValue_map : public CRawValueBase {
public:
    QMap<std::shared_ptr<CRawValueBase> , std::shared_ptr<CRawValueBase>>  value() const {return m_value; }
    // Constructor accepting QList
    explicit CValue_map(const QMap<std::shared_ptr<CRawValueBase> , std::shared_ptr<CRawValueBase>> & initVal)   : m_value(initVal) {}
    void accept(CValueVisitor& visitor) override;
private:
    const QMap<std::shared_ptr<CRawValueBase> , std::shared_ptr<CRawValueBase>>  m_value;
};

///////////**********************    concerete classes derived from CRawValueBase  END      **********************///////////


class CValueVisitor {
public:
    virtual void visit(const CValue_int& value) = 0;
    virtual void visit(const CValue_double& value) = 0;
    virtual void visit(const CValue_string& value) = 0;
    virtual void visit(const CValue_bool& value) = 0;
    virtual void visit(const CValue_list& value) = 0;
    virtual void visit(const CValue_map & value) = 0;
};


#endif // CRAWVALUEBASE_H




