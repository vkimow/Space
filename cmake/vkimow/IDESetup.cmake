function(set_vkimow_subsolution NAME)
    # set subsolution
    message("\nADDED NEW SUBSOLUTION '${NAME}'")

    # preparation
    get_property(PREFIX GLOBAL PROPERTY GLOBAL_VARIABLE_PREFIX_UPPER)

    # set subsolution path
    if(NOT "${${PREFIX}_CURRENT_SUBSOLUTION_RELATIVE_PATH}" STREQUAL "")
        set(SUBSOLUTION_RELATIVE_PATH "${${PREFIX}_CURRENT_SUBSOLUTION_RELATIVE_PATH}/${NAME}")
    else()
        set(SUBSOLUTION_RELATIVE_PATH "${NAME}")
    endif()

    # set subsolution dirs
    set(SUBSOLUTION_TESTS_RELATIVE_PATH "${SUBSOLUTION_RELATIVE_PATH}/Tests")
    set(SUBSOLUTION_SOURCE_DIR "${${PREFIX}_SOURCE_DIR}/${SUBSOLUTION_RELATIVE_PATH}")
    set(SUBSOLUTION_INCLUDE_DIR "${${PREFIX}_INCLUDE_DIR}/${SUBSOLUTION_RELATIVE_PATH}")

    private_set_vkimow_variable(VARIABLE SUBSOLUTION_NAME                   VALUE ${NAME})
    private_set_vkimow_variable(VARIABLE SUBSOLUTION_SOURCE_DIR             VALUE ${SUBSOLUTION_SOURCE_DIR})
    private_set_vkimow_variable(VARIABLE SUBSOLUTION_INCLUDE_DIR            VALUE ${SUBSOLUTION_INCLUDE_DIR})
    private_set_vkimow_variable(VARIABLE SUBSOLUTION_RELATIVE_PATH          VALUE ${SUBSOLUTION_RELATIVE_PATH})
    private_set_vkimow_variable(VARIABLE SUBSOLUTION_TESTS_RELATIVE_PATH    VALUE ${SUBSOLUTION_TESTS_RELATIVE_PATH})

    set_vkimow_global_property (VARIABLE ${NAME}_SUBSOLUTION_SOURCE_DIR             VALUE ${SUBSOLUTION_SOURCE_DIR})
    set_vkimow_global_property (VARIABLE ${NAME}_SUBSOLUTION_INCLUDE_DIR            VALUE ${SUBSOLUTION_INCLUDE_DIR})
    set_vkimow_global_property (VARIABLE ${NAME}_SUBSOLUTION_RELATIVE_PATH          VALUE ${SUBSOLUTION_RELATIVE_PATH})
    set_vkimow_global_property (VARIABLE ${NAME}_SUBSOLUTION_TESTS_RELATIVE_PATH    VALUE ${SUBSOLUTION_TESTS_RELATIVE_PATH})


    message("Relative IDE Path:         ${SUBSOLUTION_RELATIVE_PATH}")
    message("Tests Relative IDE Path:   ${SUBSOLUTION_TESTS_RELATIVE_PATH}")
    message("Source dir:                ${SUBSOLUTION_SOURCE_DIR}")
    message("Include dir:               ${SUBSOLUTION_INCLUDE_DIR}")
endFunction()

function(generate_vkimow_ide_folders)
    set(ARGUMENT_PREFIX THIS)
    set(SINGLE_VALUES FILES_DIR)
    set(MULTI_VALUES FILES)

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    foreach(FILE IN ITEMS ${THIS_FILES})
        get_filename_component(FILE_PATH "${FILE}" REALPATH)
        get_filename_component(FILE_PATH "${FILE_PATH}" PATH)
        file(RELATIVE_PATH FILE_PATH "${THIS_FILES_DIR}" "${FILE_PATH}")

        string(REPLACE "/" "\\" FILE_PATH "${FILE_PATH}")
        string(REPLACE "..\\" "" FILE_PATH "${FILE_PATH}")

        source_group("${FILE_PATH}" FILES "${FILE}")
    endforeach()
endfunction()