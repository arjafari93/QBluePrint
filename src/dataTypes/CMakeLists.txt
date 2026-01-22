
qt_add_library(QBluePrintDataTypes
    STATIC
    ${CMAKE_CURRENT_LIST_DIR}/RawValueBase.cpp
    ${CMAKE_CURRENT_LIST_DIR}/RawValueBase.h
    ${CMAKE_CURRENT_LIST_DIR}/Value_array.cpp
)

qt_extract_metatypes(QBluePrintDataTypes)

target_link_libraries(QBluePrintDataTypes
    PUBLIC
    Qt6::Core
)

target_include_directories(QBluePrintDataTypes
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../../
)
