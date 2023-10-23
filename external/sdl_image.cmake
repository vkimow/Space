message("\n=====ADDING SDL_IMAGE=====")
string(TIMESTAMP BEFORE "%s")

set(SDL2IMAGE_INSTALL OFF)
set(SDL2IMAGE_SAMPLES OFF)
set(SDL2IMAGE_VENDORED ON)
set(SDL2IMAGE_BUILD_SHARED_LIBS OFF)
set(GIT_SUBMODULES_RECURSE ON)

if(EXISTS ${SPACE_EXTERNAL_DIR}/sdl_image)
    message(STATUS "Found 'sdl_image' localy in the external directory")
    add_subdirectory(${SPACE_EXTERNAL_DIR}/sdl_image)
else()
    message(STATUS "Adding 'sdl_image' throgh CPM")
    CPMAddPackage("gh:libsdl-org/SDL_image#release-2.6.3")
endif()

target_include_directories(SDL2_image PRIVATE SDL2_INCLUDE_DIR)
set_target_properties(SDL2_image PROPERTIES FOLDER Externals/SDL2)

string(TIMESTAMP AFTER "%s")
math(EXPR DELTA "${AFTER} - ${BEFORE}")
message(STATUS "TIME: ${DELTA}s")