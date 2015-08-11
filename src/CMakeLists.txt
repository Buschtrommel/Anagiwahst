#include_directories(
#    ${CMAKE_CURRENT_BINARY_DIR}
#    ${CMAKE_CURRENT_SOURCE_DIR}
#)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (anagiwahst_SRCS
    main.cpp
    propertycreator.cpp
    propertymodel.cpp
    propertywriter.cpp
)

set (anagiwahst_HEADERS
    property.h
    propertycreator.h
    propertymodel.h
    propertywriter.h
)

set(CMAKE_CXX_FLAGS "${CMAKE_CSS_FLAGS} -std=gnu++11")


add_executable(anagiwahst ${anagiwahst_SRCS} ${anagiwahst_HEADERS} ../qml.qrc)
target_link_libraries(anagiwahst Qt5::Core Qt5::Widgets Qt5::Qml Qt5::Quick)
install(TARGETS anagiwahst DESTINATION ${BINDIR})
