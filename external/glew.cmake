message("\n=====ADDING GLEW=====")
string(TIMESTAMP BEFORE "%s")

set(BUILD_SHARED_LIBS OFF)
set(BUILD_UTILS OFF)
set(BUILD_32_BIT OFF)
set(BUILD_SINGLE_CONTEXT OFF)
set(GLEW_USE_STATIC_LIBS ON)

if(EXISTS ${SPACE_EXTERNAL_DIR}/glew)
    message(STATUS "Found 'glew' localy in external directory")
    add_subdirectory(${SPACE_EXTERNAL_DIR}/glew/build/cmake)
    set(GLEW_SOURCE_DIR ${SPACE_EXTERNAL_DIR}/glew)
else()
    message(STATUS "Adding 'glew' throgh CPM")
    CPMAddPackage(
        NAME "glew"
        URL "https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip"
        SOURCE_SUBDIR "build/cmake"
    )
    set(GLEW_SOURCE_DIR ${glew_SOURCE_DIR})
endif()

set(GLEW_LIBRARIES glew glew_s)
foreach(lib ${GLEW_LIBRARIES})
    target_include_directories(${lib} PUBLIC
        $<BUILD_INTERFACE:${GLEW_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
endforeach()
set_target_properties(${GLEW_LIBRARIES} PROPERTIES FOLDER Externals/GLEW2)
set_vkimow_target_output_dir(   TARGET ${GLEW_LIBRARIES}
                                RUNTIME_DIR ${SPACE_BIN_CONFIG_DIR}
                                ARCHIVE_DIR ${SPACE_LIB_CONFIG_DIR}
                                LIBRARY_DIR ${SPACE_LIB_CONFIG_DIR}
)
string(TIMESTAMP AFTER "%s")
math(EXPR DELTA "${AFTER} - ${BEFORE}")
message(STATUS "TIME: ${DELTA}s")