cmake_minimum_required(VERSION 3.21)

qt_add_library(QBPControls STATIC)


target_link_libraries(QBPControls
  PUBLIC Qt6::Core Qt6::Qml Qt6::Quick Qt6::QuickControls2
)

# Build this library as a QML module
qt_add_qml_module(QBPControls
  URI org.QBluePrint.Controls
  VERSION 1.0
  NO_PLUGIN
  RESOURCE_PREFIX /qt/qml
  OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/libs/QBluePrint"

  QML_FILES
    SpinBox.qml
)

