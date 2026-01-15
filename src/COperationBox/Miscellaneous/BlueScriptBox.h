#ifndef CBLUESCRIPTBOX_H
#define CBLUESCRIPTBOX_H

#include "../OperationBox.h"
#include <QJSValue>
#include <QObject>

class QJSEngine;

class CBlueScriptBox : public COperationBox
{
    Q_OBJECT
    Q_PROPERTY(QString scriptFunctionBody READ scriptFunctionBody WRITE setScriptFunctionBody NOTIFY scriptFunctionBodyChanged)
    Q_PROPERTY(int numInputs READ numInputs WRITE setNumInputs NOTIFY numInputsChanged)
    Q_PROPERTY(int numOutputs READ numOutputs WRITE setNumOutputs NOTIFY numOutputsChanged)

    friend class CBlueScriptBoxFactory;
    Q_DISABLE_COPY_MOVE(CBlueScriptBox)
    explicit CBlueScriptBox(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent = nullptr);

  public:
    ~CBlueScriptBox();
    virtual void evaluateOperation() override;
    GETUNIQUENAMEFUNC;

    const QString& scriptFunctionBody() const;
    void setScriptFunctionBody(const QString& newScriptFunctionBody);

    int numInputs() const;
    void setNumInputs(int newNumInputs);

    int numOutputs() const;
    void setNumOutputs(int newNumOutputs);

    virtual void serializeBoxInfoIntoJson(QJsonObject& jsonObj) override;
    virtual void deserializeBoxInfoFromJson(const QJsonObject& jsonObj) override;

  private:
    inline const static QString m_uniqueBoxName = "Script Box";
    QString m_scriptFunctionBody = R"(function functionBlock(in0) {
 return [in0];
}
    )";
    int m_numInputs = 1;
    int m_numOutputs = 1;
    QJSEngine* mp_jsEngine{nullptr};
    QJSValue m_functionBlock;

  signals:
    void scriptFunctionBodyChanged();
    void numInputsChanged();
    void numOutputsChanged();
};

#endif // CBLUESCRIPTBOX_H
