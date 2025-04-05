#include "src/CRawValueBase/RawValueBase.h"
#include "src/CommonHeader.h"
#include <QVariantList>

void CValue_array::accept        (CValueVisitor& visitor) const { visitor.visit(*this); }

QString CValue_array::convertToString() const
{
    QString result = "";
    for(auto pVal : m_value){
        result += (pVal->convertToString() + "\n");
    }
    return result ;
}

QVariant CValue_array::convertToVariant() const
{
    QVariantList varList ;
    for(auto pCurrentRawVal : m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            varList.push_back(pVal->value());
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            varList.push_back((float)pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            varList.push_back(pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            varList.push_back(pVal->value());
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            QVariantList innerList ;
            for(auto innerVal: pVal->value()){
                innerList << innerVal->convertToVariant();
            }
            varList <<  QVariant(innerList) ;
        }
    }
    return QVariant(varList); ;
}

int CValue_array::findIndexOfElementInArray(const std::shared_ptr<CRawValueBase> &elmnt) const
{
    if (auto* pVal = dynamic_cast<CValue_int*>(elmnt.get())) {
        int iter =0;
        for(auto pCurrentVal : m_value){
            if (auto* pInVal = dynamic_cast<CValue_int*>(pCurrentVal.get())){
                if( pInVal->value() == pVal->value() ){
                    return iter;
                }
            }
            iter++;
        }
        return -1;
    } else if (auto* pVal = dynamic_cast<CValue_double*>(elmnt.get())) {
        int iter =0;
        for(auto pCurrentVal : m_value){
            if (auto* pInVal = dynamic_cast<CValue_double*>(pCurrentVal.get())){
                if( qFuzzyCompare( (double)pInVal->value() , (double)pVal->value() )){
                    return iter;
                }
            }
            iter++;
        }
        return -1;
    }else if (auto* pVal = dynamic_cast<CValue_bool*>(elmnt.get())) {
        int iter =0;
        for(auto pCurrentVal : m_value){
            if (auto* pInVal = dynamic_cast<CValue_bool*>(pCurrentVal.get())){
                if( pInVal->value() == pVal->value() ){
                    return iter;
                }
            }
            iter++;
        }
        return -1;
    }else if (auto* pVal = dynamic_cast<CValue_string*>(elmnt.get())) {
        int iter =0;
        for(auto pCurrentVal : m_value){
            if (auto* pInVal = dynamic_cast<CValue_string*>(pCurrentVal.get())){
                if( pInVal->value() == pVal->value() ){
                    return iter;
                }
            }
            iter++;
        }
        return -1;
    }else if (auto* pVal = dynamic_cast<CValue_array*>(elmnt.get())) {
        DEBUG_MSG_PRINT << " incomplete funciton called"; // TODO: this method still needs modifications
        int iter =0;
        for(auto pCurrentVal : m_value){
            if (auto* pInVal = dynamic_cast<CValue_array*>(pCurrentVal.get())){
                if(pInVal->value().length() != pVal->value().length() )
                    return -1 ;
                for(auto pInInVal : pInVal->value()){
                    if( pVal->findIndexOfElementInArray(pInInVal) < 0  ){
                        return -1;
                    }
                }
                return iter;
            }
            iter++;
        }
        return -1;
    }
    DEBUG_MSG_PRINT << "invalid type ";
    return -1 ;
}

std::shared_ptr<CRawValueBase> CValue_array::operator+(const long long &rhs) const
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
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal + rhs ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}

std::shared_ptr<CRawValueBase> CValue_array::operator+(const long double &rhs) const
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
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal + rhs ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}

std::shared_ptr<CRawValueBase> CValue_array::operator+(const bool &  rhs) const{
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
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal + rhs ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}


std::shared_ptr<CRawValueBase> CValue_array::operator+(const QString &  rhs) const{
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
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal + rhs ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}


std::shared_ptr<CRawValueBase> operator+(const QString& lhs, const CValue_array& rhs) {
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
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( lhs +  *pVal  ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}


std::shared_ptr<CRawValueBase> CValue_array::operator+(const CValue_array &rhs) const
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
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal + rhs ) ;
        }
    }

    for(int iter = minSize ; iter < biggerList.length() ; iter++ ){
        result.push_back( biggerList.at(iter));
    }
    return std::make_shared<CValue_array>(result) ;
}



