function(add_vkimow_executable)
    set(ARGUMENT_PREFIX THIS)
    set(SINGLE_VALUES   NAME SOLUTION_FOLDER OUTPUT_DIR)
    set(MULTI_VALUES    SOURCES
                        PUBLIC_INCLUDE_DIRS
                        PRIVATE_INCLUDE_DIRS
                        PUBLIC_LINK_LIBS
                        PRIVATE_LINK_LIBS
                        PUBLIC_COMPILE_DEFS
                        PUBLIC_DEBUG_COMPILE_DEFS
                        PUBLIC_RELEASE_COMPILE_DEFS
                        PRIVATE_COMPILE_DEFS
                        PRIVATE_DEBUG_COMPILE_DEFS
                        PRIVATE_RELEASE_COMPILE_DEFS
                        REQUIRED_FOR
                        DEPENDENCIES
                        )

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    # create
    add_executable(${THIS_NAME} ${THIS_SOURCES})
    message("\nADDED NEW EXECUTABLE '${THIS_NAME}'")

    # set properties
    set_vkimow_target_properties(
        TARGET                          ${THIS_NAME}
        SOLUTION_FOLDER                 ${THIS_SOLUTION_FOLDER}
        OUTPUT_DIR                      ${THIS_OUTPUT_DIR}
        PUBLIC_INCLUDE_DIRS             ${THIS_PUBLIC_INCLUDE_DIRS}
        PRIVATE_INCLUDE_DIRS            ${THIS_PRIVATE_INCLUDE_DIRS}
        PUBLIC_LINK_LIBS                ${THIS_PUBLIC_LINK_LIBS}
        PRIVATE_LINK_LIBS               ${THIS_PRIVATE_LINK_LIBS}
        PUBLIC_COMPILE_DEFS             ${THIS_PUBLIC_COMPILE_DEFS}
        PUBLIC_DEBUG_COMPILE_DEFS       ${THIS_PUBLIC_DEBUG_COMPILE_DEFS}
        PUBLIC_RELEASE_COMPILE_DEFS     ${THIS_PUBLIC_RELEASE_COMPILE_DEFS}
        PRIVATE_COMPILE_DEFS            ${THIS_PRIVATE_COMPILE_DEFS}
        PRIVATE_DEBUG_COMPILE_DEFS      ${THIS_PRIVATE_DEBUG_COMPILE_DEFS}
        PRIVATE_RELEASE_COMPILE_DEFS    ${THIS_PRIVATE_RELEASE_COMPILE_DEFS}
        REQUIRED_FOR                    ${THIS_REQUIRED_FOR}
        DEPENDENCIES                    ${THIS_DEPENDENCIES}
    )
endfunction()

