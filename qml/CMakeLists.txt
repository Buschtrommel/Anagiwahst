file(GLOB QML_FILES "*.qml")

add_custom_target(anagiwahst-qml SOURCES ${QML_FILES})

install (FILES ${QML_FILES} DESTINATION ${QML_DIR})