std::shared_ptr<CRawValueBase> CValue_array::operator*(const long long &rhs) const
{
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>(pVal->value() * rhs ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(pVal->value() * rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>(pVal->value() * rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( pVal->value().toLongLong() * rhs) ));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal * rhs ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}

std::shared_ptr<CRawValueBase> CValue_array::operator*(const long double &rhs) const
{
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(pVal->value() * rhs ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(pVal->value() * rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(pVal->value() * rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number(  pVal->value().toDouble() * rhs , 'f' , MAX_DOUBLE_PRECISION)  ));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal * rhs ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}

std::shared_ptr<CRawValueBase> CValue_array::operator*(const bool &  rhs) const{
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>(pVal->value() * rhs ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(pVal->value() * rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>(pVal->value() * rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>(  QString::number( pVal->value().toLongLong() *  rhs )   ));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal * rhs ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}


std::shared_ptr<CRawValueBase> CValue_array::operator*(const QString &  rhs) const{
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>(  QString::number(pVal->value() * rhs.toLongLong() )  ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number(pVal->value() * rhs.toDouble(), 'f' , MAX_DOUBLE_PRECISION)  ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>(QString::number(pVal->value() * rhs.toLongLong() )  ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( pVal->value().toLongLong() *  rhs.toLongLong()  )));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal * rhs ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}


std::shared_ptr<CRawValueBase> operator*(const QString& lhs, const CValue_array& rhs) {
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : rhs.m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( lhs.toLongLong() *  pVal->value())  ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>(  QString::number( lhs.toDouble() * pVal->value(), 'f' , MAX_DOUBLE_PRECISION)  ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( lhs.toLongLong() * pVal->value())  ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( lhs.toLong() *  pVal->value().toLongLong()  ) ));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( lhs *  *pVal  ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}



std::shared_ptr<CRawValueBase> CValue_array::operator*(const CValue_array &rhs) const
{
    int minSize = std::min( rhs.m_value.length() , m_value.length() );
    const auto & biggerList = rhs.m_value.length() > m_value.length() ? rhs.m_value : m_value ;
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(int iter=0; iter < minSize ; iter++){
        auto pCurrentRawVal = m_value.at(iter);
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back(  rhs * pVal->value()  );
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back(  rhs * pVal->value() );
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back(  rhs * pVal->value()   );
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back(  pVal->value() * rhs  );
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal * rhs ) ;
        }
    }

    for(int iter = minSize ; iter < biggerList.length() ; iter++ ){
        result.push_back( biggerList.at(iter));
    }
    return std::make_shared<CValue_array>(result) ;
}






std::shared_ptr<CRawValueBase> CValue_array::operator/(const long long &rhs) const
{
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>((long double)pVal->value() / rhs ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(pVal->value() / rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>((long double)pVal->value() / rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( pVal->value().toLongLong() / rhs) ));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal / rhs ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}

std::shared_ptr<CRawValueBase> CValue_array::operator/(const long double &rhs) const
{
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(pVal->value() / rhs ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(pVal->value() / rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(pVal->value() / rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number(  pVal->value().toDouble() / rhs , 'f' , MAX_DOUBLE_PRECISION)  ));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal / rhs ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}

std::shared_ptr<CRawValueBase> CValue_array::operator/(const bool &  rhs) const{
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(pVal->value() / rhs ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(pVal->value() / rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(pVal->value() / rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>(  QString::number( pVal->value().toLongLong() /  rhs )   ));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal / rhs ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}


std::shared_ptr<CRawValueBase> CValue_array::operator/(const QString &  rhs) const{
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>(  QString::number(pVal->value() / rhs.toLongLong() )  ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number(pVal->value() / rhs.toDouble(), 'f' , MAX_DOUBLE_PRECISION)  ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>(QString::number(pVal->value() / rhs.toLongLong() )  ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( pVal->value().toLongLong() /  rhs.toLongLong()  )));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal / rhs ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}




std::shared_ptr<CRawValueBase> CValue_array::operator/(const CValue_array &rhs) const
{
    int minSize = std::min( rhs.m_value.length() , m_value.length() );
    const auto & biggerList = rhs.m_value.length() > m_value.length() ? rhs.m_value : m_value ;
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(int iter=0; iter < minSize ; iter++){
        auto pCurrentRawVal = m_value.at(iter);
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back(    pVal->value() / rhs  );
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back(   pVal->value() / rhs );
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back(   pVal->value() / rhs  );
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back(  pVal->value() / rhs  );
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal / rhs ) ;
        }
    }

    for(int iter = minSize ; iter < biggerList.length() ; iter++ ){
        result.push_back( biggerList.at(iter));
    }
    return std::make_shared<CValue_array>(result) ;
}


std::shared_ptr<CRawValueBase> operator/(const long long   & lhs, const CValue_array& rhs) {
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : rhs.m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(  (long double)lhs/ pVal->value())  );
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>( (long double)lhs / pVal->value()  ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(  (long double)lhs / pVal->value())  );
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>( (long double)lhs /  pVal->value().toLongLong()  ) );
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( lhs /  *pVal  ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}

std::shared_ptr<CRawValueBase> operator/(const long double & lhs, const CValue_array& rhs) {
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : rhs.m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(  lhs / pVal->value())  );
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(  lhs / pVal->value()  ) );
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>( lhs / pVal->value())  );
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( (double)(lhs /  pVal->value().toDouble())  ) ));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( lhs /  *pVal  ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}

std::shared_ptr<CRawValueBase> operator/(const bool &  lhs, const CValue_array& rhs) {
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : rhs.m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(  lhs / pVal->value())  );
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(   lhs / pVal->value() ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_double>(  lhs / pVal->value())  );
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( lhs /  pVal->value().toLongLong()  ) ));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( lhs /  *pVal  ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}


