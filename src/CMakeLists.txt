#include_directories(
#    ${CMAKE_CURRENT_BINARY_DIR}
#    ${CMAKE_CURRENT_SOURCE_DIR}
#)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (anagiwahst_SRCS
    main.cpp
    property.cpp
    propertymodel.cpp
    propertywriter.cpp
    configuration.cpp
    dbmanager.cpp
    project.cpp
    projectmodel.cpp
    projectfiltermodel.cpp
    unit.cpp
    unitmodel.cpp
    unitfiltermodel.cpp
)

set (anagiwahst_HEADERS
    property.h
    propertymodel.h
    propertywriter.h
    configuration.h
    dbmanager.h
    project.h
    projectmodel.h
    projectfiltermodel.h
    unit.h
    unitmodel.h
    unitfiltermodel.h
)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")


add_executable(anagiwahst ${anagiwahst_SRCS} ${anagiwahst_HEADERS})
target_link_libraries(anagiwahst
    Qt5::Core
    Qt5::Widgets
    Qt5::Qml
    Qt5::Quick
    Qt5::Sql
    Grantlee5::Templates)
install(TARGETS anagiwahst DESTINATION ${BINDIR})
