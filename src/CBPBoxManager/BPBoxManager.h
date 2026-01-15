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

#include <QDebug>
#include <QObject>

#include "BluePrintPage.h"

class CBPBoxManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<CBluePrintPage> listOfBluePrintPages READ listOfBluePrintPages NOTIFY listOfBluePrintPagesChanged)
    Q_PROPERTY(QQmlListProperty<COperationBox> bpBoxBrowserList READ bpBoxBrowserList NOTIFY bpBoxBrowserListChanged)
    Q_PROPERTY(QQmlListProperty<COperationBox> bpBoxBrowserListProxy READ bpBoxBrowserListProxy NOTIFY bpBoxBrowserListProxyChanged)
    Q_PROPERTY(bool isArchiveSearchActive READ isArchiveSearchActive WRITE setIsArchiveSearchActive NOTIFY isArchiveSearchActiveChanged)
    Q_PROPERTY(bool darkThemeEnabled READ darkThemeEnabled WRITE setDarkThemeEnabled NOTIFY darkThemeEnabledChanged)
    Q_PROPERTY(bool terminalGlowEnable READ terminalGlowEnable WRITE setTerminalGlowEnable NOTIFY terminalGlowEnableChanged)
    Q_PROPERTY(int activePageIndex READ activePageIndex WRITE setActivePageIndex NOTIFY activePageIndexChanged)

  private:
    explicit CBPBoxManager(QObject* parent = nullptr);

  public:
    ~CBPBoxManager();
    static CBPBoxManager* getInstance();
    QQmlListProperty<CBluePrintPage> listOfBluePrintPages();
    QQmlListProperty<COperationBox> bpBoxBrowserList();
    QQmlListProperty<COperationBox> bpBoxBrowserListProxy();

    Q_INVOKABLE void boxListSearchBoxTextChanged(const QString& newSearch);
    Q_INVOKABLE void addNewBluePrintPage(); // called by + button in GUI
    Q_INVOKABLE void removeBluePrintPage(const int& pageIndex);

    bool darkThemeEnabled() const;
    void setDarkThemeEnabled(const bool& newValue);

    bool isArchiveSearchActive() const;
    void setIsArchiveSearchActive(const bool& newValue);

    int activePageIndex() const;
    void setActivePageIndex(const int& newValue);

    bool terminalGlowEnable() const;
    void setTerminalGlowEnable(bool newTerminalGlowEnable);

  private: // variables
    QList<CBluePrintPage*> m_listOfBluePrintPages;
    QList<COperationBox*> m_bpBoxBrowserList;      // list of items in the left menue
    QList<COperationBox*> m_bpBoxBrowserListProxy; // list of items in the left menu in search mode
    bool m_isArchiveSearchActive = false;
    bool m_darkThemeEnabled = true;
    int m_activePageIndex = 0;
    bool m_terminalGlowEnable = true;

  signals:

    void listOfBluePrintPagesChanged();
    void bpBoxBrowserListChanged();
    void bpBoxBrowserListProxyChanged();
    void darkThemeEnabledChanged();
    void showStatusBarMessage(const QString& msgText, const int& msgDuration, const QColor& msgColor = QColor(255, 255, 255));
    void isArchiveSearchActiveChanged();
    void activePageIndexChanged();
    void terminalGlowEnableChanged();
};

#endif // CBPBOXMANAGER_H
