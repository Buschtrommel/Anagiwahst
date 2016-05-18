# CMakeLists for anagiwahst
project(anagiwahst)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)


set(ANAGIWAHST_VERSION_MAJOR "0")
set(ANAGIWAHST_VERSION_MINOR "4")
set(ANAGIWAHST_VERSION_PATCH "4")
set(ANAGIWAHST_VERSION "${ANAGIWAHST_VERSION_MAJOR}.${ANAGIWAHST_VERSION_MINOR}.${ANAGIWAHST_VERSION_PATCH}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(PkgConfig REQUIRED)
find_package(Qt5 5.2.0 COMPONENTS
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
set (DATADIR "${CMAKE_INSTALL_PREFIX}/share")
set (ICONS_DIR "${DATADIR}/icons")
set (DESKTOPFILE_DIR "${DATADIR}/applications")
set (APP_DIR "${DATADIR}/anagiwahst")
set (L10N_DIR "${APP_DIR}/l10n")
set (VERSION "${ANAGIWAHST_VERSION}")

add_definitions("-DAPP_VERSION=\"${ANAGIWAHST_VERSION}\"")
add_definitions("-DL10N_DIR=\"${L10N_DIR}\"")

set (QT_DEBUG "-DQT_NO_DEBUG")
option (DEBUG_ENABLED "Enabling debug output" OFF)
if (DEBUG_ENABLED)
    set (QT_DEBUG "-DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -DQT_DEBUG")
    message(STATUS "Enabling debug output")
else(DEBUG_ENABLED)
    message(STATUS "Disabling debug output")
endif (DEBUG_ENABLED)

add_definitions(${QT_DEBUG})

install(FILES anagiwahst.desktop DESTINATION ${DESKTOPFILE_DIR})

add_subdirectory(src)
add_subdirectory(images)
add_subdirectory(l10n)
