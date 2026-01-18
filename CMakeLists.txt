cmake_minimum_required(VERSION 3.21)

project(QBluePrint
    VERSION 0.9.3
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 Network Charts)

qt_standard_project_setup()

add_subdirectory(libs/QBPControls)

include(cmake/commonFiles.cmake)
set(CMAKE_AUTORCC ON)
qt_add_executable(QBluePrint
    main.cpp
    ${QBLUEPRINT_SOURCES}
    ${QBLUEPRINT_HEADERS}
    qml.qrc
)


target_link_libraries(QBluePrint PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Network
    Qt6::Charts
    QBPControls
)

target_include_directories(QBluePrint
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_compile_definitions(QBluePrint PRIVATE
    APP_VERSION="0.9.4"
)

target_include_directories(QBluePrint PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if (WIN32)
    target_sources(QBluePrint PRIVATE cmake/windows/app.rc)
endif()

# Stack size (in QBP, loops are recursions, so we need a big stack)
if (WIN32)
    if (MSVC)
        target_link_options(QBluePrint PRIVATE /STACK:250000000)
    else()
        target_link_options(QBluePrint PRIVATE -Wl,--stack,250000000)
    endif()
endif()



