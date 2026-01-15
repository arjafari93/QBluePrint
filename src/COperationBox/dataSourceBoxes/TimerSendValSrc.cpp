#include "TimerSendValSrc.h"

#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "src/CRawValueBase/RawValueBase.h"
#include <QJsonObject>
#include <memory>

CTimerSendValSrc::CTimerSendValSrc(int newBlueBox_xPos, int newBlueBox_yPos, QObject* parent)
    : COperationBox{m_uniqueBoxName, newBlueBox_xPos, newBlueBox_yPos, blueBoxWidth + 130, blueBoxHeight + 200, parent}
{
    m_valueToBeSentInt = 15;
    m_valueToBeSentDouble = 15;
    m_valueToBeSentString = "test string";
    m_valueToBeSentBool = false;
    m_valueToBeSentlist.push_back(std::make_shared<CValue_int>(12));
    m_valueToBeSentlist.push_back(std::make_shared<CValue_double>(12.5));
    m_valueToBeSentlist.push_back(std::make_shared<CValue_string>("test string in array"));
    m_valueToBeSentlist.push_back(std::make_shared<CValue_bool>(false));
    m_blueBox_GUIType = CBPStatic::EBPDelegateGUIType::E_InputSpinBoxWithTimer;
    m_blueBox_HeaderIcon = "qrc:/Images/clock.png";
    m_blueBox_HeadColor = QColor(0, 169, 255);

    auto outPutNodeInt = new COutputTerminal(0, this);
    outPutNodeInt->setTerminalName("Int");
    m_listOfOutputTerminals.push_back(outPutNodeInt);

    auto outPutNodeDouble = new COutputTerminal(1, this);
    outPutNodeDouble->setTerminalName("Double");
    m_listOfOutputTerminals.push_back(outPutNodeDouble);

    auto outPutNodeString = new COutputTerminal(2, this);
    outPutNodeString->setTerminalName("String");
    m_listOfOutputTerminals.push_back(outPutNodeString);

    auto outPutNodeBool = new COutputTerminal(3, this);
    outPutNodeBool->setTerminalName("Bool");
    m_listOfOutputTerminals.push_back(outPutNodeBool);

    auto outPutNodeList = new COutputTerminal(4, this);
    outPutNodeList->setTerminalName("Array");
    m_listOfOutputTerminals.push_back(outPutNodeList);

    mp_sendValueTimer = new QTimer(this);
    connect(mp_sendValueTimer, SIGNAL(timeout()), this, SLOT(sendValueTimerTimeOut()));
    mp_sendValueTimer->setInterval(m_sendValueInterval);
    mp_sendValueTimer->start();

    m_blueBox_keyWords = "timer, timeout, send , value, source, auto , generate, generation ";
    m_blueBox_Catgr = CBPStatic::EBPBoxCategoryType::E_BP_InputSource;
}

void CTimerSendValSrc::evaluateOperation() {}

void CTimerSendValSrc::serializeBoxInfoIntoJson(QJsonObject& jsonObj)
{
    COperationBox::serializeBoxInfoIntoJson(jsonObj);
    jsonObj["interval"] = QString::number(m_sendValueInterval);
    jsonObj["intVal"] = QString::number(m_valueToBeSentInt);
    jsonObj["doubleVal"] = QString::number(m_valueToBeSentDouble);
    jsonObj["boolVal"] = QString::number(m_valueToBeSentBool);
    jsonObj["stringVal"] = m_valueToBeSentString;
}

void CTimerSendValSrc::deserializeBoxInfoFromJson(const QJsonObject& jsonObj)
{
    COperationBox::deserializeBoxInfoFromJson(jsonObj);
    m_sendValueInterval = jsonObj["interval"].toString().toInt();
    m_valueToBeSentInt = jsonObj["intVal"].toString().toInt();
    m_valueToBeSentDouble = jsonObj["doubleVal"].toString().toDouble();
    m_valueToBeSentBool = (bool)jsonObj["boolVal"].toString().toInt();
    m_valueToBeSentString = jsonObj["stringVal"].toString();
    mp_sendValueTimer->setInterval(m_sendValueInterval);
}

void CTimerSendValSrc::setSendValueInterval(const int& newValue)
{
    if (m_sendValueInterval == newValue)
        return;
    m_sendValueInterval = newValue;
    mp_sendValueTimer->setInterval(newValue);
    emit sendValueIntervalChanged();
}

void CTimerSendValSrc::sendValueTimerTimeOut()
{
    m_listOfOutputTerminals.at(0)->sendValueToFlowLine(std::make_shared<CValue_int>(m_valueToBeSentInt));
    m_listOfOutputTerminals.at(1)->sendValueToFlowLine(std::make_shared<CValue_double>(m_valueToBeSentDouble));
    m_listOfOutputTerminals.at(2)->sendValueToFlowLine(std::make_shared<CValue_string>(m_valueToBeSentString));
    m_listOfOutputTerminals.at(3)->sendValueToFlowLine(std::make_shared<CValue_bool>(m_valueToBeSentBool));
    m_listOfOutputTerminals.at(4)->sendValueToFlowLine(std::make_shared<CValue_array>(m_valueToBeSentlist));
}

QVariant CTimerSendValSrc::getArrayValueData() const
{
    CValue_array tempArr(m_valueToBeSentlist);
    return tempArr.convertToVariant();
}

void CTimerSendValSrc::changeArrayValueData(const QVariant& newValue)
{
    using recFuncType = std::function<void(QList<std::shared_ptr<CRawValueBase>>&, const QVariant&)>;
    recFuncType recursiveInsertor;
    recursiveInsertor = [&](QList<std::shared_ptr<CRawValueBase>>& listOfRawVals, const QVariant& recVal) {
        switch (recVal.type())
        {
        case QVariant::Int:
            listOfRawVals.push_back(std::make_shared<CValue_int>(recVal.toInt()));
            break;
        case QVariant::Double:
            listOfRawVals.push_back(std::make_shared<CValue_double>(recVal.toDouble()));
            break;
        case QVariant::Bool:
            listOfRawVals.push_back(std::make_shared<CValue_bool>(recVal.toBool()));
            break;
        case QVariant::String:
            listOfRawVals.push_back(std::make_shared<CValue_string>(recVal.toString()));
            break;
        default:
            if (recVal.canConvert<QVariantList>())
            {
                auto listOfInnerVals = recVal.toList();
                QList<std::shared_ptr<CRawValueBase>> innerListOfRawVals;
                for (const auto& currentInnerVal : listOfInnerVals)
                {
                    recursiveInsertor(innerListOfRawVals, currentInnerVal);
                }
                listOfRawVals.push_back(std::make_shared<CValue_array>(std::move(innerListOfRawVals)));
            }
            else
            {
                DEBUG_MSG_PRINT << " type doesn't exist " << recVal.type();
            }
            break;
        }
    };

    // newValue is in fact an array
    ASSERTWITHINFO(newValue.canConvert<QVariantList>());
    auto listOfVals = newValue.toList();
    QList<std::shared_ptr<CRawValueBase>> listOfRawVals;
    for (auto const& currentVal : listOfVals)
    {
        recursiveInsertor(listOfRawVals, currentVal);
    }
    m_valueToBeSentlist = listOfRawVals;
}