function(add_vkimow_library)
    set(ARGUMENT_PREFIX THIS)
    set(SINGLE_VALUES   NAME TYPE SOLUTION_FOLDER OUTPUT_DIR)
    set(MULTI_VALUES    SOURCES
                        PUBLIC_INCLUDE_DIRS
                        PRIVATE_INCLUDE_DIRS
                        PUBLIC_LINK_LIBS
                        PRIVATE_LINK_LIBS
                        PUBLIC_COMPILE_DEFS
                        PUBLIC_DEBUG_COMPILE_DEFS
                        PUBLIC_RELEASE_COMPILE_DEFS
                        PRIVATE_COMPILE_DEFS
                        PRIVATE_DEBUG_COMPILE_DEFS
                        PRIVATE_RELEASE_COMPILE_DEFS
                        REQUIRED_FOR
                        DEPENDENCIES
                        )

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    # create
    if ("${THIS_TYPE}" STREQUAL "")
        set(THIS_TYPE STATIC)
    endif()
    add_library(${THIS_NAME} ${THIS_TYPE} ${THIS_SOURCES})
    message("\nADDED NEW ${THIS_TYPE} LIBRARY '${THIS_NAME}'")

    # alias
    get_property(PREFIX GLOBAL PROPERTY GLOBAL_VARIABLE_PREFIX_LOWER)
    set(LIBRARY_ALIAS ${PREFIX})
    set(LIBRARY_SOLUTIONS "")
    if (NOT "${THIS_SOLUTION_FOLDER}" STREQUAL "")
        string(REPLACE "/" " " LIBRARY_SOLUTIONS ${THIS_SOLUTION_FOLDER})
    endif()

    foreach(ADDITIONAL_ALIAS IN ITEMS ${LIBRARY_SOLUTIONS} ${THIS_NAME})
        string(TOLOWER ${ADDITIONAL_ALIAS} LOWER_ALIAS)
        set(LIBRARY_ALIAS "${LIBRARY_ALIAS}::${LOWER_ALIAS}")
    endforeach()

    add_library(${LIBRARY_ALIAS} ALIAS ${THIS_NAME})
    message("Alias: ${LIBRARY_ALIAS}")

    # set properties
    set_vkimow_target_properties(
        TARGET                          ${THIS_NAME}
        LIBRARY_TYPE                    ${THIS_TYPE}
        SOLUTION_FOLDER                 ${THIS_SOLUTION_FOLDER}
        OUTPUT_DIR                      ${THIS_OUTPUT_DIR}
        PUBLIC_INCLUDE_DIRS             ${THIS_PUBLIC_INCLUDE_DIRS}
        PRIVATE_INCLUDE_DIRS            ${THIS_PRIVATE_INCLUDE_DIRS}
        PUBLIC_LINK_LIBS                ${THIS_PUBLIC_LINK_LIBS}
        PRIVATE_LINK_LIBS               ${THIS_PRIVATE_LINK_LIBS}
        PUBLIC_COMPILE_DEFS             ${THIS_PUBLIC_COMPILE_DEFS}
        PUBLIC_DEBUG_COMPILE_DEFS       ${THIS_PUBLIC_DEBUG_COMPILE_DEFS}
        PUBLIC_RELEASE_COMPILE_DEFS     ${THIS_PUBLIC_RELEASE_COMPILE_DEFS}
        PRIVATE_COMPILE_DEFS            ${THIS_PRIVATE_COMPILE_DEFS}
        PRIVATE_DEBUG_COMPILE_DEFS      ${THIS_PRIVATE_DEBUG_COMPILE_DEFS}
        PRIVATE_RELEASE_COMPILE_DEFS    ${THIS_PRIVATE_RELEASE_COMPILE_DEFS}
        REQUIRED_FOR                    ${THIS_REQUIRED_FOR}
        DEPENDENCIES                    ${THIS_DEPENDENCIES}
    )
endfunction()

function(add_vkimow_copy_target)
    set(ARGUMENT_PREFIX THIS)
    set(SINGLE_VALUES   NAME INPUT_DIR OUTPUT_DIR)
    set(MULTI_VALUES    COMMENT
                        REQUIRED_FOR
                        DEPENDENCIES
                        )

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    # create
    add_custom_target(${THIS_NAME} ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${THIS_INPUT_DIR}
        ${THIS_OUTPUT_DIR}
        COMMENT ${THIS_COMMENT}
    )
    message("\nADDED NEW COPY COMMAND '${THIS_NAME}'")
    message("Input Dir: ${THIS_INPUT_DIR}")
    message("Output Dir: ${THIS_OUTPUT_DIR}")
    message("Comment: ${THIS_COMMENT}")

    # set properties
    set_vkimow_target_properties(
        TARGET                  ${THIS_NAME}
        SOLUTION_FOLDER         "CMake/Custom Targets"
        REQUIRED_FOR            ${THIS_REQUIRED_FOR}
        DEPENDENCIES            ${THIS_DEPENDENCIES}
    )
endfunction()

