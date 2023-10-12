
function(setup_vkimow_global_variable_prefix)
    message("\n=====SETUP OF GLOBAL VARIABLE PREFIX=====")

    set(ARGUMENT_PREFIX THIS)
    set(SINGLE_VALUES LOWERCASE_PREFIX UPPERCASE_PREFIX)

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        ""
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    # preparation
    if("${THIS_LOWERCASE_PREFIX}" STREQUAL "" AND "${THIS_UPPERCASE_PREFIX}" STREQUAL "")
        message(FATAL_ERROR "At least one argument should be given: LOWERCASE_PREFIX or UPPERCASE_PREFIX")
    endif()

    if(NOT "${THIS_LOWERCASE_PREFIX}" STREQUAL "")
        string(TOLOWER ${THIS_LOWERCASE_PREFIX} LOWERCASE_PREFIX)
    else()
        string(TOLOWER ${THIS_UPPERCASE_PREFIX} LOWERCASE_PREFIX)
    endif()

    if(NOT "${THIS_UPPERCASE_PREFIX}" STREQUAL "")
        string(TOUPPER ${THIS_UPPERCASE_PREFIX} UPPERCASE_PREFIX)
    else()
        string(TOUPPER ${THIS_LOWERCASE_PREFIX} UPPERCASE_PREFIX)
    endif()

    # set properties
    set_property(GLOBAL PROPERTY GLOBAL_VARIABLE_PREFIX_UPPER ${UPPERCASE_PREFIX})
    set_property(GLOBAL PROPERTY GLOBAL_VARIABLE_PREFIX_LOWER ${LOWERCASE_PREFIX})

    message("Global Variable Prefix lowercase: ${LOWERCASE_PREFIX}")
    message("Global Variable Prefix uppercase: ${UPPERCASE_PREFIX}")
endfunction()

function(set_vkimow_global_property)
    set(ARGUMENT_PREFIX THIS)
    set(SINGLE_VALUES VARIABLE)
    set(MULTI_VALUES VALUE VALUES)

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    if ("${THIS_VARIABLE}" STREQUAL "")
        message(FATAL_ERROR "Can't create target variable without VARIABLE")
    endif()

    # preparation
    get_property(PREFIX GLOBAL PROPERTY GLOBAL_VARIABLE_PREFIX_UPPER)
    string(TOUPPER ${THIS_VARIABLE} VARIABLE_UPPER)

    # setting
    set_property(GLOBAL PROPERTY ${PREFIX}_${VARIABLE_UPPER} ${THIS_VALUE} ${THIS_VALUES})
endfunction()

function(set_vkimow_target_variable)
    set(ARGUMENT_PREFIX THIS)
    set(SINGLE_VALUES TARGET VARIABLE)
    set(MULTI_VALUES VALUE VALUES)

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    private_set_vkimow_target_variable(
        TARGET ${THIS_TARGET}
        VARIABLE ${THIS_VARIABLE}
        VALUE ${THIS_VALUE} ${THIS_VALUES}
    )
endfunction()

macro(private_set_vkimow_target_variable)
    set(ARGUMENT_PREFIX PRIVATE_SET_VARIABLE)
    set(SINGLE_VALUES TARGET VARIABLE)
    set(MULTI_VALUES VALUE)

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${PRIVATE_SET_VARIABLE_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${PRIVATE_SET_VARIABLE_UNPARSED_ARGUMENTS}")
    endif()

    if ("${PRIVATE_SET_VARIABLE_TARGET}" STREQUAL "")
        message(FATAL_ERROR "Can't create target variable without TARGET")
    endif()

    if ("${PRIVATE_SET_VARIABLE_VARIABLE}" STREQUAL "")
        message(FATAL_ERROR "Can't create target variable without VARIABLE")
    endif()

    # preparation
    get_property(PREFIX GLOBAL PROPERTY GLOBAL_VARIABLE_PREFIX_UPPER)
    string(TOUPPER ${PRIVATE_SET_VARIABLE_TARGET} TARGET_UPPER)
    string(TOUPPER ${PRIVATE_SET_VARIABLE_VARIABLE} VARIABLE_UPPER)

    # setting
    set(${PREFIX}_CURRENT_${VARIABLE_UPPER} ${PRIVATE_SET_VARIABLE_VALUE} PARENT_SCOPE)
    set_property(GLOBAL PROPERTY ${PREFIX}_${TARGET_UPPER}_${VARIABLE_UPPER} ${PRIVATE_SET_VARIABLE_VALUE})
endmacro()

macro(private_set_vkimow_variable)
    set(ARGUMENT_PREFIX PRIVATE_SET_VARIABLE)
    set(SINGLE_VALUES VARIABLE)
    set(MULTI_VALUES VALUE)

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${PRIVATE_SET_VARIABLE_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${PRIVATE_SET_VARIABLE_UNPARSED_ARGUMENTS}")
    endif()

    if ("${PRIVATE_SET_VARIABLE_VARIABLE}" STREQUAL "")
        message(FATAL_ERROR "Can't create target variable without VARIABLE")
    endif()

    # preparation
    get_property(PREFIX GLOBAL PROPERTY GLOBAL_VARIABLE_PREFIX_UPPER)
    string(TOUPPER ${PRIVATE_SET_VARIABLE_VARIABLE} VARIABLE_UPPER)

    # setting
    set(${PREFIX}_CURRENT_${VARIABLE_UPPER} ${PRIVATE_SET_VARIABLE_VALUE} PARENT_SCOPE)
endmacro()
