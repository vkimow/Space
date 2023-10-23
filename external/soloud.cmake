message("\n=====ADDING SOLOUD=====")
string(TIMESTAMP BEFORE "%s")

set(SOLOUD_BACKEND_WASAPI ON)
set(SOLOUD_BACKEND_SDL2 OFF)
set(SOLOUD_BUILD_DEMOS OFF)
set(SOLOUD_DYNAMIC OFF)
set(SOLOUD_STATIC ON)

if(EXISTS ${SPACE_EXTERNAL_DIR}/soloud)
    message(STATUS "Found 'soloud' localy in the external directory")
    add_subdirectory(${SPACE_EXTERNAL_DIR}/soloud/contrib)
    set(SOLOUD_SOURCE_DIR ${SPACE_EXTERNAL_DIR}/soloud)
else()
    message(STATUS "Adding 'soloud' throgh CPM")
    CPMAddPackage(
        NAME soloud
        GITHUB_REPOSITORY jarikomppa/soloud
        GIT_TAG RELEASE_20200207
        SOURCE_SUBDIR "contrib"
    )
    set(SOLOUD_SOURCE_DIR ${soloud_SOURCE_DIR})
endif()

set_target_properties(soloud PROPERTIES FOLDER Externals/SOLOUD)
target_include_directories(soloud
    PUBLIC
    $<BUILD_INTERFACE:${SOLOUD_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

string(TIMESTAMP AFTER "%s")
math(EXPR DELTA "${AFTER} - ${BEFORE}")
message(STATUS "TIME: ${DELTA}s")