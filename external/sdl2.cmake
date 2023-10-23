message("\n=====ADDING SDL2=====")
string(TIMESTAMP BEFORE "%s")

set(SDL2_DISABLE_INSTALL ON)
set(SDL_SHARED OFF)
set(SDL_STATIC ON)
set(SDL_STATIC_PIC ON)
set(SDL_WERROR OFF)
set(SDL_TEST OFF)
set(SDL_TESTS OFF)

if(EXISTS ${SPACE_EXTERNAL_DIR}/sdl2)
    message(STATUS "Found 'sdl2' localy in the external directory")
    add_subdirectory(${SPACE_EXTERNAL_DIR}/sdl2)
    set(SDL2_SOURCE_DIR ${SPACE_EXTERNAL_DIR}/sdl2)
else()
    message(STATUS "Adding 'sdl2' throgh CPM")
    CPMAddPackage("gh:libsdl-org/SDL#release-2.28.4")
endif()


set(SDL2_INCLUDE_DIR ${SDL2_SOURCE_DIR}/include)
set_target_properties(sdl_headers_copy SDL2main SDL2-static PROPERTIES FOLDER Externals/SDL2)

string(TIMESTAMP AFTER "%s")
math(EXPR DELTA "${AFTER} - ${BEFORE}")
message(STATUS "TIME: ${DELTA}s")