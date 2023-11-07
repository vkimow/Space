cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# project
project(Space CXX)

# options
option(SPACE_ENABLE_TESTS "Enabling tests targets" OFF)

# include
set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
include(VkimowFunctions)

# setup environment
setup_vkimow_global_variable_prefix(UPPERCASE_PREFIX SPACE)
setup_vkimow_configurations()
setup_vkimow_global_directories()
setup_vkimow_global_properties()
setup_vkimow_cmake_output_directories(
   RUNTIME_DIR ${SPACE_BIN_CONFIG_DIR}
   ARCHIVE_DIR ${SPACE_LIB_CONFIG_DIR}
   LIBRARY_DIR ${SPACE_LIB_CONFIG_DIR}
)


# setup external libs
add_subdirectory(external)

# enable CTest & Catch
if(SPACE_ENABLE_TESTS)
   message("Tests are enabled")
   include(CTest)
   enable_testing()
   include(Catch)
endif()

# add main project
add_compile_definitions(GLEW_STATIC)
add_subdirectory(src/Engine Engine)
add_subdirectory(src/Main Main)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
   set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT App)
endif()