function(add_vkimow_custom_build_target)
    set(ARGUMENT_PREFIX THIS)
    set(SINGLE_VALUES   NAME SOLUTION_FOLDER)
    set(MULTI_VALUES    REQUIRED_FOR
                        DEPENDENCIES
                        )

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    # create
    add_custom_target(${THIS_NAME})
    message("\nADDED NEW CUSTOM BUILD TARGET '${THIS_NAME}'")

    # set properties
    set_vkimow_target_properties(
        TARGET                          ${THIS_NAME}
        SOLUTION_FOLDER                 ${THIS_SOLUTION_FOLDER}
        REQUIRED_FOR                    ${THIS_REQUIRED_FOR}
        DEPENDENCIES                    ${THIS_DEPENDENCIES}
    )
endfunction()

function(set_vkimow_target_properties)
    set(ARGUMENT_PREFIX THIS)
    set(SINGLE_VALUES TARGET SOLUTION_FOLDER OUTPUT_DIR LIBRARY_TYPE)
    set(MULTI_VALUES    PUBLIC_INCLUDE_DIRS
                        PRIVATE_INCLUDE_DIRS
                        PUBLIC_LINK_LIBS
                        PRIVATE_LINK_LIBS
                        PUBLIC_COMPILE_DEFS
                        PUBLIC_DEBUG_COMPILE_DEFS
                        PUBLIC_RELEASE_COMPILE_DEFS
                        PRIVATE_COMPILE_DEFS
                        PRIVATE_DEBUG_COMPILE_DEFS
                        PRIVATE_RELEASE_COMPILE_DEFS
                        REQUIRED_FOR
                        DEPENDENCIES
                        )

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    set(PUBLIC_TYPE PUBLIC)
    set(PRIVATE_TYPE PRIVATE)

    #Expection for interface libraries
    if("${THIS_LIBRARY_TYPE}" STREQUAL "INTERFACE")
        set(PUBLIC_TYPE INTERFACE)
        set(PRIVATE_TYPE INTERFACE)
    endif()

    #include
    set_vkimow_target_include_directories(TARGET ${THIS_TARGET} TYPE ${PUBLIC_TYPE}  DIRECTORIES ${THIS_PUBLIC_INCLUDE_DIRS})
    set_vkimow_target_include_directories(TARGET ${THIS_TARGET} TYPE ${PRIVATE_TYPE} DIRECTORIES ${THIS_PRIVATE_INCLUDE_DIRS})

    #link
    set_vkimow_target_link_libraries(TARGET ${THIS_TARGET} TYPE ${PUBLIC_TYPE} LIBRARIES ${THIS_PUBLIC_LINK_LIBS})
    set_vkimow_target_link_libraries(TARGET ${THIS_TARGET} TYPE ${PRIVATE_TYPE} LIBRARIES ${THIS_PRIVATE_LINK_LIBS})

    # compile defenitions
    set_vkimow_target_compile_defs(TARGET ${THIS_TARGET} TYPE ${PUBLIC_TYPE} COMPILE_DEFS ${THIS_PUBLIC_COMPILE_DEFS})
    set_vkimow_target_compile_defs(TARGET ${THIS_TARGET} TYPE ${PUBLIC_TYPE} CONFIG "Debug" COMPILE_DEFS ${THIS_PUBLIC_DEBUG_COMPILE_DEFS})
    set_vkimow_target_compile_defs(TARGET ${THIS_TARGET} TYPE ${PUBLIC_TYPE} CONFIG "Release" COMPILE_DEFS ${THIS_PUBLIC_RELEASE_COMPILE_DEFS})

    set_vkimow_target_compile_defs(TARGET ${THIS_TARGET} TYPE ${PRIVATE_TYPE} COMPILE_DEFS ${THIS_PRIVATE_COMPILE_DEFS})
    set_vkimow_target_compile_defs(TARGET ${THIS_TARGET} TYPE ${PRIVATE_TYPE} CONFIG "Debug" COMPILE_DEFS ${THIS_PRIVATE_DEBUG_COMPILE_DEFS})
    set_vkimow_target_compile_defs(TARGET ${THIS_TARGET} TYPE ${PRIVATE_TYPE} CONFIG "Release" COMPILE_DEFS ${THIS_PRIVATE_RELEASE_COMPILE_DEFS})

    # output dir
    if(NOT "${THIS_OUTPUT_DIR}" STREQUAL "")
        set_vkimow_target_output_dir(TARGET ${THIS_TARGET} OUTPUT_DIR ${THIS_OUTPUT_DIR})
        message("Output Dir: ${THIS_OUTPUT_DIR}")
    endif()

    # folder
    if(NOT "${THIS_SOLUTION_FOLDER}" STREQUAL "")
        set_target_properties(${THIS_TARGET} PROPERTIES FOLDER ${THIS_SOLUTION_FOLDER})
        message("Solution Folder: ${THIS_SOLUTION_FOLDER}")
    endif()

    if(NOT "${THIS_REQUIRED_FOR}" STREQUAL "")
        foreach(REQUARED_FOR_TARGET IN ITEMS ${THIS_REQUIRED_FOR})
            add_dependencies(${REQUARED_FOR_TARGET} ${THIS_TARGET} )
        endforeach()
        message("Requaried for: ${THIS_REQUIRED_FOR}")
    endif()

    if(NOT "${THIS_DEPENDENCIES}" STREQUAL "")
        foreach(DEPENDENCY IN ITEMS ${THIS_DEPENDENCIES})
            add_dependencies(${THIS_TARGET} ${DEPENDENCY} )
        endforeach()
        message("Dependencies: ${THIS_DEPENDENCIES}")
    endif()
