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
#include <QVariant>

#ifndef MAX_DOUBLE_PRECISION
#define MAX_DOUBLE_PRECISION  2
#endif


class CValueVisitor ;

class CRawValueBase
{
public:
    virtual ~CRawValueBase() = default;
    virtual QString convertToString() const = 0 ;
    virtual QVariant convertToVariant() const  = 0 ;
    virtual void accept(CValueVisitor& opBox ) const  = 0;
};


///////////**********************    concerete classes derived from CRawValueBase  BEGIN      **********************///////////


class CValue_int : public CRawValueBase {
    Q_DISABLE_COPY_MOVE(CValue_int);
public:
    long long value() const {return m_value; }
    explicit CValue_int(const long long & initVal) : m_value(initVal) {}
    void accept(CValueVisitor& visitor) const  override;
    virtual QString convertToString() const override {return QString::number(m_value); } ;
    virtual QVariant convertToVariant() const override{ return  m_value ; }
private:
    const long long m_value;
};

class CValue_double : public CRawValueBase {
    Q_DISABLE_COPY_MOVE(CValue_double);
public:
    long double value() const {return m_value; }
    explicit CValue_double(const long double & initVal) : m_value(initVal) {}
    void accept(CValueVisitor& visitor) const  override;
    virtual QString convertToString() const override {return QString::number( m_value , 'f' , MAX_DOUBLE_PRECISION  ); } ;
    virtual QVariant convertToVariant() const override{ return  (float)m_value ; }
private:
    const long double m_value;
};

class CValue_string : public CRawValueBase {
    Q_DISABLE_COPY_MOVE(CValue_string);
public:
    QString value() const {return m_value; }
    explicit CValue_string(const QString & initVal) : m_value(std::move(initVal)) {}
    void accept(CValueVisitor& visitor)  const override;
    virtual QString convertToString() const override {return m_value; } ;
    virtual QVariant convertToVariant() const override{ return  m_value ; }
private:
    const QString m_value;
};

class CValue_bool : public CRawValueBase {
    Q_DISABLE_COPY_MOVE(CValue_bool);
public:
    bool value() const {return m_value; }
    explicit CValue_bool(const bool & initVal) : m_value(initVal) {}
    void accept(CValueVisitor& visitor)  const override;
    virtual QString convertToString() const override {return QString::number((int)m_value); } ;
    virtual QVariant convertToVariant() const override{ return  m_value ; }
private:
    const bool m_value;
};

class CValue_array : public CRawValueBase {
    Q_DISABLE_COPY_MOVE(CValue_array);
public:
    QList<std::shared_ptr<CRawValueBase>> value() const {return m_value; }
    // default constructor
    explicit CValue_array(){};
    // Constructor accepting QList
    explicit CValue_array(const QList<std::shared_ptr<CRawValueBase>>& initVal)   : m_value(initVal) {}
    // accept list of strings
    explicit CValue_array(const QStringList & initVal)  {
        for(const auto & str : initVal){
            m_value.push_back(std::make_shared<CValue_string>(str));
        }
    }
    // Constructor accepting initializer list
    explicit CValue_array(std::initializer_list<std::shared_ptr<CRawValueBase>> initList)  : m_value(initList) {}
    void accept(CValueVisitor& visitor)  const override;
    virtual QString convertToString() const override  ;
    virtual QVariant convertToVariant() const override ;
    int findIndexOfElementInArray(const std::shared_ptr<CRawValueBase> & elmnt ) const ;
    std::shared_ptr<CRawValueBase> operator+(const long long &  rhs) const;
    std::shared_ptr<CRawValueBase> operator+(const long double &  rhs) const;
    std::shared_ptr<CRawValueBase> operator+(const bool &  rhs) const;
    std::shared_ptr<CRawValueBase> operator+(const QString &  rhs) const;
    std::shared_ptr<CRawValueBase> operator+(const CValue_array &  rhs) const;
    friend std::shared_ptr<CRawValueBase> operator+(const QString& lhs, const CValue_array& rhs);

    std::shared_ptr<CRawValueBase> operator*(const long long &  rhs) const;
    std::shared_ptr<CRawValueBase> operator*(const long double &  rhs) const;
    std::shared_ptr<CRawValueBase> operator*(const bool &  rhs) const;
    std::shared_ptr<CRawValueBase> operator*(const QString &  rhs) const;
    std::shared_ptr<CRawValueBase> operator*(const CValue_array &  rhs) const;
    friend std::shared_ptr<CRawValueBase> operator*(const QString& lhs, const CValue_array& rhs);

    std::shared_ptr<CRawValueBase> operator/(const long long &  rhs) const;
    std::shared_ptr<CRawValueBase> operator/(const long double &  rhs) const;
    std::shared_ptr<CRawValueBase> operator/(const bool &  rhs) const;
    std::shared_ptr<CRawValueBase> operator/(const QString &  rhs) const;
    std::shared_ptr<CRawValueBase> operator/(const CValue_array &  rhs) const;
    friend std::shared_ptr<CRawValueBase> operator/(const long long   & lhs, const CValue_array& rhs);
    friend std::shared_ptr<CRawValueBase> operator/(const long double & lhs, const CValue_array& rhs);
    friend std::shared_ptr<CRawValueBase> operator/(const bool &  lhs, const CValue_array& rhs);
    friend std::shared_ptr<CRawValueBase> operator/(const QString& lhs, const CValue_array& rhs);



private:
    /*const*/ QList<std::shared_ptr<CRawValueBase>> m_value;  // TODO: consider using Qvector instead of QList
};

class CValue_map : public CRawValueBase {
    Q_DISABLE_COPY_MOVE(CValue_map);
public:
    QMap<std::shared_ptr<CRawValueBase> , std::shared_ptr<CRawValueBase>>  value() const {return m_value; }
    // Constructor accepting QList
    explicit CValue_map(const QMap<std::shared_ptr<CRawValueBase> , std::shared_ptr<CRawValueBase>> & initVal)   : m_value(initVal) {}
    void accept(CValueVisitor& visitor) const  override;
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
    virtual void visit(const CValue_array& value) = 0;
    virtual void visit(const CValue_map & value) = 0;
};


#endif // CRAWVALUEBASE_H




