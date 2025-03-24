#include "LiveDataXYModel.h"


#include "src/CommonHeader.h"

CLiveDataXYModel::CLiveDataXYModel()
{
    m_minValueLiveData =  std::numeric_limits<float>::max() ;
    m_maxValueLiveData =  std::numeric_limits<float>::min() ;

}

CLiveDataXYModel::~CLiveDataXYModel()
{
    qDeleteAll(m_mainListOfValues);
}


int CLiveDataXYModel::totalLengthOfSessionData() const
{
    return m_mainListOfValues.length();
}


void CLiveDataXYModel::resetRequestReceived()
{
    beginResetModel();
    qDeleteAll(m_mainListOfValues);
    m_mainListOfValues.clear();
    endResetModel();

    m_minValueLiveData =  std::numeric_limits<float>::max() ;
    m_maxValueLiveData =  std::numeric_limits<float>::min() ;

    m_lastLiveCapturedVal = 0 ;
    m_totalLengthOfSessionData    = 0 ;
    m_totalPointsCounter = 0 ;

    emit totalLengthOfSessionDataChanged();
    emit maxValueLiveDataChanged () ;
    emit minValueLiveDataChanged () ;
}

int CLiveDataXYModel::totalPointsCounter() const
{
    return m_totalPointsCounter;
}

void CLiveDataXYModel::setTotalPointsCounter(int newTotalPointsCounter)
{
    if (m_totalPointsCounter == newTotalPointsCounter)
        return;
    m_totalPointsCounter = newTotalPointsCounter;
    emit totalPointsCounterChanged();
}

int CLiveDataXYModel::movingWindowLength() const
{
    return m_movingWindowLength;
}

void CLiveDataXYModel::setMovingWindowLength(int newValue)
{
    if (m_movingWindowLength == newValue)
        return;
    if(newValue < 10)
        return ;
    m_movingWindowLength = newValue;
    emit movingWindowLengthChanged();
}


void CLiveDataXYModel::newDataReceivedFromTerminal(const float &newDataValue)
{
    // add data to main original list
    m_lastLiveCapturedVal = newDataValue ;

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    QPointF *  tempPoint = new  QPointF( m_totalPointsCounter  , newDataValue );
    m_mainListOfValues.push_back(  tempPoint );
    m_totalLengthOfSessionData =  m_mainListOfValues.length();
    endInsertRows();

    // Handle window length constraint
    while (m_mainListOfValues.length() > m_movingWindowLength) {
        beginRemoveRows(QModelIndex(), 0, 0); // Notify that the first row is being removed
        auto pFrontVal = m_mainListOfValues.front();
        m_mainListOfValues.pop_front();
        delete pFrontVal;
        endRemoveRows();
    }

    emit totalLengthOfSessionDataChanged();
    if(newDataValue > m_maxValueLiveData ){
        m_maxValueLiveData = newDataValue ;
        emit maxValueLiveDataChanged () ;
    }

    if(newDataValue < m_minValueLiveData ){
        m_minValueLiveData = newDataValue ;
        emit minValueLiveDataChanged () ;
    }
    m_totalPointsCounter++;
    emit totalPointsCounterChanged();
}


int CLiveDataXYModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_mainListOfValues.length();
}


int CLiveDataXYModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2; // we are dealing with QPoints , so we have x and y, this 2 is for x and y for each row
}


QVariant CLiveDataXYModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation)
    Q_UNUSED(role)
    if(section == 0)
        return "x";
    else
        return "y";
}


QVariant CLiveDataXYModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role);
    if(index.row() >= m_mainListOfValues.length() ){ // this should never happen
        DEBUG_MSG_PRINT << " index out of range  " << index.row() << m_mainListOfValues.length() ;
        return QVariant();
    }

    if (index.column() == 0)
        return m_mainListOfValues[index.row()]->x();
    else
        return m_mainListOfValues[index.row()]->y();
}


int CLiveDataXYModel::getMaxDataValue() const
{
    return m_maxValueLiveData ;
}

int CLiveDataXYModel::getMinDataValue() const
{
    return    m_minValueLiveData ;
}




