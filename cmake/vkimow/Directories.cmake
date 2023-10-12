function(set_vkimow_default_target_dirs)
    set(ARGUMENTS_PREFIX THIS)
    set(SINGLE_VALUES TARGET SOURCE_DIR INCLUDE_DIR OUTPUT_DIR TESTS_DIR)

    # parse
    cmake_parse_arguments(${ARGUMENTS_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        ""
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    # preparation
    message("\nSETTING DERICTORY PATHS FOR '${THIS_TARGET}'")

    # source dir
    private_set_vkimow_custom_target_dir(
        TARGET ${THIS_TARGET}
        VARIABLE Source
        DIR ${THIS_SOURCE_DIR}
    )

    # include dir
    private_set_vkimow_custom_target_dir(
        TARGET ${THIS_TARGET}
        VARIABLE Include
        DIR ${THIS_INCLUDE_DIR}
    )

    # output dir
    private_set_vkimow_custom_target_dir(
        TARGET ${THIS_TARGET}
        VARIABLE Output
        DIR ${THIS_OUTPUT_DIR}
    )

    # tests dir
    private_set_vkimow_custom_target_dir(
        TARGET ${THIS_TARGET}
        VARIABLE Tests
        DIR ${THIS_TESTS_DIR}
    )
endfunction()

function(set_vkimow_custom_target_dir)
    set(ARGUMENTS_PREFIX THIS)
    set(SINGLE_VALUES TARGET VARIABLE DIR)

    # parse
    cmake_parse_arguments(${ARGUMENTS_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        ""
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    private_set_vkimow_custom_target_dir(
        TARGET ${THIS_TARGET}
        VARIABLE ${THIS_VARIABLE}
        DIR ${THIS_DIR}
    )
endfunction()

macro(private_set_vkimow_custom_target_dir)
    set(ARGUMENTS_PREFIX PRIVATE_SET_DIR)
    set(SINGLE_VALUES TARGET VARIABLE DIR)

    # parse
    cmake_parse_arguments(${ARGUMENTS_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        ""
                        ${ARGN})

    if (NOT "${PRIVATE_SET_DIR_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${PRIVATE_SET_DIR_UNPARSED_ARGUMENTS}")
    endif()

    # custom dir
    private_set_vkimow_target_variable(
        TARGET ${PRIVATE_SET_DIR_TARGET}
        VARIABLE ${PRIVATE_SET_DIR_VARIABLE}_DIR
        VALUE ${PRIVATE_SET_DIR_DIR}
    )

    if (NOT "${PRIVATE_SET_DIR_DIR}" STREQUAL "")
        message("${PRIVATE_SET_DIR_VARIABLE} Dir: ${PRIVATE_SET_DIR_DIR}")
    else()
        message("${PRIVATE_SET_DIR_VARIABLE} Dir: Empty")
    endif()
endmacro()