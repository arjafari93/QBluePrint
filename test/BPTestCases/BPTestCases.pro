TEMPLATE = app

QT += testlib #Include QtTest to use SignalSpy, QTest::mouseClick, etc
QT += core quick  qml gui   quickcontrols2 network charts
CONFIG += c++17

CONFIG += testcase #Creates 'check' target in Makefile.
CONFIG -= debug_and_release
CONFIG += console
CONFIG += c++17

TARGET = Tests

INCLUDEPATH += ../../
include(../../commonFiles.pri)
#LIBS += -L../ApplicationLib -lApplicationLib

include(../GoogleTest/GoogleTest.pri)



SOURCES += main.cpp \
    BPTest.cpp
