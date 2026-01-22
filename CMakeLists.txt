cmake_minimum_required(VERSION 3.21)

project(QBluePrint
    VERSION 0.9.3
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 Network Charts)

qt_standard_project_setup()

add_subdirectory(src/dataTypes)
add_subdirectory(src/core)

qt_add_executable(QBluePrint
    main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/CommonHeader.h
    qml.qrc
)

target_compile_definitions(QBluePrint PRIVATE
    APP_VERSION="0.9.4"
)

qt_generate_foreign_qml_types(QBluePrintCore QBluePrint)

target_link_libraries(QBluePrint PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Network
    Qt6::Charts
    QBluePrintCore
)

include(cmake/qmlModule.cmake)

target_include_directories(QBluePrint
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/src/CBPBoxFactory
    ${CMAKE_CURRENT_LIST_DIR}/src/CBPBoxManager
    ${CMAKE_CURRENT_LIST_DIR}/src/COperationBox
    ${CMAKE_CURRENT_LIST_DIR}/src/COperationBox/Miscellaneous
    ${CMAKE_CURRENT_LIST_DIR}/src/COperationBox/dataSinkBoxes
    ${CMAKE_CURRENT_LIST_DIR}/src/COperationBox/dataSourceBoxes
    ${CMAKE_CURRENT_LIST_DIR}/src/COperationBox/LoopsArrays
    ${CMAKE_CURRENT_LIST_DIR}/src/COperationBox/MathOperationBoxes
    ${CMAKE_CURRENT_LIST_DIR}/src/COperationBox/LogicalOperationBoxes
    ${CMAKE_CURRENT_LIST_DIR}/src/COperationBox/BitwiseOperationBoxes
    ${CMAKE_CURRENT_LIST_DIR}/src/COperationBox/DataComparisonOperations
)

if (WIN32)
    target_sources(QBluePrint PRIVATE app.rc)
endif()

# Stack size (in QBP, loops are recursions, so we need a big stack)
if (WIN32)
    if (MSVC)
        target_link_options(QBluePrint PRIVATE /STACK:250000000)
    else()
        target_link_options(QBluePrint PRIVATE -Wl,--stack,250000000)
    endif()
endif()

qt_finalize_executable(QBluePrint)

install(TARGETS QBluePrint
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set(QML_IMPORT_PATH
    ${CMAKE_BINARY_DIR}/qml
    CACHE STRING "" FORCE
)
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)
