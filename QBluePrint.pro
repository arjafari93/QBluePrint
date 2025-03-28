QT += core quick  qml gui   quickcontrols2 network charts
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32:RC_ICONS += AppLogo.ico

VERSION = 0.9
DEFINES += APP_VERSION=\\\"$$VERSION\\\"


SOURCES += \
        main.cpp \
        src/CBPBoxFactory/BPBoxFactory.cpp \
        src/CBPStatic/BPStatic.cpp \
        src/CFlowConnectionLine/FlowConnectionLine.cpp \
        src/CIOTerminal/CInputTerminal/InputTerminal.cpp \
        src/CIOTerminal/COutputTerminal/OutputTerminal.cpp \
        src/CIOTerminal/IOTerminal.cpp \
        src/CBPBoxManager/BPBoxManager.cpp \
        src/COperationBox/BitwiseOperationBoxes/BitWiseAND.cpp \
        src/COperationBox/BitwiseOperationBoxes/BitWiseComplement.cpp \
        src/COperationBox/BitwiseOperationBoxes/BitWiseLeftShift.cpp \
        src/COperationBox/BitwiseOperationBoxes/BitWiseOR.cpp \
        src/COperationBox/BitwiseOperationBoxes/BitWiseRightShift.cpp \
        src/COperationBox/BitwiseOperationBoxes/BitWiseXOR.cpp \
        src/COperationBox/Miscellaneous/ConditionalBranch.cpp \
        src/COperationBox/Miscellaneous/DataCounter.cpp \
        src/COperationBox/DataComparisonOperations/DataComparisonEqual.cpp \
        src/COperationBox/DataComparisonOperations/DataComparisonGreater.cpp \
        src/COperationBox/DataComparisonOperations/DataComparisonLess.cpp \
        src/COperationBox/Miscellaneous/StopWatch.cpp \
        src/COperationBox/dataSinkBoxes/LiveDataXYModel.cpp \
        src/COperationBox/dataSinkBoxes/LineSeriesChartBox.cpp \
        src/COperationBox/LogicalOperationBoxes/LogicalAND.cpp \
        src/COperationBox/LogicalOperationBoxes/LogicalNOT.cpp \
        src/COperationBox/LogicalOperationBoxes/LogicalOR.cpp \
        src/COperationBox/MathOperationBoxes/MathAbsolute.cpp \
        src/COperationBox/MathOperationBoxes/MathAddition.cpp \
        src/COperationBox/MathOperationBoxes/MathDivision.cpp \
        src/COperationBox/MathOperationBoxes/MathModulus.cpp \
        src/COperationBox/MathOperationBoxes/MathMultiplication.cpp \
        src/COperationBox/MathOperationBoxes/MathPower.cpp \
        src/COperationBox/MathOperationBoxes/MathSubtraction.cpp \
        src/COperationBox/dataSinkBoxes/CSocketClientSink.cpp \
        src/COperationBox/dataSinkBoxes/StringOutputSink.cpp \
        src/COperationBox/dataSourceBoxes/ButtonSource.cpp \
        src/COperationBox/dataSourceBoxes/TCPSocketServerSource.cpp \
        src/COperationBox/dataSourceBoxes/TimerSendValSrc.cpp \
        src/COperationBox/dataSourceBoxes/UDPSocketServerSource.cpp \
        src/COperationBox/Miscellaneous/UniversalTypeConvertor.cpp \
        src/COperationBox/OperationBox.cpp \
        src/CRawValueBase/RawValueBase.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/CBPBoxFactory/BPBoxFactory.h \
    src/CBPStatic/BPStatic.h \
    src/CFlowConnectionLine/FlowConnectionLine.h \
    src/CIOTerminal/CInputTerminal/InputTerminal.h \
    src/CIOTerminal/COutputTerminal/OutputTerminal.h \
    src/CIOTerminal/IOTerminal.h \
    src/CBPBoxManager/BPBoxManager.h \
    src/COperationBox/BitwiseOperationBoxes/BitWiseAND.h \
    src/COperationBox/BitwiseOperationBoxes/BitWiseComplement.h \
    src/COperationBox/BitwiseOperationBoxes/BitWiseLeftShift.h \
    src/COperationBox/BitwiseOperationBoxes/BitWiseOR.h \
    src/COperationBox/BitwiseOperationBoxes/BitWiseRightShift.h \
    src/COperationBox/BitwiseOperationBoxes/BitWiseXOR.h \
    src/COperationBox/Miscellaneous/ConditionalBranch.h \
    src/COperationBox/Miscellaneous/DataCounter.h \
    src/COperationBox/DataComparisonOperations/DataComparisonEqual.h \
    src/COperationBox/DataComparisonOperations/DataComparisonGreater.h \
    src/COperationBox/DataComparisonOperations/DataComparisonLess.h \
    src/COperationBox/Miscellaneous/StopWatch.h \
    src/COperationBox/dataSinkBoxes/LiveDataXYModel.h \
    src/COperationBox/dataSinkBoxes/LineSeriesChartBox.h \
    src/COperationBox/LogicalOperationBoxes/LogicalAND.h \
    src/COperationBox/LogicalOperationBoxes/LogicalNOT.h \
    src/COperationBox/LogicalOperationBoxes/LogicalOR.h \
    src/COperationBox/MathOperationBoxes/MathAbsolute.h \
    src/COperationBox/MathOperationBoxes/MathAddition.h \
    src/COperationBox/MathOperationBoxes/MathDivision.h \
    src/COperationBox/MathOperationBoxes/MathModulus.h \
    src/COperationBox/MathOperationBoxes/MathMultiplication.h \
    src/COperationBox/MathOperationBoxes/MathPower.h \
    src/COperationBox/MathOperationBoxes/MathSubtraction.h \
    src/COperationBox/dataSinkBoxes/CSocketClientSink.h \
    src/COperationBox/dataSinkBoxes/StringOutputSink.h \
    src/COperationBox/dataSourceBoxes/ButtonSource.h \
    src/COperationBox/dataSourceBoxes/TCPSocketServerSource.h \
    src/COperationBox/dataSourceBoxes/TimerSendValSrc.h \
    src/COperationBox/dataSourceBoxes/UDPSocketServerSource.h \
    src/COperationBox/Miscellaneous/UniversalTypeConvertor.h \
    src/COperationBox/OperationBox.h \
    src/CommonHeader.h \
    src/CRawValueBase/RawValueBase.h
