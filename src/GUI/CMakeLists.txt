
#qt_add_library(QBluePrintGUI STATIC)

qt_add_qml_module(QBluePrintGUI
    URI "org.QBluePrint.GUI"
    VERSION 1.0
    OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/org/QBluePrint/GUI

    QML_FILES
    Main.qml
    QML/BluePrintBoxes/BoxesFullScreenRepeater.qml
    QML/BluePrintBoxes/SingleBoxInstance/SingleBoxInstance.qml
    QML/BluePrindLineFlow/LineFlowFullScreenRepeater.qml
    QML/BluePrindLineFlow/SingleLineFlowInstance/SingleLineFlowInstance.qml
    QML/BottomStatusBar/BottomStatusBar.qml
    QML/BottomStatusBar/StatusBarMessageDelegate.qml
    QML/TopMenuBar/TopMenuBar.qml
    QML/BluePrintBoxes/SingleTerminalInstance/TerminalMenus.qml
    QML/BluePrintBoxes/SingleTerminalInstance/SingleTerminalInstance.qml
    QML/BluePrintBoxes/SpinBoxTimerInputSourceBox/SpinBoxTimerInputSourceBox.qml
    QML/BluePrintBoxes/SinkOutputString/SinkOutputString.qml
    QML/BluePrintBoxes/SingleBoxInstance/RemoveBoxConfirm.qml
    QML/LeftDrawerListOfBoxes/LeftDrawerListOfBoxes.qml
    QML/BluePrintBoxes/OperatorWithBigText/OperatorWithBigText.qml
    QML/BluePrintBoxes/BigPictureOperator/BigPictureOperator.qml
    QML/TopMenuBar/WindowControlButtons.qml
    QML/Style/ShadowedRectangle.qml
    QML/BottomStatusBar/ResizeHandle.qml
    QML/BoxRemoverArea.qml
    QML/TopMenuBar/ApplicationIconImage.qml
    QML/SoftwareInfo/SoftwareInfoPopup.qml
    QML/BluePrintBoxes/NetworkBoxes/TCPServerInputBox.qml
    QML/BluePrintBoxes/TypeConvertorOperatorBox/TypeConvertorOperatorBox.qml
    QML/BluePrintBoxes/NetworkBoxes/TCPClientOutputBox.qml
    QML/BluePrintBoxes/SingleTerminalInstance/ChangeTerminalDataPopUp.qml
    QML/BluePrintBoxes/ChartBoxes/LineSeriesChartBox.qml
    QML/BluePrintBoxes/ChartBoxes/ChartBoxSettings.qml
    QML/BluePrintBoxes/ButtonSourceBox/ButtonSourceBox.qml
    QML/BluePrintBoxes/StopWatchBox/StopWatchBox.qml
    QML/BluePrintBoxes/ScriptRunnerBox/ScriptRunnerBox.qml
    QML/BluePrintBoxes/ScriptRunnerBox/ScriptRunnerSettingsPopup.qml
    QML/BluePrintBoxes/NetworkBoxes/HTTPHeaderSettingsPopup.qml
    QML/BluePrintPageDelegate.qml
    QML/BluePrintPagesSelector/BluePrintPagesSelector.qml
    QML/BluePrintPagesSelector/PageSelectorDelegate.qml
    QML/BluePrintBoxes/SingleTerminalInstance/ArrayValueModifierPopUp.qml
    QML/BluePrintBoxes/SingleTerminalInstance/AddNewArrayElementPopup.qml
    QML/BluePrintPagesSelector/ExitConfirmationPopup.qml

    RESOURCES

    shaders/terminal_colorize.frag
    shaders/terminal_colorize.frag.qsb
    shaders/wave.frag
    shaders/wave.frag.qsb
)

target_link_libraries(QBluePrintGUI
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Network
    Qt6::Charts
)

install(TARGETS QBluePrintGUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
