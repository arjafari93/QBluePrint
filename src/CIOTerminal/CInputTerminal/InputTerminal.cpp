#include "InputTerminal.h"

#include "src/COperationBox/OperationBox.h"

CInputTerminal::CInputTerminal(const int& terminalIndexInBox, COperationBox* parent) : CIOTerminal{terminalIndexInBox, parent} {}

void CInputTerminal::receivedValueFromFlowLine(const std::shared_ptr<CRawValueBase>& newValue)
{
    try
    {
        emit nodeIsPassingNewValue();
        setTerminalCurrentData(newValue);
        if (m_emissionEnabled)
            mp_containerBPBox->evaluateOperation();
    }
    catch (const std::exception& e)
    {
        DEBUG_MSG_PRINT << " exception: " << e.what();
    }
    catch (...)
    {
        DEBUG_MSG_PRINT << " exception happened";
    }
}
