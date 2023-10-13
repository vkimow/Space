include("CPM")
set(FETCHCONTENT_BASE_DIR ${SPACE_VENDOR_DIR}/CPM)

#GLFW
message("\n=====ADDING GLFW=====")
if(EXISTS ${SPACE_VENDOR_DIR}/glfw)
    message("Found 'glfw' localy in the vendor directory")
    add_subdirectory(${SPACE_VENDOR_DIR}/glfw)
else()
    message("Adding 'glfw' throgh CPM")
    CPMAddPackage(
        NAME GLFW
        GITHUB_REPOSITORY glfw/glfw
        GIT_TAG 3.3.8
        OPTIONS
          "GLFW_BUILD_TESTS OFF"
          "GLFW_BUILD_EXAMPLES OFF"
          "GLFW_BULID_DOCS OFF"
    )
endif()

set_target_properties(glfw uninstall update_mappings PROPERTIES FOLDER Vendors/GLFW3)
# set_target_properties(boing gears heightmap particles sharing simple splitview wave offscreen PROPERTIES FOLDER Vendors/GLFW3/Examples)

#GLEW
message("\n=====ADDING GLEW=====")
if(EXISTS ${SPACE_VENDOR_DIR}/glew)
    message("Found 'glew' localy in vendor directory")
    add_subdirectory(${SPACE_VENDOR_DIR}/glew/build/cmake)
    target_include_directories(glew PUBLIC ${SPACE_VENDOR_DIR}/glew/include)
else()
    message("Adding 'glew' throgh CPM")
    CPMAddPackage("https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip")
    add_subdirectory(${glew_SOURCE_DIR}/build/cmake)
    target_include_directories(glew PUBLIC ${glew_SOURCE_DIR}/include)
endif()

set_target_properties(glew glew_s glewinfo visualinfo PROPERTIES FOLDER Vendors/GLEW2)

#GLM
message("\n=====ADDING GLM=====")
if(EXISTS ${SPACE_VENDOR_DIR}/glm)
    message("Found 'glm' localy in the vendor directory")
    add_subdirectory(${SPACE_VENDOR_DIR}/glm)
else()
    message("Adding 'glm' throgh CPM")
    CPMAddPackage("gh:g-truc/glm#0.9.9.8")
endif()

#GLI
message("\n=====ADDING GLI=====")
if(EXISTS ${SPACE_VENDOR_DIR}/gli)
    message("Found 'gli' localy in the vendor directory")
    add_subdirectory(${SPACE_VENDOR_DIR}/gli)
else()
    message("Adding 'gli' throgh CPM")
    CPMAddPackage("gh:g-truc/gli#0.8.2.0")
endif()

#ASSIMP
message("\n=====ADDING ASSIMP=====")
if(EXISTS ${SPACE_VENDOR_DIR}/assimp)
    message("Found 'assimp' localy in the vendor directory")
    add_subdirectory(${SPACE_VENDOR_DIR}/assimp)
else()
    message("Adding 'assimp' throgh CPM")
    CPMAddPackage("gh:assimp/assimp#v5.3.1")
endif()

set_target_properties(assimp unit zlibstatic UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER Vendors/ASSIMP)

#CATCH2
message("\n=====ADDING CATCH2=====")
if(EXISTS ${SPACE_VENDOR_DIR}/catch2)
    message("Found 'catch2' localy in the vendor directory")
    add_subdirectory(${SPACE_VENDOR_DIR}/catch2)
else()
    message("Adding 'catch2' throgh CPM")
    CPMAddPackage("gh:catchorg/Catch2#v3.4.0")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Catch2_SOURCE_DIR}/extras)
endif()

set_target_properties(Catch2 Catch2WithMain PROPERTIES FOLDER Vendors/CATCH2)

#SPDLOG
message("\n=====ADDING SPDLOG=====")
if(EXISTS ${SPACE_VENDOR_DIR}/spdlog)
    message("Found 'spdlog' localy in the vendor directory")
    add_subdirectory(${SPACE_VENDOR_DIR}/spdlog)
else()
    message("Adding 'spdlog' throgh CPM")
    CPMAddPackage("gh:gabime/spdlog#v1.12.0")
endif()

set_target_properties(spdlog PROPERTIES FOLDER Vendors/SPDLOG)

# CMAKE_MODULES_FROM_PACKAGES
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} PARENT_SCOPE)