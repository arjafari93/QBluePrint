#include "RawValueBase.h"




void CValue_int::accept         (CValueVisitor& visitor) { visitor.visit(*this); }


void CValue_double::accept      (CValueVisitor& visitor) { visitor.visit(*this); }
void CValue_string::accept      (CValueVisitor& visitor) { visitor.visit(*this); }
void CValue_bool::accept        (CValueVisitor& visitor) { visitor.visit(*this); }
void CValue_list::accept        (CValueVisitor& visitor) { visitor.visit(*this); }

std::shared_ptr<CRawValueBase> CValue_list::operator+(const long long &rhs) const
{
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>(pVal->value() + rhs ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(pVal->value() + rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>(pVal->value() + rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
           result.push_back( std::make_shared<CValue_string>( pVal->value() + QString::number(rhs ) ));
        }if (auto* pVal = dynamic_cast<CValue_list*>(pCurrentRawVal.get())) {
            result.push_back( *pVal + rhs ) ;
        }
    }
    return std::make_shared<CValue_list>(result) ;
}

std::shared_ptr<CRawValueBase> CValue_list::operator+(const long double &rhs) const
{
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(pVal->value() + rhs ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(pVal->value() + rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(pVal->value() + rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
           result.push_back( std::make_shared<CValue_string>( pVal->value() + QString::number( rhs , 'f' , MAX_DOUBLE_PRECISION) ));
        }if (auto* pVal = dynamic_cast<CValue_list*>(pCurrentRawVal.get())) {
            result.push_back( *pVal + rhs ) ;
        }
    }
    return std::make_shared<CValue_list>(result) ;
}

std::shared_ptr<CRawValueBase> CValue_list::operator+(const bool &  rhs) const{
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>(pVal->value() + rhs ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(pVal->value() + rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>(pVal->value() + rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
           result.push_back( std::make_shared<CValue_string>( pVal->value() + QString::number(rhs ) ));
        }if (auto* pVal = dynamic_cast<CValue_list*>(pCurrentRawVal.get())) {
            result.push_back( *pVal + rhs ) ;
        }
    }
    return std::make_shared<CValue_list>(result) ;
}


std::shared_ptr<CRawValueBase> CValue_list::operator+(const QString &  rhs) const{
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>(  QString::number(pVal->value()) + rhs ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number(pVal->value(), 'f' , MAX_DOUBLE_PRECISION) + rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>(QString::number(pVal->value()) + rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
           result.push_back( std::make_shared<CValue_string>( pVal->value() +  rhs  ));
        }if (auto* pVal = dynamic_cast<CValue_list*>(pCurrentRawVal.get())) {
            result.push_back( *pVal + rhs ) ;
        }
    }
    return std::make_shared<CValue_list>(result) ;
}


std::shared_ptr<CRawValueBase> operator+(const QString& lhs, const CValue_list& rhs) {
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : rhs.m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>(  lhs +  QString::number(pVal->value())  ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( lhs +  QString::number(pVal->value(), 'f' , MAX_DOUBLE_PRECISION)  ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( lhs + QString::number(pVal->value())  ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
           result.push_back( std::make_shared<CValue_string>( lhs +  pVal->value()   ));
        }if (auto* pVal = dynamic_cast<CValue_list*>(pCurrentRawVal.get())) {
            result.push_back( lhs +  *pVal  ) ;
        }
    }
    return std::make_shared<CValue_list>(result) ;
}



std::shared_ptr<CRawValueBase> CValue_list::operator+(const CValue_list &rhs) const
{
    int minSize = std::min( rhs.m_value.length() , m_value.length() );
    const auto & biggerList = rhs.m_value.length() > m_value.length() ? rhs.m_value : m_value ;
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(int iter=0; iter < minSize ; iter++){
        auto pCurrentRawVal = m_value.at(iter);
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back(  rhs + pVal->value()  );
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back(  rhs + pVal->value() );
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back(  rhs + pVal->value()   );
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
           result.push_back(  pVal->value() + rhs  );
        }if (auto* pVal = dynamic_cast<CValue_list*>(pCurrentRawVal.get())) {
            result.push_back( *pVal + rhs ) ;
        }
    }

    for(int iter = minSize ; iter < biggerList.length() ; iter++ ){
         result.push_back( biggerList.at(iter));
    }
    return std::make_shared<CValue_list>(result) ;
}








void CValue_map::accept         (CValueVisitor& visitor) { visitor.visit(*this); }
