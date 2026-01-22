#ifndef CLIVEDATAXYMODEL_H
#define CLIVEDATAXYMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QPointF>
#include <QtQml>

class CLiveDataXYModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Provided in C++ only; it cannot be created in QML")
    Q_PROPERTY(int totalLengthOfSessionData READ totalLengthOfSessionData NOTIFY totalLengthOfSessionDataChanged)
    Q_PROPERTY(float maxValueLiveData MEMBER m_maxValueLiveData NOTIFY maxValueLiveDataChanged)
    Q_PROPERTY(float minValueLiveData MEMBER m_minValueLiveData NOTIFY minValueLiveDataChanged)
    Q_PROPERTY(float lastLiveCapturedVal MEMBER m_lastLiveCapturedVal NOTIFY totalLengthOfSessionDataChanged)
    Q_PROPERTY(int movingWindowLength READ movingWindowLength WRITE setMovingWindowLength NOTIFY movingWindowLengthChanged)
    Q_PROPERTY(int totalPointsCounter READ totalPointsCounter WRITE setTotalPointsCounter NOTIFY totalPointsCounterChanged)

  public: // functions
    explicit CLiveDataXYModel();
    ~CLiveDataXYModel();

    // override functions for QAbstractTableModel -> used in line chart
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    /*!
     * \brief getMaxDataValue
     * getter function for max value
     * \return
     */
    int getMaxDataValue() const;
    int getMinDataValue() const;

    /*!
     * \brief totalLengthOfSessionData
     * this is in fact number of points receved in current session, in other word, this is
     * length of m_mainListOfValues
     * \return
     */
    int totalLengthOfSessionData() const;

    int movingWindowLength() const;
    void setMovingWindowLength(int newValue);

    int totalPointsCounter() const;
    void setTotalPointsCounter(int newTotalPointsCounter);

  public slots:
    /*!
     * \brief newDataReceivedFromTerminal
     * \param newDataValue
     * this is connected to the outside world and it is called whenever a new data is recvd
     */
    void newDataReceivedFromTerminal(const float& newDataValue);
    QList<QPointF*> mainListOfValues() { return m_mainListOfValues; }

    void resetRequestReceived();

  private: // variables
    /*!
     * \brief m_totalLengthOfSessionData
     * this is in fact number of points receved in current session, in other word, this is
     * length of m_mainListOfValues
     */
    int m_totalLengthOfSessionData = 0;

    /*!
     * \brief m_maxValueLiveData
     * maximum value between receieved values
     */
    float m_maxValueLiveData = 0;

    /*!
     * \brief m_minValueLiveData
     * minimum values between receieved values
     */
    float m_minValueLiveData = 0;

    /*!
     * \brief m_lastLiveCapturedVal
     * last value received from terminal
     */
    float m_lastLiveCapturedVal = 0;

    /*!
     * \brief m_mainListOfValues
     * this is the list of values recenved from terminal
     */
    QList<QPointF*> m_mainListOfValues{};

    /*!
     * \brief m_movingWindowLength
     * we capture data in the list untill it reaches to m_movingWindowLength number of points, after this
     * time for every point we receive we remove the oldest point in the list, so its like we are moving the window
     * on the time axis and m_movingWindowLength is the length of this window
     */
    int m_movingWindowLength = 300;

    /*!
     * \brief m_totalPointsCounter
     * this starts counting the number of points received from the terminal and is used
     * as the x axis of the chart, we can not use length of the m_mainListOfValues as the x
     * bcz when the length reaches to m_movingWindowLength it will be fixed
     */
    int m_totalPointsCounter = 0;

  signals:

    void totalLengthOfSessionDataChanged();
    void maxValueLiveDataChanged();
    void minValueLiveDataChanged();
    void movingWindowLengthChanged();
    void totalPointsCounterChanged();
};

#endif // CLIVEDATAXYMODEL_H
