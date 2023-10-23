message("\n=====ADDING CATCH2=====")
string(TIMESTAMP BEFORE "%s")

if(EXISTS ${SPACE_EXTERNAL_DIR}/catch2)
    message(STATUS "Found 'catch2' localy in the external directory")
    add_subdirectory(${SPACE_EXTERNAL_DIR}/catch2)
    set(CATCH2_SOURCE_DIR ${SPACE_EXTERNAL_DIR}/catch2)
else()
    message(STATUS "Adding 'catch2' throgh CPM")
    CPMAddPackage("gh:catchorg/Catch2#v3.4.0")
    set(CATCH2_SOURCE_DIR ${Catch2_SOURCE_DIR})
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CATCH2_SOURCE_DIR}/extras)
set_target_properties(Catch2 Catch2WithMain PROPERTIES FOLDER Externals/CATCH2)

string(TIMESTAMP AFTER "%s")
math(EXPR DELTA "${AFTER} - ${BEFORE}")
message(STATUS "TIME: ${DELTA}s")