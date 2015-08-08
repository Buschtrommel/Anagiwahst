TEMPLATE = app

TARGET = anagiwahst

CONFIG += c++11

VERSION = 0.1.0

DEFINES += APP_VERSION=\"\\\"$${VERSION}\\\"\"

QT += qml quick widgets

SOURCES += \
    src/main.cpp \
    src/propertymodel.cpp \
    src/propertycreator.cpp

RESOURCES += \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

unix{
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }

    target.path = $$PREFIX/bin
}

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/propertymodel.h \
    src/propertycreator.h \
    src/property.h
