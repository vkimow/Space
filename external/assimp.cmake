message("\n=====ADDING ASSIMP=====")
string(TIMESTAMP BEFORE "%s")

set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_SAMPLES OFF)
set(ASSIMP_BUILD_TESTS OFF)

if(EXISTS ${SPACE_EXTERNAL_DIR}/assimp)
    message(STATUS "Found 'assimp' localy in the external directory")
    add_subdirectory(${SPACE_EXTERNAL_DIR}/assimp)
else()
    message(STATUS "Adding 'assimp' throgh CPM")
    CPMAddPackage("gh:assimp/assimp#v5.3.1")
endif()

set_target_properties(assimp zlibstatic UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER Externals/ASSIMP)

string(TIMESTAMP AFTER "%s")
math(EXPR DELTA "${AFTER} - ${BEFORE}")
message(STATUS "TIME: ${DELTA}s")