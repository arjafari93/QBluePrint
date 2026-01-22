#ifndef CIOTERMINAL_H
#define CIOTERMINAL_H

#include <QColor>
#include <QObject>
#include <QQmlListProperty>
#include <QVariant>
#include <memory>
#include <QtQml>

class COperationBox;
class CFlowConnectionLine;
class CRawValueBase;

class CIOTerminal : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Provided in C++ only; it cannot be created in QML")
    Q_PROPERTY(QString terminalName MEMBER m_terminalName CONSTANT)
    Q_PROPERTY(int terminalXPos MEMBER m_terminalXPos)
    Q_PROPERTY(int terminalYPos MEMBER m_terminalYPos)
    Q_PROPERTY(int terminalSize MEMBER m_terminalSize)
    Q_PROPERTY(bool isTerminalHovered READ isTerminalHovered WRITE setIsTerminalHovered NOTIFY isTerminalHoveredChanged)
    Q_PROPERTY(bool emissionEnabled READ emissionEnabled WRITE setEmissionEnabled NOTIFY emissionEnabledChanged)
    Q_PROPERTY(QColor terminalColor READ terminalColor WRITE setTerminalColor NOTIFY terminalColorChanged)
    Q_PROPERTY(QQmlListProperty<CFlowConnectionLine> listOfConnectedLines READ listOfConnectedLines NOTIFY listOfConnectedLinesChanged)

  public:
    Q_DISABLE_COPY_MOVE(CIOTerminal)
    explicit CIOTerminal(const int& terminalIndexInBox, COperationBox* parent);
    virtual ~CIOTerminal(){};

    QString terminalName() const { return m_terminalName; }
    void setTerminalName(const QString& newValue) { m_terminalName = newValue; }

    std::shared_ptr<CRawValueBase> terminalCurrentData() const { return m_terminalCurrentData; }
    void setTerminalCurrentData(const std::shared_ptr<CRawValueBase>& newValue);

    Q_INVOKABLE void changeTerminalCurrentData(const QVariant& newValue);      // called from QML
    Q_INVOKABLE void changeTerminalCurrentDataArray(const QVariant& newValue); // called from QML by array elmnt
    Q_INVOKABLE QVariant getTerminalCurrentData();                             // called from QML

    int terminalXPos() const { return m_terminalXPos; }
    int terminalYPos() const { return m_terminalYPos; }
    int terminalSize() const { return m_terminalSize; }

    QQmlListProperty<CFlowConnectionLine> listOfConnectedLines();
    QList<CFlowConnectionLine*> getListOfConnectedLines() const { return m_listOfConnectedLines; }

    void addFlowLineToConnectedList(CFlowConnectionLine* lineToBeAdded);
    void removeFlowLineFromConnectedList(CFlowConnectionLine* lineToBeRemoved);

    void setIsTerminalHovered(const bool& newValue);
    bool isTerminalHovered() const;

    COperationBox* containerBPBox() const { return mp_containerBPBox; }

    QColor terminalColor() const;
    void setTerminalColor(const QColor& newTerminalColor);

    bool emissionEnabled() const;
    void setEmissionEnabled(bool newEmissionEnabled);

  public slots:
    void highlightLineFlowAtIndex(const int& lineFlowIndex, const bool& highLightOrNot);
    void removeLineFlowAtIndex(const int& lineFlowIndex);
    void removeAllFlowLines();

  protected: // change this to protected and seet get and set functions for properties
    QList<CFlowConnectionLine*> m_listOfConnectedLines;
    std::shared_ptr<CRawValueBase> m_terminalCurrentData{nullptr};
    QString m_terminalName = "";
    int m_terminalXPos = 0;
    int m_terminalYPos = 0;
    int m_terminalSize = 0;
    bool m_isTerminalHovered = false;
    QColor m_terminalColor = QColor(200, 200, 200);
    COperationBox* mp_containerBPBox = nullptr; // the BPBox that this terminal belongs to it
    int m_terminalIndexInBox = 0;
    bool m_emissionEnabled = true;

  signals:
    void listOfConnectedLinesChanged();
    void isTerminalHoveredChanged();
    void nodeIsPassingNewValue();
    void terminalColorChanged();
    void emissionEnabledChanged();
};

#endif // CIOTERMINAL_H
