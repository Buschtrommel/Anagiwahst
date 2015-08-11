# CMakeLists for anagiwahst
project(anagiwahst)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)


set(ANAGIWAHST_VERSION_MAJOR "0")
set(ANAGIWAHST_VERSION_MINOR "2")
set(ANAGIWAHST_VERSION_PATCH "0")
set(ANAGIWAHST_VERSION "${ANAGIWAHST_VERSION_MAJOR}.${ANAGIWAHST_VERSION_MINOR}.${ANAGIWAHST_VERSION_PATCH}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(PkgConfig REQUIRED)
find_package(Qt5 5.2.0 COMPONENTS
    Core
    Qml
    Quick
    Widgets
    REQUIRED
)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "Anagiwahst default install prefix" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)


set (PREFIXDIR "${CMAKE_INSTALL_PREFIX}")
set (BINDIR "${CMAKE_INSTALL_PREFIX}/bin")
set (DATADIR "${CMAKE_INSTALL_PREFIX}/share/anagiwahst")
set (L10N_DIR "${DATADIR}/l10n")
set (QML_DIR "${DATADIR}/qml")
set (ICONS_DIR "${CMAKE_INSTALL_PREFIX}/share/icons")
set (VERSION "${ANAGIWAHST_VERSION}")

add_definitions("-DAPP_VERSION=\"${ANAGIWAHST_VERSION}\"")
add_definitions("-DL10N_DIR=\"${L10N_DIR}\"")

set (QT_DEBUG "-DQT_NO_DEBUG")
option (DEBUG_ENABLED "Enabled debug output" OFF)
if (DEBUG_ENABLED)
    set (QT_DEBUG "-DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -DQT_DEBUG")
endif (DEBUG_ENABLED)

add_definitions(${QT_DEBUG})

add_subdirectory(src)
add_subdirectory(images)
add_subdirectory(l10n)
