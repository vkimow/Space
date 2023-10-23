message("\n=====ADDING GLM=====")
string(TIMESTAMP BEFORE "%s")

set(GLM_TEST_ENABLE OFF)
set(BUILD_STATIC_LIBS OFF)
set(BUILD_SHARED_LIBS OFF)


if(EXISTS ${SPACE_EXTERNAL_DIR}/glm)
    message(STATUS "Found 'glm' localy in the external directory")
    add_subdirectory(${SPACE_EXTERNAL_DIR}/glm)
else()
    message(STATUS "Adding 'glm' throgh CPM")
    CPMAddPackage("gh:g-truc/glm#0.9.9.8")
endif()


string(TIMESTAMP AFTER "%s")
math(EXPR DELTA "${AFTER} - ${BEFORE}")
message(STATUS "TIME: ${DELTA}s")