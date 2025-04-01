#ifndef CBPBOXMANAGER_H
#define CBPBOXMANAGER_H

/*
 * Copyright (c) 2025 Alireza Jafari (https://github.com/arjafari93)
 *
 * This software is provided "as is", without warranty of any kind.
 * You may use, modify, and distribute this software, but you MUST keep
 * this copyright notice and credit the original author.
 *
 * Licensed under the BSD 3-Clause License
 */

#include <QObject>
#include <QDebug>

#include "src/CFlowConnectionLine/FlowConnectionLine.h"
#include "src/COperationBox/OperationBox.h"

class CIOTerminal;

class CBPBoxManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isLineFlowDrawActive MEMBER m_isLineFlowDrawActive NOTIFY isLineFlowDrawActiveChanged)
    Q_PROPERTY( QQmlListProperty<COperationBox> listOfBlueBoxes READ listOfBlueBoxes NOTIFY  listOfBlueBoxesChanged )
    Q_PROPERTY( QQmlListProperty<COperationBox> bpBoxBrowserList READ bpBoxBrowserList NOTIFY  bpBoxBrowserListChanged )
    Q_PROPERTY( QQmlListProperty<COperationBox> bpBoxBrowserListProxy READ bpBoxBrowserListProxy NOTIFY  bpBoxBrowserListProxyChanged )
    Q_PROPERTY(bool isArchiveSearchActive READ isArchiveSearchActive WRITE setIsArchiveSearchActive NOTIFY isArchiveSearchActiveChanged)
    Q_PROPERTY(QString currentBluePrintFilePath READ currentBluePrintFilePath WRITE setCurrentBluePrintFilePath NOTIFY currentBluePrintFilePathChanged)
    Q_PROPERTY( QQmlListProperty<CFlowConnectionLine> listOfFlowConnectionLines READ listOfFlowConnectionLines NOTIFY  listOfFlowConnectionLinesChanged )
    Q_PROPERTY(float applicationScaleFactor READ applicationScaleFactor WRITE setApplicationScaleFactor NOTIFY applicationScaleFactorChanged)
    Q_PROPERTY(bool darkThemeEnabled READ darkThemeEnabled WRITE setDarkThemeEnabled NOTIFY darkThemeEnabledChanged)
    Q_PROPERTY(int maxBPBoxXpos MEMBER m_maxBPBoxXpos NOTIFY maxBPBoxXposChanged)
    Q_PROPERTY(int maxBPBoxYpos MEMBER m_maxBPBoxYpos NOTIFY maxBPBoxYposChanged)

private:
    explicit          CBPBoxManager(QObject *parent = nullptr);
    COperationBox *   checkIntersectionsWithBoxes( const int & absPosX , const int & absPosY);
    CIOTerminal*         checkIntersectionsWithTerminals(COperationBox *boxToBeSearched , const int & absPosX , const int & absPosY  );
    void              recalculateMaxPositions();

public:
    ~CBPBoxManager();
    static CBPBoxManager *                 getInstance() ;
    QQmlListProperty<COperationBox>        listOfBlueBoxes() ;
    QQmlListProperty<COperationBox>        bpBoxBrowserList() ;
    QQmlListProperty<COperationBox>        bpBoxBrowserListProxy() ;
    QQmlListProperty<CFlowConnectionLine>  listOfFlowConnectionLines() ;

    Q_INVOKABLE void  lineFlowStartedFromConnectionPoint( QObject * startTerminal );
    Q_INVOKABLE void  lineFlowPosChagnedFromConnectionPoint(const int & relPosX , const int & relPosY, const int & absPosX , const int & absPosY);
    Q_INVOKABLE void  lineFlowReleased(const int & absPosX , const int & absPosY );
    Q_INVOKABLE void  removeLineFromListModel( CFlowConnectionLine * lineToBeRemoved );
    Q_INVOKABLE void  removeBPBoxFromListModel(QObject * boxToBeRemoved );
    Q_INVOKABLE bool  createNewBoxFromGivenType( const QString & boxName , const int & posX , const int & posY  );
    Q_INVOKABLE bool saveBluePrintInfo(const QString & pathToFile)  ;
    Q_INVOKABLE bool  loadBluePrintInfo(const QString & pathToFile);
    Q_INVOKABLE void  boxListSearchBoxTextChanged(const QString & newSearch);
    Q_INVOKABLE void  clearCurrentBluePrintSession( );

    float applicationScaleFactor() const {return m_applicationScaleFactor; }
    void  setApplicationScaleFactor(const float & newValue );

    COperationBox* getBPBoxFromUniqieID(const int & BPBoxID );


    bool darkThemeEnabled() const;
    void setDarkThemeEnabled(bool newDarkThemeEnabled);

    bool isArchiveSearchActive() const;
    void setIsArchiveSearchActive(bool newIsArchiveSearchActive);

    const QString &currentBluePrintFilePath() const;
    void setCurrentBluePrintFilePath(const QString &newCurrentBluePrintFilePath);

private:  // variables
    QList<COperationBox*>                              m_listOfBlueBoxes; // user has created these
    QList<COperationBox*>                              m_bpBoxBrowserList; // list of items in the left menue
    QList<COperationBox*>                              m_bpBoxBrowserListProxy ; // list of items in the left menu in search mode
    bool                                               m_isArchiveSearchActive  = false  ;
    QList<CFlowConnectionLine*>                        m_listOfFlowConnectionLines;
    bool                                               m_isLineFlowDrawActive = false ;
    CIOTerminal *                                      mp_lastGlowingTerminal = nullptr ;
    float                                              m_applicationScaleFactor = 1.0 ;
    QString                                            m_currentBluePrintFilePath = "" ;
    bool                                               m_darkThemeEnabled = true ;
    int                                                m_maxBPBoxXpos = 0 ;
    int                                                m_maxBPBoxYpos = 0 ;




signals:

    void   maxBPBoxYposChanged () ;
    void   maxBPBoxXposChanged () ;
    void   listOfBlueBoxesChanged();
    void   bpBoxBrowserListChanged();
    void   bpBoxBrowserListProxyChanged();
    void   darkThemeEnabledChanged();
    void   isLineFlowDrawActiveChanged();
    void   applicationScaleFactorChanged();
    void   listOfFlowConnectionLinesChanged() ;
    void   showStatusBarMessage(const QString & msgText , const int & msgDuration , const QColor & msgColor = QColor(255,255,255));
    void   isArchiveSearchActiveChanged();
    void   currentBluePrintFilePathChanged();
};

#endif // CBPBOXMANAGER_H
