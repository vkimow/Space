message("\n=====ADDING IMGUI=====")
string(TIMESTAMP BEFORE "%s")

option(IMGUI_BUILD_EXAMPLES "Build imgui examples" ON)
option(IMGUI_BUILD_GLFW_EXAMPLE "Build glfw imgui example" ON)
option(IMGUI_BUILD_SDL3_EXAMPLE "Build sdl3 imgui example" OFF)


if(EXISTS ${SPACE_EXTERNAL_DIR}/imgui)
    message(STATUS "Found 'imgui' localy in the external directory")
    set(IMGUI_SOURCE_DIR ${SPACE_EXTERNAL_DIR}/imgui)
else()
    message(STATUS "Adding 'imgui' throgh CPM")
    CPMAddPackage("gh:ocornut/imgui#v1.89.9")
    set(IMGUI_SOURCE_DIR ${imgui_SOURCE_DIR})
endif()

set(IMGUI_SOURCES
    ${IMGUI_SOURCE_DIR}/imconfig.h
    ${IMGUI_SOURCE_DIR}/imgui.h
    ${IMGUI_SOURCE_DIR}/imgui.cpp
    ${IMGUI_SOURCE_DIR}/imgui_draw.cpp
    ${IMGUI_SOURCE_DIR}/imgui_internal.h
    ${IMGUI_SOURCE_DIR}/imgui_widgets.cpp
    ${IMGUI_SOURCE_DIR}/imstb_rectpack.h
    ${IMGUI_SOURCE_DIR}/imstb_textedit.h
    ${IMGUI_SOURCE_DIR}/imstb_truetype.h
    ${IMGUI_SOURCE_DIR}/imgui_tables.cpp
    ${IMGUI_SOURCE_DIR}/imgui_demo.cpp
    ${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    #${IMGUI_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    #${IMGUI_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

add_library(imgui STATIC)
target_sources(imgui PRIVATE ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${IMGUI_SOURCE_DIR} ${IMGUI_SOURCE_DIR}/backends)
#target_link_libraries(imgui PRIVATE glfw SDL2-static SDL2main)
target_link_libraries(imgui PRIVATE glfw)
set_target_properties(imgui PROPERTIES FOLDER Externals/IMGUI)

if (IMGUI_BUILD_EXAMPLES)
    message(STATUS "Building examples")
    set(IMGUI_EXAMPLES_DIR ${IMGUI_SOURCE_DIR}/examples)
    set(IMGUI_GLFW_EXAMPLE_DIR ${IMGUI_EXAMPLES_DIR}/example_glfw_opengl3)
    set(IMGUI_SDL3_EXAMPLE_DIR ${IMGUI_EXAMPLES_DIR}/example_sdl3_opengl3)

    set(IMGUI_GLFW_EXAMPLE_SOURCES ${IMGUI_GLFW_EXAMPLE_DIR}/main.cpp)
    set(IMGUI_SDL3_EXAMPLE_SOURCES ${IMGUI_SDL3_EXAMPLE_DIR}/main.cpp)

    if (IMGUI_BUILD_GLFW_EXAMPLE)
        message(STATUS "Building glfw imgui example")
        add_executable(imgui_glfw_example)
        target_sources(imgui_glfw_example PRIVATE ${IMGUI_GLFW_EXAMPLE_SOURCES})
        target_link_libraries(imgui_glfw_example PRIVATE imgui glfw)
        set_target_properties(imgui_glfw_example PROPERTIES FOLDER Externals/IMGUI/Examples)
    endif()

    if (IMGUI_BUILD_SDL3_EXAMPLE)
        message(STATUS "Building sdl3 imgui example")
        add_executable(imgui_sdl3_example)
        target_sources(imgui_sdl3_example PRIVATE ${IMGUI_SDL3_EXAMPLE_SOURCES})
        target_link_libraries(imgui_sdl3_example PRIVATE imgui glfw SDL2-static SDL2main)
        set_target_properties(imgui_sdl3_example PROPERTIES FOLDER Externals/IMGUI/Examples)
    endif()
endif()

string(TIMESTAMP AFTER "%s")
math(EXPR DELTA "${AFTER} - ${BEFORE}")
message(STATUS "TIME: ${DELTA}s")