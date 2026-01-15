#ifndef CFLOWCONNECTIONLINE_H
#define CFLOWCONNECTIONLINE_H

/*
 * Copyright (c) 2025 Alireza Jafari (https://github.com/arjafari93)
 *
 * This software is provided "as is", without warranty of any kind.
 * You may use, modify, and distribute this software, but you MUST keep
 * this copyright notice and credit the original author.
 *
 * Licensed under the BSD 3-Clause License
 */

#include "src/CommonHeader.h"
#include <QColor>
#include <QObject>

class CInputTerminal;
class COutputTerminal;
class CRawValueBase;

class CFlowConnectionLine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int flowLine_startX READ flowLine_startX WRITE setFlowLine_startX NOTIFY flowLine_startXChanged)
    Q_PROPERTY(int flowLine_startY READ flowLine_startY WRITE setFlowLine_startY NOTIFY flowLine_startYChanged)
    Q_PROPERTY(int flowLine_endX READ flowLine_endX WRITE setFlowLine_endX NOTIFY flowLine_endXChanged)
    Q_PROPERTY(int flowLine_endY READ flowLine_endY WRITE setFlowLine_endY NOTIFY flowLine_endYChanged)
    Q_PROPERTY(QColor flowLine_color READ flowLine_color WRITE setFlowLine_color NOTIFY flowLine_colorChanged)

    Q_PROPERTY(int flowLine_strokeWidth MEMBER m_flowLine_strokeWidth NOTIFY flowLine_strokeWidthChanged)

  public:
    Q_DISABLE_COPY_MOVE(CFlowConnectionLine)
    explicit CFlowConnectionLine(QObject* parent = nullptr);
    virtual ~CFlowConnectionLine(){};
    Q_DECL_DEPRECATED explicit CFlowConnectionLine(int newFlowLine_startX, int newflowLine_startY, int newFlowLine_endX, int newFlowLine_endY, QObject* parent = nullptr);

    explicit CFlowConnectionLine(COutputTerminal* pStartTerminal, QObject* parent = nullptr);

    int flowLine_startX() const;
    int flowLine_startY() const;
    int flowLine_endX() const;
    int flowLine_endY() const;

    COutputTerminal* startPoint() const { return mp_startPoint; }
    CInputTerminal* endPoint() const { return mp_endPoint; }

    void setStartPoint(COutputTerminal* newValue);
    void setEndPoint(CInputTerminal* newValue) { mp_endPoint = newValue; }

    void setFlowLine_strokeWidth(const int& newValue);
    int flowLine_strokeWidth() const { return m_flowLine_strokeWidth; }

    void passValueToEndPoint(const std::shared_ptr<CRawValueBase>& valueToBePassed);

    static void bindFlowLineToInputTerminal(CFlowConnectionLine* pFlowLine, CInputTerminal* pInputTerminal);
    static void bindFlowLineToOutputTerminal(CFlowConnectionLine* pFlowLine, COutputTerminal* pOutputTerminal);

    const QColor& flowLine_color() const;
    void setFlowLine_color(const QColor& newValue);

    virtual void serializeFlowLineInfoIntoJson(QJsonObject& jsonObj);

  public slots:
    void setFlowLine_startX(const int& newValue);
    void setFlowLine_startY(const int& newValue);
    void setFlowLine_endX(const int& newValue);
    void setFlowLine_endY(const int& newValue);

  private:
    int m_flowLine_startX = 0; // absolute postion
    int m_flowLine_startY = 0; // absolute postion
    int m_flowLine_endX = 0;   // relative to startX
    int m_flowLine_endY = 0;   // relative to startY

    COutputTerminal* mp_startPoint = nullptr;
    CInputTerminal* mp_endPoint = nullptr;
    QColor m_flowLine_color = QColor(0, 255, 255);
    int m_flowLine_strokeWidth = 1;

  signals:
    void flowLine_startXChanged();
    void flowLine_startYChanged();
    void flowLine_endXChanged();
    void flowLine_endYChanged();
    void flowLine_colorChanged();
    void flowLine_strokeWidthChanged();
};

#endif // CFLOWCONNECTIONLINE_H
