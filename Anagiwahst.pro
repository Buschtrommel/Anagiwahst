TEMPLATE = app

TARGET = anagiwahst

CONFIG += c++11

VERSION = 0.2.0

DEFINES += APP_VERSION=\"\\\"$${VERSION}\\\"\"

QT += qml quick widgets

SOURCES += \
    src/main.cpp \
    src/propertymodel.cpp \
    src/propertycreator.cpp \
    src/propertywriter.cpp

RESOURCES += \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

unix{
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }

    target.path = $$PREFIX/bin

    isEmpty(DESKTOPICONS_PATH) {
        DESKTOPICONS_PATH = $$PREFIX/share/icons/hicolor
    }

    desktopiconsvg.files = images/scalable/*.svg
    desktopiconsvg.path = $$DESKTOPICONS_PATH/scalable/apps
    INSTALLS += desktopiconsvg

    desktopicon128.files = images/128x128/*.png
    desktopicon128.path = $$DESKTOPICONS_PATH/128x128/apps
    INSTALLS += desktopicon128

    desktopicon64.files = images/64x64/*.png
    desktopicon64.path = $$DESKTOPICONS_PATH/64x64/apps
    INSTALLS += desktopicon64

    desktopicon48.files = images/48x48/*.png
    desktopicon48.path = $$DESKTOPICONS_PATH/48x48/apps
    INSTALLS += desktopicon48

    desktopicon32.files = images/32x32/*.png
    desktopicon32.path = $$DESKTOPICONS_PATH/32x32/apps
    INSTALLS += desktopicon32

    desktopicon22.files = images/22x22/*.png
    desktopicon22.path = $$DESKTOPICONS_PATH/22x22/apps
    INSTALLS += desktopicon22

    desktopicon16.files = images/16x16/*.png
    desktopicon16.path = $$DESKTOPICONS_PATH/16x16/apps
    INSTALLS += desktopicon16

    isEmpty(DESKTOPFILE_PATH) {
        desktopfile.path = $$PREFIX/share/applications
    }

    desktopfile.files = anagiwahst.desktop
    INSTALLS += desktopfile
}

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/propertymodel.h \
    src/propertycreator.h \
    src/property.h \
    src/propertywriter.h
