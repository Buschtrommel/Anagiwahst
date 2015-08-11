find_program(LRELEASE_CMD_PATH NAMES lrelease lrelease-qt5)

set(LRELEASE_CMD ${LRELEASE_CMD_PATH})

if(LRELEASE_CMD)
    message(STATUS "Found lrelease at ${LRELEASE_CMD}")
    message(STATUS "Translations are enabled")
else(LRELEASE_CMD)
    message(WARNING "lrelease executable cannot be found")
    message(WARNING "Translations are disabled")
endif(LRELEASE_CMD)

if (LRELEASE_CMD)

    set(LANGS de)

    foreach(l ${LANGS})
        execute_process(COMMAND ${LRELEASE_CMD} -silent ${CMAKE_CURRENT_SOURCE_DIR}/anagiwahst_${l}.ts -qm ${CMAKE_CURRENT_BINARY_DIR}/anagiwahst_${l}.qm)
        list(APPEND QM_FILES ${CMAKE_CURRENT_BINARY_DIR}/anagiwahst_${l}.qm)
    endforeach(l)

    install (FILES ${QM_FILES} DESTINATION ${L10N_DIR})

endif(LRELEASE_CMD)
