#ifndef COPERATIONBOX_H
#define COPERATIONBOX_H

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
#include <QQmlListProperty>
#include <QColor>
#include "src/CBPStatic/BPStatic.h"


class CInputTerminal  ;
class COutputTerminal ;

class CValue_string  ;
class CValue_double  ;
class CValue_int     ;
class CRawValueBase  ;
class QJsonObject    ;

class COperationBox : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString  blueBox_name        READ blueBox_name       WRITE setBlueBox_name       NOTIFY  blueBox_nameChanged       )
    Q_PROPERTY(QString  blueBox_keyWords    READ blueBox_keyWords   WRITE setBlueBox_keyWords   NOTIFY  blueBox_keyWordsChanged   )
    Q_PROPERTY(int      blueBox_xPos        READ blueBox_xPos       WRITE setBlueBox_xPos       NOTIFY  blueBox_xPosChanged       )
    Q_PROPERTY(int      blueBox_yPos        READ blueBox_yPos       WRITE setBlueBox_yPos       NOTIFY  blueBox_yPosChanged       )
    Q_PROPERTY(int      blueBox_width       READ blueBox_width      WRITE setBlueBox_width      NOTIFY  blueBox_widthChanged      )
    Q_PROPERTY(int      blueBox_height      READ blueBox_height     WRITE setBlueBox_height     NOTIFY  blueBox_heightChanged     )
    Q_PROPERTY(CBPStatic::EBPDelegateGUIType  blueBox_GUIType  MEMBER m_blueBox_GUIType CONSTANT)
    Q_PROPERTY(CBPStatic::EBPBoxCategoryType  blueBox_Catgr  MEMBER m_blueBox_Catgr CONSTANT)
    Q_PROPERTY(QString  blueBox_settingQMLPath  MEMBER m_blueBox_settingQMLPath CONSTANT  )
    Q_PROPERTY(QString  blueBox_HeaderIcon      MEMBER m_blueBox_HeaderIcon     CONSTANT  )
    Q_PROPERTY(QColor   blueBox_HeadColor       MEMBER m_blueBox_HeadColor      CONSTANT  )
    Q_PROPERTY(QQmlListProperty<COutputTerminal>   listOfOutputTerminals  READ   listOfOutputTerminals  NOTIFY  listOfOutputTerminalsChanged )
    Q_PROPERTY(QQmlListProperty<CInputTerminal>    listOfInputTerminals   READ   listOfInputTerminals   NOTIFY  listOfInputTerminalsChanged  )


public:
    Q_DISABLE_COPY_MOVE(COperationBox)
    explicit COperationBox(QObject *parent = nullptr) = delete;
    explicit COperationBox(QString  newBlueBox_name  ,
                           int      newBlueBox_xPos  ,
                           int      newBlueBox_yPos  ,
                           int      newBlueBox_width ,
                           int      newBlueBox_height ,
                           QObject *parent = nullptr );

    virtual void  evaluateOperation( ) = 0 ;

    QQmlListProperty<COutputTerminal>             listOfOutputTerminals () ;
    QQmlListProperty<CInputTerminal>              listOfInputTerminals  () ;

    QList<COutputTerminal*>                      getListOfOutputTerminals(){  return m_listOfOutputTerminals;  }
    QList<CInputTerminal*>                       getListOfInputTerminals() {  return  m_listOfInputTerminals;  }

    QString  blueBox_keyWords  () const ;
    QString  blueBox_name      () const ;
    int      blueBox_xPos      () const ;
    int      blueBox_yPos      () const ;
    int      blueBox_width     () const ;
    int      blueBox_height    () const ;

    void setBlueBox_GUIType(const CBPStatic::EBPDelegateGUIType & newValue){
        m_blueBox_GUIType = newValue ;
    }

    CBPStatic::EBPDelegateGUIType blueBox_GUIType() const {
        return m_blueBox_GUIType;
    }

    int getBoxUniqueIDNumber() const {return m_boxUniqueIDNumber;}
    void setBoxUniqueIDNumber(const int & newValue );

    void  reCalcOutGoingLineFlowPos();
    void  reCalcIncomingLineFlowPos();

    virtual void serializeBoxInfoIntoJson( QJsonObject & jsonObj );
    virtual void deserializeBoxInfoFromJson( const QJsonObject & jsonObj );

public slots:
    void setBlueBox_keyWords  ( const QString & newValue ) ;
    void setBlueBox_name      ( const QString & newValue ) ;
    void setBlueBox_xPos      ( const int     & newValue ) ;
    void setBlueBox_yPos      ( const int     & newValue ) ;
    void setBlueBox_width     ( const int     & newValue ) ;
    void setBlueBox_height    ( const int     & newValue ) ;

protected:
    void  sendValueOnAllOutputTerminals( std::shared_ptr<CRawValueBase>  valueToBeSent );


protected:
    QString                          m_blueBox_name      = "" ;
    QString                          m_blueBox_keyWords  = "" ;
    int                              m_blueBox_xPos      = 0 ;
    int                              m_blueBox_yPos      = 0 ;
    int                              m_blueBox_width     = 0 ;
    int                              m_blueBox_height    = 0 ;
    QList<COutputTerminal*>          m_listOfOutputTerminals ;
    QList<CInputTerminal*>           m_listOfInputTerminals  ;
    QString                          m_blueBox_settingQMLPath = "";
    QColor                           m_blueBox_HeadColor = QColor(255, 0, 0, 127);
    QString                          m_blueBox_HeaderIcon = "" ;
    CBPStatic::EBPDelegateGUIType    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_InvalidGUIType ;
    CBPStatic::EBPBoxCategoryType    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_INVALIDTYPE ;
    int                              m_boxUniqueIDNumber = 0;


signals:
    void   blueBox_nameChanged       () ;
    void   blueBox_xPosChanged       () ;
    void   blueBox_yPosChanged       () ;
    void   blueBox_widthChanged      () ;
    void   blueBox_heightChanged     () ;
    void   blueBox_keyWordsChanged   () ;
    void   listOfOutputTerminalsChanged () ;
    void   listOfInputTerminalsChanged  () ;


};

#endif // COPERATIONBOX_H
