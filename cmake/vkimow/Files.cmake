
function(find_vkimow_auto_files)
    set(ARGUMENTS_PREFIX THIS)
    set(SINGLE_VALUES   ROOT_DIR TARGET TYPE VARIABLE)
    set(MULTI_VALUES    INCLUDE_DIRS EXCLUDE_DIRS EXTENSIONS)
    # parse
    cmake_parse_arguments(${ARGUMENTS_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    message("\nFIND AUTO '${THIS_VARIABLE}' FILES FOR '${THIS_TARGET}'")

    if ("${THIS_TYPE}" STREQUAL "")
        set(THIS_TYPE "GLOB_RECURSE")
    endif()

    if("${THIS_INCLUDE_DIRS}" STREQUAL "")
        set(THIS_INCLUDE_DIRS ${THIS_ROOT_DIR})
    endif()

    # find auto files
    private_find_vkimow_auto_files(
        TYPE ${THIS_TYPE}
        ROOT_DIR ${THIS_ROOT_DIR}
        INCLUDE_DIRS  ${THIS_INCLUDE_DIRS}
        EXCLUDE_DIRS  ${THIS_EXCLUDE_DIRS}
        VARIABLE AUTO_FILES
        EXTENSIONS ${THIS_EXTENSIONS}
    )
    message("Extensions: ${PROCESSED_EXTENSIONS}")

    # set auto files
    private_set_vkimow_files(
        TARGET ${THIS_TARGET}
        DIR ${THIS_ROOT_DIR}
        VARIABLE ${THIS_VARIABLE}
        TYPE Auto
        FILES ${AUTO_FILES}
    )
endfunction()

macro(private_find_vkimow_auto_files)
    set(ARGUMENTS_PREFIX PRIVATE_FIND_AUTO)
    set(SINGLE_VALUES TYPE ROOT_DIR VARIABLE)
    set(MULTI_VALUES  INCLUDE_DIRS EXCLUDE_DIRS EXTENSIONS)
    # parse
    cmake_parse_arguments(${ARGUMENTS_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${PRIVATE_FIND_AUTO_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${PRIVATE_FIND_AUTO_UNPARSED_ARGUMENTS}")
    endif()

    if ("${PRIVATE_FIND_AUTO_ROOT_DIR}" STREQUAL "")
        message(FATAL_ERROR "Can't find files without ROOT_DIR")
    endif()

    if ("${PRIVATE_FIND_AUTO_INCLUDE_DIRS}" STREQUAL "")
        message(FATAL_ERROR "Can't find files without INCLUDE_DIRS")
    endif()

    if ("${PRIVATE_FIND_AUTO_VARIABLE}" STREQUAL "")
        message(FATAL_ERROR "Can't find files without VARIABLE")
    endif()

    if ("${PRIVATE_FIND_AUTO_EXTENSIONS}" STREQUAL "")
        message(FATAL_ERROR "Can't find files without EXTENSIONS")
    endif()

    if ("${PRIVATE_FIND_AUTO_TYPE}" STREQUAL "")
        message(FATAL_ERROR "Can't find files without TYPE")
    endif()

    if (NOT "${PRIVATE_FIND_AUTO_TYPE}" STREQUAL "GLOB" AND NOT "${PRIVATE_FIND_AUTO_TYPE}" STREQUAL "GLOB_RECURSE")
        message(FATAL_ERROR "TYPE should be rather GLOB or GLOB_RECURSE")
    endif()

    message("Root Dir: ${PRIVATE_FIND_AUTO_ROOT_DIR}")

    # dirs check
    set(INCLUDE_DIRS_FOR_OUTPUT "")
    foreach(DIR IN ITEMS ${PRIVATE_FIND_AUTO_INCLUDE_DIRS})
        string(FIND ${DIR} ${PRIVATE_FIND_AUTO_ROOT_DIR} INDEX)
        if(NOT ${INDEX} EQUAL 0)
            message(FATAL_ERROR "All dirs in INCLUDE_DIRS should include ROOT_DIR")
            message(FATAL_ERROR "Error Include Dir: ${DIR}")
        endif()
        if("${DIR}" STREQUAL "${PRIVATE_FIND_AUTO_ROOT_DIR}")
            set(INCLUDE_DIRS_FOR_OUTPUT "${INCLUDE_DIRS_FOR_OUTPUT}; 'Root Dir'")
        else()
            string(REPLACE "${PRIVATE_FIND_AUTO_ROOT_DIR}/" "" RELATIVE_PATH_OF_DIR ${DIR})
            set(INCLUDE_DIRS_FOR_OUTPUT "${INCLUDE_DIRS_FOR_OUTPUT}; ${RELATIVE_PATH_OF_DIR}")
        endif()
    endforeach()
    string(SUBSTRING ${INCLUDE_DIRS_FOR_OUTPUT} 1 -1 INCLUDE_DIRS_FOR_OUTPUT)
    message("Include Dirs: ${INCLUDE_DIRS_FOR_OUTPUT}")

    if (NOT "${PRIVATE_FIND_AUTO_EXCLUDE_DIRS}" STREQUAL "")
        set(EXCLUDE_DIRS_FOR_OUTPUT "")
        foreach(DIR IN ITEMS ${PRIVATE_FIND_AUTO_EXCLUDE_DIRS})
            string(FIND ${DIR} ${PRIVATE_FIND_AUTO_ROOT_DIR} INDEX)
            if(NOT ${INDEX} EQUAL 0)
                message(FATAL_ERROR "All dirs in EXCLUDE_DIRS should include ROOT_DIR")
                message(FATAL_ERROR "Error Exclude Dir: ${DIR}")
            endif()
            if("${DIR}" STREQUAL "${PRIVATE_FIND_AUTO_ROOT_DIR}")
                set(EXCLUDE_DIRS_FOR_OUTPUT "${EXCLUDE_DIRS_FOR_OUTPUT}; 'Root Dir'")
            else()
                string(REPLACE "${PRIVATE_FIND_AUTO_ROOT_DIR}/" "" RELATIVE_PATH_OF_DIR ${DIR})
            set(EXCLUDE_DIRS_FOR_OUTPUT "${EXCLUDE_DIRS_FOR_OUTPUT}; ${RELATIVE_PATH_OF_DIR}")
        endif()
        endforeach()
        string(SUBSTRING ${EXCLUDE_DIRS_FOR_OUTPUT} 1 -1 EXCLUDE_DIRS_FOR_OUTPUT)
        message("Exclude Dirs: ${EXCLUDE_DIRS_FOR_OUTPUT}")
    endif()

    # process extensions
    process_extensions(
        VARIABLE PROCESSED_EXTENSIONS
        EXTENSIONS ${PRIVATE_FIND_AUTO_EXTENSIONS}
    )

    # auto files
    set(RESULT_AUTO_FILES "")
    set(TEMPORARY_AUTO_FILES "")
    foreach(INCLUDE_DIR IN ITEMS ${PRIVATE_FIND_AUTO_INCLUDE_DIRS})
        foreach(EXTENSION IN ITEMS ${PROCESSED_EXTENSIONS})
            file(GLOB_RECURSE TEMPORARY_AUTO_FILES ${INCLUDE_DIR}/*${EXTENSION})
            set(RESULT_AUTO_FILES ${RESULT_AUTO_FILES} ${TEMPORARY_AUTO_FILES})
        endforeach()
    endforeach()
    set(${PRIVATE_FIND_AUTO_VARIABLE} ${RESULT_AUTO_FILES})

    #exclude
    if (NOT "${PRIVATE_FIND_AUTO_EXCLUDE_DIRS}" STREQUAL "")
        set(TEMPORARY_AUTO_FILES ${RESULT_AUTO_FILES})
        set(RESULT_AUTO_FILES "")
        foreach(EXCLUDE_DIR IN ITEMS ${PRIVATE_FIND_AUTO_EXCLUDE_DIRS})
            foreach(FILE IN ITEMS ${TEMPORARY_AUTO_FILES})
                string(FIND ${FILE} ${EXCLUDE_DIR} INDEX)
                if(NOT ${INDEX} EQUAL 0)
                    set(RESULT_AUTO_FILES ${RESULT_AUTO_FILES} ${FILE})
                endif()
            endforeach()
        endforeach()
        set(${PRIVATE_FIND_AUTO_VARIABLE} ${RESULT_AUTO_FILES})
    endif()
endmacro()

function(set_vkimow_custom_files)
    set(ARGUMENTS_PREFIX THIS)
    set(SINGLE_VALUES   TARGET DIR VARIABLE)
    set(MULTI_VALUES    FILES)
    # parse
    cmake_parse_arguments(${ARGUMENTS_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    message("\nSET CUSTOM '${THIS_VARIABLE}' FILES FOR '${THIS_TARGET}'")

    # custom files
    foreach(FILE IN ITEMS ${THIS_FILES})
        set(TEMPORARY_CUSTOM_FILE ${THIS_DIR}/${FILE})
        set(CUSTOM_FILES ${CUSTOM_FILES} ${TEMPORARY_CUSTOM_FILE})
    endforeach()

    private_set_vkimow_files(
        TARGET ${THIS_TARGET}
        DIR ${THIS_DIR}
        VARIABLE ${THIS_VARIABLE}
        TYPE Custom
        FILES ${CUSTOM_FILES}
    )
endfunction()

macro(private_set_vkimow_files)
    set(ARGUMENTS_PREFIX PRIVATE_SET_FILES)
    set(SINGLE_VALUES   TARGET DIR VARIABLE TYPE)
    set(MULTI_VALUES    FILES)
    # parse
    cmake_parse_arguments(${ARGUMENTS_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${PRIVATE_SET_FILES_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${PRIVATE_SET_FILES_UNPARSED_ARGUMENTS}")
    endif()

    if ("${PRIVATE_SET_FILES_TARGET}" STREQUAL "")
        message(FATAL_ERROR "Can't set files variable without TARGET")
    endif()

    if ("${PRIVATE_SET_FILES_DIR}" STREQUAL "")
        message(FATAL_ERROR "Can't set files variable without DIR")
    endif()

    if ("${PRIVATE_SET_FILES_VARIABLE}" STREQUAL "")
        message(FATAL_ERROR "Can't set files variable without VARIABLE")
    endif()

    if ("${PRIVATE_SET_FILES_TYPE}" STREQUAL "")
        message(FATAL_ERROR "Can't set files variable without TYPE")
    endif()

    private_set_vkimow_target_variable(
        TARGET ${PRIVATE_SET_FILES_TARGET}
        VARIABLE ${PRIVATE_SET_FILES_TYPE}_${PRIVATE_SET_FILES_VARIABLE}
        VALUE ${PRIVATE_SET_FILES_FILES}
    )

    # debug
    message("Dir: ${PRIVATE_SET_FILES_DIR}")
    if (NOT "${PRIVATE_SET_FILES_FILES}" STREQUAL "")
        string(REPLACE "${PRIVATE_SET_FILES_DIR}/" ", " FILES_FOR_OUTPUT ${PRIVATE_SET_FILES_FILES})
        string(SUBSTRING ${FILES_FOR_OUTPUT} 2 -1 FILES_FOR_OUTPUT)
        message("${PRIVATE_SET_FILES_TYPE} '${PRIVATE_SET_FILES_VARIABLE}': ${FILES_FOR_OUTPUT}")
    else()
        message("${PRIVATE_SET_FILES_TYPE} '${PRIVATE_SET_FILES_VARIABLE}': No files at all")
    endif()
endmacro()

function(set_vkimow_target_files)
    set(ARGUMENT_PREFIX THIS)
    set(SINGLE_VALUES TARGET VARIABLE FILES_DIR)
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

    # set
    private_set_vkimow_target_variable(
        TARGET ${THIS_TARGET}
        VARIABLE ${THIS_VARIABLE}
        VALUE ${THIS_FILES}
    )

    generate_vkimow_ide_folders(
        FILES_DIR ${THIS_FILES_DIR}
        FILES ${THIS_FILES}
        )
endfunction()

function(process_vkimow_configure_folder)
    set(ARGUMENT_PREFIX THIS)
    set(SINGLE_VALUES FILES_DIR OUTPUT_DIR)
    set(MULTI_VALUES EXTENSIONS)

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    if ("${THIS_OUTPUT_DIR}" STREQUAL "")
        message(FATAL_ERROR "Can't process config without OUTPUT_DIR")
    endif()

    if ("${THIS_FILES_DIR}" STREQUAL "")
        message(FATAL_ERROR "Can't process config without FILES_DIR")
    endif()

    if ("${THIS_EXTENSIONS}" STREQUAL "")
        set(THIS_EXTENSIONS .in)
    endif()

    private_find_vkimow_auto_files(
        TYPE GLOB_RECURSE
        ROOT_DIR  ${THIS_FILES_DIR}
        INCLUDE_DIRS  ${THIS_FILES_DIR}
        VARIABLE CONFIG_FILES
        EXTENSIONS ${THIS_EXTENSIONS}
    )

    process_vkimow_configure_files(
        FILES_DIR ${THIS_FILES_DIR}
        OUTPUT_DIR ${THIS_OUTPUT_DIR}
        FILES ${CONFIG_FILES}
    )
endfunction()


function(process_vkimow_configure_files)
    set(ARGUMENT_PREFIX THIS)
    set(SINGLE_VALUES FILES_DIR OUTPUT_DIR)
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

    if ("${THIS_OUTPUT_DIR}" STREQUAL "")
        message(FATAL_ERROR "Can't process config without OUTPUT_DIR")
    endif()

    if ("${THIS_FILES_DIR}" STREQUAL "")
        message(FATAL_ERROR "Can't process config without FILES_DIR")
    endif()

    if ("${THIS_FILES}" STREQUAL "")
        message("Can't process config without files in FILES")
        return()
    endif()

    foreach(FILE IN ITEMS ${THIS_FILES})
        string(FIND ${FILE} ${THIS_FILES_DIR} INDEX)
        if(NOT ${INDEX} EQUAL 0)
            message(FATAL_ERROR "All paths in FILES should include FILES_DIR")
            message(FATAL_ERROR "Error file: ${FILE}")
        endif()
    endforeach()

    foreach(FILE IN ITEMS ${THIS_FILES})
        string(REPLACE "${THIS_FILES_DIR}/" "" FILE_NAME ${FILE})
        string(REGEX REPLACE "\\.[^.]*$" ""  FILE_NAME_WITHOUT_LAST_EXTENSION ${FILE_NAME})
        configure_file(
            ${FILE}
            "${THIS_OUTPUT_DIR}/${FILE_NAME_WITHOUT_LAST_EXTENSION}" ESCAPE_QUOTES
        )
        set(OUTPUT_FILES "${OUTPUT_FILES}, ${FILE_NAME} -> ${FILE_NAME_WITHOUT_LAST_EXTENSION}")
        string(SUBSTRING ${OUTPUT_FILES} 2 -1 OUTPUT_FILES)
    endforeach()

    # debug
    message("\nPROCESS CONFIG")
    message("Files Dir: ${THIS_FILES_DIR}")
    message("Output Dir: ${THIS_OUTPUT_DIR}")
    message("Output Files: ${OUTPUT_FILES}")
endfunction()

macro(process_extensions)
    set(ARGUMENT_PREFIX PROCESS_EXTENSIONS)
    set(SINGLE_VALUES VARIABLE)
    set(MULTI_VALUES EXTENSIONS)

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        "${MULTI_VALUES}"
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    set(${PROCESS_EXTENSIONS_VARIABLE} "")
    foreach(UNPROCESSED_EXTENSION IN ITEMS ${PROCESS_EXTENSIONS_EXTENSIONS})
        string(REPLACE "." "" EXTENSION_WITHOUT_DOT ${UNPROCESSED_EXTENSION})
        string(TOLOWER ${EXTENSION_WITHOUT_DOT} EXTENSION_LOW)
        set(${PROCESS_EXTENSIONS_VARIABLE} ${${PROCESS_EXTENSIONS_VARIABLE}} ".${EXTENSION_LOW}")
    endforeach()
endmacro()
