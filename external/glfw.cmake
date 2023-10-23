message("\n=====ADDING GLFW=====")
string(TIMESTAMP BEFORE "%s")

set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BULID_DOCS OFF)

if(EXISTS ${SPACE_EXTERNAL_DIR}/glfw)
    message(STATUS "Found 'glfw' localy in the external directory")
    add_subdirectory(${SPACE_EXTERNAL_DIR}/glfw)
else()
    message(STATUS "Adding 'glfw' throgh CPM")
    CPMAddPackage("gh:glfw/glfw#3.3.8")
endif()

set_target_properties(glfw uninstall update_mappings PROPERTIES FOLDER Externals/GLFW3)
# set_target_properties(boing gears heightmap particles sharing simple splitview wave offscreen PROPERTIES FOLDER Externals/GLFW3/Examples)

string(TIMESTAMP AFTER "%s")
math(EXPR DELTA "${AFTER} - ${BEFORE}")
message(STATUS "TIME: ${DELTA}s")
