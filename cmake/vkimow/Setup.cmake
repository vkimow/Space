
macro(setup_vkimow_configurations)
    message("\n=====SETUP OF CONFIGURATIONS=====")
        if(NOT SET_UP_CONFIGURATIONS_DONE)
            set(SET_UP_CONFIGURATIONS_DONE TRUE CACHE INTERNAL "")

            # No reason to set CMAKE_CONFIGURATION_TYPES if it's not a multiconfig generator
            # Also no reason mess with CMAKE_BUILD_TYPE if it's a multiconfig generator.
            get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
            if(isMultiConfig)
                set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING "" FORCE)
            else()
                if(NOT CMAKE_BUILD_TYPE)
                    message("Defaulting to release build.")
                    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
                endif()
                set_property(CACHE CMAKE_BUILD_TYPE PROPERTY HELPSTRING "Choose the type of build")
                # set the valid options for cmake-gui drop-down list
                set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS  Debug Release)
            endif()
            get_property(PREFIX GLOBAL PROPERTY GLOBAL_VARIABLE_PREFIX_UPPER)
            set(${PREFIX}_CONFIG_STRING "$<$<CONFIG:Debug>:debug>$<$<CONFIG:Release>:release>" CACHE INTERNAL "")
            message("Config String: ${${PREFIX}_CONFIG_STRING}")
        else()
            message("=====SETUP OF CONFIGURATIONS HAVE BEEN ALREADY DONE=====")
        endif()
endmacro()

macro(setup_vkimow_global_directories)
    message("\n=====SETUP OF GLOBAL DIRECTORIES=====")

    # preparation
    set(ROOT_DIR ${CMAKE_SOURCE_DIR})
    get_property(PREFIX GLOBAL PROPERTY GLOBAL_VARIABLE_PREFIX_UPPER)

    # set global directories in cache
    set(${PREFIX}_ROOT_DIR       "${ROOT_DIR}"                                  CACHE INTERNAL "")
    set(${PREFIX}_INCLUDE_DIR    "${ROOT_DIR}/include"                          CACHE INTERNAL "")
    set(${PREFIX}_SOURCE_DIR     "${ROOT_DIR}/src"                              CACHE INTERNAL "")
    set(${PREFIX}_VENDOR_DIR     "${ROOT_DIR}/vendor"                           CACHE INTERNAL "")
    set(${PREFIX}_PROJECT_DIR    "${ROOT_DIR}/project"                          CACHE INTERNAL "")
    set(${PREFIX}_BIN_DIR        "${ROOT_DIR}/bin"                              CACHE INTERNAL "")
    set(${PREFIX}_BIN_CONFIG_DIR "${ROOT_DIR}/bin/${${PREFIX}_CONFIG_STRING}"   CACHE INTERNAL "")

    message("Root Dir:              ${${PREFIX}_ROOT_DIR}")
    message("Include Dir:           ${${PREFIX}_INCLUDE_DIR}")
    message("Source Dir:            ${${PREFIX}_SOURCE_DIR}")
    message("Vendor Dir:            ${${PREFIX}_VENDOR_DIR}")
    message("Project Dir:           ${${PREFIX}_PROJECT_DIR}")
    message("Bin Dir:               ${${PREFIX}_BIN_DIR}")
    message("Bin Config Dir:        ${${PREFIX}_BIN_CONFIG_DIR}")

    # set current subsolution directories
    set(${PREFIX}_CURRENT_SUBSOLUTION_SOURCE_DIR "${${PREFIX}_SOURCE_DIR}")
    set(${PREFIX}_CURRENT_SUBSOLUTION_INCLUDE_DIR "${${PREFIX}_INCLUDE_DIR}")
    set(${PREFIX}_CURRENT_SUBSOLUTION_OUTPUT_DIR "${${PREFIX}_BIN_CONFIG_DIR}")

    message("Solution Source Dir:   ${${PREFIX}_CURRENT_SUBSOLUTION_SOURCE_DIR}")
    message("Solution Include Dir:  ${${PREFIX}_CURRENT_SUBSOLUTION_INCLUDE_DIR}")
    message("Solution Output Dir:   ${${PREFIX}_CURRENT_SUBSOLUTION_OUTPUT_DIR}")
endmacro()

macro(setup_vkimow_cmake_output_directories)
    message("\n=====SETUP OF CMAKE OUTPUT DIRECTORIES=====")
    set(ARGUMENT_PREFIX THIS)
    set(SINGLE_VALUES RUNTIME_DIR ARCHIVE_DIR LIBRARY_DIR)

    # parse
    cmake_parse_arguments(${ARGUMENT_PREFIX}
                        ""
                        "${SINGLE_VALUES}"
                        ""
                        ${ARGN})

    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    # set cmake directories
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${THIS_RUNTIME_DIR}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${THIS_ARCHIVE_DIR}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${THIS_LIBRARY_DIR}")

    message("CMake Runtime Dir:     ${THIS_RUNTIME_DIR}")
    message("CMake Archive Dir:     ${THIS_ARCHIVE_DIR}")
    message("CMake Output Dir:      ${THIS_LIBRARY_DIR}")
endmacro()

macro(setup_vkimow_global_properties)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")
endmacro()
