project(Main CXX)

#directories
set_vkimow_default_target_dirs(
    TARGET ${PROJECT_NAME}
    SOURCE_DIR ${SPACE_CURRENT_SUBSOLUTION_SOURCE_DIR}/${PROJECT_NAME}
    INCLUDE_DIR ${SPACE_CURRENT_SUBSOLUTION_INCLUDE_DIR}/${PROJECT_NAME}
    RUNTIME_DIR ${SPACE_BIN_CONFIG_DIR}
    ARCHIVE_DIR ${SPACE_LIB_CONFIG_DIR}
    LIBRARY_DIR ${SPACE_LIB_CONFIG_DIR}
)

#files
find_vkimow_auto_files(
    TARGET ${PROJECT_NAME}
    ROOT_DIR ${SPACE_CURRENT_SOURCE_DIR}
    VARIABLE Sources
    EXTENSIONS .cpp .h
)

set_vkimow_target_files(
    VARIABLE Sources
    TARGET ${PROJECT_NAME}
    FILES_DIR ${SPACE_CURRENT_SOURCE_DIR}
    FILES ${SPACE_CURRENT_AUTO_SOURCES}
    )

find_vkimow_auto_files(
    TARGET ${PROJECT_NAME}
    ROOT_DIR ${SPACE_CURRENT_INCLUDE_DIR}
    VARIABLE Public_Headers
    EXTENSIONS .h
)

set_vkimow_target_files(
    VARIABLE Public_Headers
    TARGET ${PROJECT_NAME}
    FILES_DIR ${SPACE_CURRENT_INCLUDE_DIR}
    FILES ${SPACE_CURRENT_AUTO_PUBLIC_HEADERS}
    )

# executable
add_vkimow_library(
    NAME ${PROJECT_NAME}
    SOLUTION_FOLDER ${SPACE_CURRENT_SUBSOLUTION_RELATIVE_PATH}
    SOURCES ${SPACE_CURRENT_SOURCES} ${SPACE_CURRENT_PUBLIC_HEADERS}
    PUBLIC_LINK_LIBS    glew_s
                        glfw
                        glm
                        space::engine::tools
                        space::engine::window
                        space::engine::objects
                        space::engine::ui
                        space::engine::input
                        space::engine::audio
                        space::engine::graphics
                        space::engine::essentials

    PUBLIC_INCLUDE_DIRS ${SPACE_INCLUDE_DIR}
)