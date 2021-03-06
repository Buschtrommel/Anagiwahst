# CMakeLists for anagiwahst
project(anagiwahst)

cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)


set(ANAGIWAHST_VERSION_MAJOR "0")
set(ANAGIWAHST_VERSION_MINOR "6")
set(ANAGIWAHST_VERSION_PATCH "3")
set(ANAGIWAHST_VERSION "${ANAGIWAHST_VERSION_MAJOR}.${ANAGIWAHST_VERSION_MINOR}.${ANAGIWAHST_VERSION_PATCH}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(PkgConfig REQUIRED)
find_package(Grantlee5 REQUIRED)
find_package(Qt5 5.5.0 COMPONENTS
    Qml
    Quick
    Widgets
    Sql
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
set (L10N_DIR "${APP_DIR}/l10n" CACHE PATH "Directory to install translations")
set (TMPL_DIR "${APP_DIR}/templates" CACHE PATH "Directory to install templates")
set (QML_DIR "${APP_DIR}/qml" CACHE PATH "Directory to install QML files")
set (VERSION "${ANAGIWAHST_VERSION}")

add_definitions("-DAPP_VERSION=\"${ANAGIWAHST_VERSION}\"")
add_definitions("-DL10N_DIR=\"${L10N_DIR}\"")
add_definitions("-DTMPL_DIR=\"${TMPL_DIR}\"")
add_definitions("-DQML_DIR=\"${QML_DIR}\"")

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS_DEBUG "-Wall -fsanitize=address -ggdb")

set (QT_DEBUG "-DQT_NO_DEBUG")
option (DEBUG_ENABLED "Enabling debug output" OFF)
if (DEBUG_ENABLED)
    set (QT_DEBUG "-DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -DQT_DEBUG")
    message(STATUS "Enabling debug output")
endif (DEBUG_ENABLED)

add_definitions(${QT_DEBUG})

install(FILES anagiwahst.desktop DESTINATION ${DESKTOPFILE_DIR})
install(DIRECTORY templates/ DESTINATION ${TMPL_DIR})

add_subdirectory(src)
add_subdirectory(images)
add_subdirectory(l10n)
add_subdirectory(qml)
