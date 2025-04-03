#ifndef CSTOPWATCH_H
#define CSTOPWATCH_H

#include <QObject>
#include <chrono>
#include "../OperationBox.h"
class QTimer ;

class CStopWatch : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(bool stopWatchRunning    READ stopWatchRunning WRITE setStopWatchRunning NOTIFY stopWatchRunningChanged  )
    Q_PROPERTY(int  elapsedTime         READ elapsedTime      WRITE setElapsedTime      NOTIFY elapsedTimeChanged       )
    friend class CStopWatchFactory ;
    Q_DISABLE_COPY_MOVE(CStopWatch)
    explicit CStopWatch(
            int      newBlueBox_xPos  ,
            int      newBlueBox_yPos  ,
            QObject *parent = nullptr );
public:
    ~CStopWatch();
    virtual void  evaluateOperation(  ) override ;
    GETUNIQUENAMEFUNC;

    bool stopWatchRunning() const;
    void setStopWatchRunning(bool newStopWatchRunning);

    int elapsedTime() const;
    void setElapsedTime(int newElapsedTime);

private:
    inline const static QString    m_uniqueBoxName  = "Stop Watch" ;
    bool    m_stopWatchRunning = false ;
    QTimer * mp_internalTimer = nullptr;
    int m_elapsedTime = 0;
    std::chrono::high_resolution_clock::time_point  m_startTime  {};

signals:
    void stopWatchRunningChanged();
    void elapsedTimeChanged();


};



#endif // CSTOPWATCH_H
