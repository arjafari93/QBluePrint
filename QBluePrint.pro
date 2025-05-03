QT += core quick  qml gui   quickcontrols2 network charts
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32:RC_ICONS += AppLogo.ico
# Used for showing in About dialog, etc.
APP_VERSION_STRING = "0.9.3-alpha"
DEFINES += APP_VERSION=\\\"$$APP_VERSION_STRING\\\"
win32 {
    contains(QMAKE_CXX, "cl") {
        # MSVC
        QMAKE_LFLAGS += /STACK:250000000
    } else {
        # MinGW/GCC
        QMAKE_LFLAGS += -Wl,--stack,250000000
    }
}


SOURCES += \
        main.cpp

include(commonFiles.pri)


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
