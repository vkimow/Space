project(Game CXX)

#directories
set_vkimow_default_target_dirs(
    TARGET ${PROJECT_NAME}
    SOURCE_DIR ${SPACE_CURRENT_SUBSOLUTION_SOURCE_DIR}/${PROJECT_NAME}
    RUNTIME_DIR ${SPACE_BIN_CONFIG_DIR}
    ARCHIVE_DIR ${SPACE_LIB_CONFIG_DIR}
    LIBRARY_DIR ${SPACE_LIB_CONFIG_DIR}
)

#files
find_vkimow_auto_files(
    TARGET ${PROJECT_NAME}
    ROOT_DIR ${SPACE_CURRENT_SOURCE_DIR}
    EXCLUDE_DIRS ${SPACE_CURRENT_SHADERS_DIR}
    VARIABLE Sources
    EXTENSIONS .cpp .h
)

set_vkimow_target_files(
    VARIABLE Sources
    TARGET ${PROJECT_NAME}
    FILES_DIR ${SPACE_CURRENT_SOURCE_DIR}
    FILES ${SPACE_CURRENT_AUTO_SOURCES}
)


add_vkimow_library(
    NAME ${PROJECT_NAME}
    SOLUTION_FOLDER ${SPACE_CURRENT_SUBSOLUTION_RELATIVE_PATH}
    SOURCES ${SPACE_CURRENT_SOURCES}
    PUBLIC_LINK_LIBS    space::engine::main
                        space::main::shaders
                        space::main::editor
                        space::main::space
    PRIVATE_INCLUDE_DIRS ${SPACE_CURRENT_SUBSOLUTION_SOURCE_DIR}
)