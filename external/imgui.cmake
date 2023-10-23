message("\n=====ADDING IMGUI=====")
string(TIMESTAMP BEFORE "%s")

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
target_link_libraries(imgui PRIVATE glfw SDL2-static)
set_target_properties(imgui PROPERTIES FOLDER Externals/IMGUI)

string(TIMESTAMP AFTER "%s")
math(EXPR DELTA "${AFTER} - ${BEFORE}")
message(STATUS "TIME: ${DELTA}s")