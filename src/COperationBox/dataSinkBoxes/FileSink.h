#ifndef CFILESINK_H
#define CFILESINK_H

#include "../OperationBox.h"
#include <QObject>

class QTimer;

class CFileSink : public COperationBox
{
    Q_OBJECT

    friend class CFileSinkFactory;
    Q_DISABLE_COPY_MOVE(CFileSink)
    explicit CFileSink(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent = nullptr);

  public:
    ~CFileSink();
    virtual void evaluateOperation() override;
    GETUNIQUENAMEFUNC;

  private slots:
    void flushStringsIntoFile();

  private:
    inline const static QString m_uniqueBoxName = "File Sink";
    QString m_pathToFile = "";
    QVector<QString> m_bufferOfStrings;
    const int m_maxBufferSize = 100;
    QTimer* mp_flushTimer{nullptr};
    const int m_flushTimerIntervalMS = 90000;
};

#endif // CFILESINK_H
