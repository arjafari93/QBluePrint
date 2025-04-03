#ifndef CBLUEPRINTPAGE_H
#define CBLUEPRINTPAGE_H


#include <QObject>
#include <QDebug>

#include "src/CFlowConnectionLine/FlowConnectionLine.h"
#include "src/COperationBox/OperationBox.h"

class CIOTerminal;

class CBluePrintPage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isLineFlowDrawActive MEMBER m_isLineFlowDrawActive NOTIFY isLineFlowDrawActiveChanged)
    Q_PROPERTY( QQmlListProperty<COperationBox> listOfBlueBoxes READ listOfBlueBoxes NOTIFY  listOfBlueBoxesChanged )
    Q_PROPERTY( QString currentBluePrintFilePath READ currentBluePrintFilePath WRITE setCurrentBluePrintFilePath NOTIFY currentBluePrintFilePathChanged)
    Q_PROPERTY( QQmlListProperty<CFlowConnectionLine> listOfFlowConnectionLines READ listOfFlowConnectionLines NOTIFY  listOfFlowConnectionLinesChanged )
    Q_PROPERTY(float applicationScaleFactor READ applicationScaleFactor WRITE setApplicationScaleFactor NOTIFY applicationScaleFactorChanged)
    Q_PROPERTY(int maxBPBoxXpos MEMBER m_maxBPBoxXpos NOTIFY maxBPBoxXposChanged)
    Q_PROPERTY(int maxBPBoxYpos MEMBER m_maxBPBoxYpos NOTIFY maxBPBoxYposChanged)

    friend class CBPBoxManager;
private:
    explicit          CBluePrintPage(QObject *parent = nullptr);
    COperationBox *   checkIntersectionsWithBoxes( const int & absPosX , const int & absPosY);
    CIOTerminal*      checkIntersectionsWithTerminals(COperationBox *boxToBeSearched , const int & absPosX , const int & absPosY  );
    void              recalculateMaxPositions();

public:
    ~CBluePrintPage();
    QQmlListProperty<COperationBox>        listOfBlueBoxes() ;
    QQmlListProperty<CFlowConnectionLine>  listOfFlowConnectionLines() ;

    Q_INVOKABLE void  lineFlowStartedFromConnectionPoint( QObject * startTerminal );
    Q_INVOKABLE void  lineFlowPosChagnedFromConnectionPoint(const int & relPosX , const int & relPosY, const int & absPosX , const int & absPosY);
    Q_INVOKABLE void  lineFlowReleased(const int & absPosX , const int & absPosY );
    Q_INVOKABLE void  removeLineFromListModel( CFlowConnectionLine * lineToBeRemoved );
    Q_INVOKABLE void  removeBPBoxFromListModel(QObject * boxToBeRemoved );
    Q_INVOKABLE bool  createNewBoxFromGivenType( const QString & boxName , const int & posX , const int & posY , const bool & emitSignal = true );
    Q_INVOKABLE bool  saveBluePrintInfo(const QString & pathToFile)  ;
    Q_INVOKABLE bool  loadBluePrintInfo(const QString & pathToFile);
    Q_INVOKABLE void  clearCurrentBluePrintSession( );

    float applicationScaleFactor() const {return m_applicationScaleFactor; }
    void  setApplicationScaleFactor(const float & newValue );

    const QString &currentBluePrintFilePath() const;
    void setCurrentBluePrintFilePath(const QString &newCurrentBluePrintFilePath);

    COperationBox * getBPBoxFromUniqueID(const int &BPBoxID);

private:  // variables
    QList<COperationBox*>          m_listOfBlueBoxes; // user has created these
    QList<CFlowConnectionLine*>    m_listOfFlowConnectionLines;
    bool                           m_isLineFlowDrawActive = false ;
    CIOTerminal *                  mp_lastGlowingTerminal = nullptr ;
    float                          m_applicationScaleFactor = 1.0 ;
    QString                        m_currentBluePrintFilePath = "" ;
    int                            m_maxBPBoxXpos = 0 ;
    int                            m_maxBPBoxYpos = 0 ;




signals:

    void   maxBPBoxYposChanged () ;
    void   maxBPBoxXposChanged () ;
    void   listOfBlueBoxesChanged();
    void   isLineFlowDrawActiveChanged();
    void   applicationScaleFactorChanged();
    void   listOfFlowConnectionLinesChanged() ;
    void   currentBluePrintFilePathChanged();
};


#endif // CBLUEPRINTPAGE_H
