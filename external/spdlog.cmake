message("\n=====ADDING SPDLOG=====")
string(TIMESTAMP BEFORE "%s")

if(EXISTS ${SPACE_EXTERNAL_DIR}/spdlog)
    message(STATUS "Found 'spdlog' localy in the external directory")
    add_subdirectory(${SPACE_EXTERNAL_DIR}/spdlog)
else()
    message(STATUS "Adding 'spdlog' throgh CPM")
    CPMAddPackage("gh:gabime/spdlog#v1.12.0")
endif()

set_target_properties(spdlog PROPERTIES FOLDER Externals/SPDLOG)

string(TIMESTAMP AFTER "%s")
math(EXPR DELTA "${AFTER} - ${BEFORE}")
message(STATUS "TIME: ${DELTA}s")