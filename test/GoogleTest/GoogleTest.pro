TEMPLATE = lib
CONFIG += static exceptions
CONFIG -= debug_and_release

TARGET = GoogleTest
CONFIG += c++17

INCLUDEPATH += \
    googletest/googletest/include \
    googletest/googlemock/include \
    googletest/googletest \
    googletest/googlemock

SOURCES = \
    googletest/googletest/src/gtest-all.cc \
    googletest/googlemock/src/gmock-all.cc