std::shared_ptr<CRawValueBase> operator/(const QString& lhs, const CValue_array& rhs) {
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : rhs.m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( lhs.toLongLong() / pVal->value())  ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>(  QString::number( lhs.toDouble() / pVal->value(), 'f' , MAX_DOUBLE_PRECISION)  ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( lhs.toLongLong() / pVal->value())  ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( lhs.toLong() /  pVal->value().toLongLong()  ) ));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( lhs /  *pVal  ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}


std::shared_ptr<CRawValueBase> CValue_array::operator%(const long long &rhs) const
{
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>( pVal->value() % rhs ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>((long long)pVal->value() % rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>((long long)pVal->value() % rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( pVal->value().toLongLong() % rhs) ));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal % rhs ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}

std::shared_ptr<CRawValueBase> CValue_array::operator%(const long double &rhs) const
{
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>((long long)pVal->value() % (long long)rhs ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>((long long)pVal->value() %(long long) rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>((long long)pVal->value() % (long long)rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number(  (long long)pVal->value().toDouble() % (long long)rhs , 'f' , MAX_DOUBLE_PRECISION)  ));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal % rhs ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}

std::shared_ptr<CRawValueBase> CValue_array::operator%(const bool &  rhs) const{
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>(pVal->value() % rhs ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>((long long)pVal->value() % rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>(pVal->value() % rhs ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>(  QString::number( pVal->value().toLongLong() %  rhs )   ));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal % rhs ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}


std::shared_ptr<CRawValueBase> CValue_array::operator%(const QString &  rhs) const{
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>(  QString::number(pVal->value() % rhs.toLongLong() )  ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number((long long)pVal->value() % (long long)rhs.toDouble(), 'f' , MAX_DOUBLE_PRECISION)  ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>(QString::number(pVal->value() % rhs.toLongLong() )  ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( pVal->value().toLongLong() %  rhs.toLongLong()  )));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal % rhs ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}




std::shared_ptr<CRawValueBase> CValue_array::operator%(const CValue_array &rhs) const
{
    int minSize = std::min( rhs.m_value.length() , m_value.length() );
    const auto & biggerList = rhs.m_value.length() > m_value.length() ? rhs.m_value : m_value ;
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(int iter=0; iter < minSize ; iter++){
        auto pCurrentRawVal = m_value.at(iter);
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back(    pVal->value() % rhs  );
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back(   pVal->value() % rhs );
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back(   pVal->value() % rhs  );
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back(  pVal->value() % rhs  );
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( *pVal % rhs ) ;
        }
    }

    for(int iter = minSize ; iter < biggerList.length() ; iter++ ){
        result.push_back( biggerList.at(iter));
    }
    return std::make_shared<CValue_array>(result) ;
}


std::shared_ptr<CRawValueBase> operator%(const long long   & lhs, const CValue_array& rhs) {
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : rhs.m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>( (long long)lhs% pVal->value())  );
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>( (long long)lhs % (long long)pVal->value()  ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>(  (long long)lhs % pVal->value())  );
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>( (long long)lhs %  pVal->value().toLongLong()  ) );
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( lhs %  *pVal  ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}

std::shared_ptr<CRawValueBase> operator%(const long double & lhs, const CValue_array& rhs) {
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : rhs.m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>(  (long long)lhs % pVal->value())  );
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>(  (long long)lhs % (long long)pVal->value()  ) );
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>( (long long)lhs % pVal->value())  );
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( ((long long)lhs %  (long long)pVal->value().toDouble())  ) ));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( lhs %  *pVal  ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}

std::shared_ptr<CRawValueBase> operator%(const bool &  lhs, const CValue_array& rhs) {
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : rhs.m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>(  lhs % pVal->value())  );
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>(   (long long)lhs % (long long)pVal->value() ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_int>(  lhs % pVal->value())  );
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( lhs %  pVal->value().toLongLong()  ) ));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( lhs %  *pVal  ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}


std::shared_ptr<CRawValueBase> operator%(const QString& lhs, const CValue_array& rhs) {
    QList<std::shared_ptr<CRawValueBase>> result ;
    for(auto pCurrentRawVal : rhs.m_value){
        if (auto* pVal = dynamic_cast<CValue_int*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( lhs.toLongLong() % pVal->value())  ));
        } else if (auto* pVal = dynamic_cast<CValue_double*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>(  QString::number( (long long)lhs.toDouble() % (long long)pVal->value(), 'f' , MAX_DOUBLE_PRECISION)  ));
        }else if (auto* pVal = dynamic_cast<CValue_bool*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( lhs.toLongLong() % pVal->value())  ));
        }else if (auto* pVal = dynamic_cast<CValue_string*>(pCurrentRawVal.get())) {
            result.push_back( std::make_shared<CValue_string>( QString::number( lhs.toLong() %  pVal->value().toLongLong()  ) ));
        }else if (auto* pVal = dynamic_cast<CValue_array*>(pCurrentRawVal.get())) {
            result.push_back( lhs %  *pVal  ) ;
        }
    }
    return std::make_shared<CValue_array>(result) ;
}
