
qt_add_library(QBluePrintCore
    STATIC
    ${CMAKE_CURRENT_LIST_DIR}/BPStatic.cpp
    ${CMAKE_CURRENT_LIST_DIR}/BPStatic.h
    ${CMAKE_CURRENT_LIST_DIR}/FlowConnectionLine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FlowConnectionLine.h
    ${CMAKE_CURRENT_LIST_DIR}/IOTerminal.cpp
    ${CMAKE_CURRENT_LIST_DIR}/IOTerminal.h
    ${CMAKE_CURRENT_LIST_DIR}/InputTerminal.cpp
    ${CMAKE_CURRENT_LIST_DIR}/InputTerminal.h
    ${CMAKE_CURRENT_LIST_DIR}/OutputTerminal.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OutputTerminal.h
    ${CMAKE_CURRENT_LIST_DIR}/BluePrintPage.h
    ${CMAKE_CURRENT_LIST_DIR}/BluePrintPage.cpp
)

qt_extract_metatypes(QBluePrintCore)

target_link_libraries(QBluePrintCore
    PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    QBluePrintDataTypes
)

target_include_directories(QBluePrintCore
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
)