endfunction()

function(set_vkimow_target_output_dir)
    set(ARGUMENT_PREFIX THIS)
    set(SINGLE_VALUES OUTPUT_DIR)
    set(MULTI_VALUES TARGET)

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    set_target_properties(${THIS_TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${THIS_OUTPUT_DIR})
    set_target_properties(${THIS_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${THIS_OUTPUT_DIR})
    set_target_properties(${THIS_TARGET} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${THIS_OUTPUT_DIR})
endfunction()

function(set_vkimow_target_compile_defs)
    set(ARGUMENT_PREFIX THIS)
    set(SINGLE_VALUES   TARGET TYPE CONFIG)
    set(MULTI_VALUES    COMPILE_DEFS
                        )

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    if(NOT "${THIS_COMPILE_DEFS}" STREQUAL "")
        if(NOT "${THIS_CONFIG}" STREQUAL "")
            target_compile_definitions(${THIS_TARGET} ${THIS_TYPE} $<$<CONFIG:${THIS_CONFIG}>:${THIS_COMPILE_DEFS}>)
            message("${THIS_CONFIG} ${THIS_TYPE} Compile Defs: ${THIS_COMPILE_DEFS}")
        else()
            target_compile_definitions(${THIS_TARGET} ${THIS_TYPE} ${THIS_COMPILE_DEFS})
            message("Overall ${THIS_TYPE} Compile Defs: ${THIS_COMPILE_DEFS}")
        endif()
    endif()
endfunction()

function(set_vkimow_target_include_directories)
    set(ARGUMENT_PREFIX THIS)
    set(SINGLE_VALUES   TARGET TYPE)
    set(MULTI_VALUES    DIRECTORIES)

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    if(NOT "${THIS_DIRECTORIES}" STREQUAL "")
        target_include_directories(${THIS_TARGET} ${THIS_TYPE} ${THIS_DIRECTORIES})
        message("${THIS_TYPE} Include Dirs: ${THIS_DIRECTORIES}")
    endif()
endfunction()

function(set_vkimow_target_link_libraries)
    set(ARGUMENT_PREFIX THIS)
    set(SINGLE_VALUES   TARGET TYPE)
    set(MULTI_VALUES    LIBRARIES)

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    if(NOT "${THIS_LIBRARIES}" STREQUAL "")
        target_link_libraries(${THIS_TARGET} ${THIS_TYPE} ${THIS_LIBRARIES})
        message("${THIS_TYPE} Link Libs: ${THIS_LIBRARIES}")
    endif()
endfunction()