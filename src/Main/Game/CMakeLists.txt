project(Game CXX)

#directories
set_vkimow_default_target_dirs(
    TARGET ${PROJECT_NAME}
    SOURCE_DIR ${SPACE_CURRENT_SUBSOLUTION_SOURCE_DIR}/${PROJECT_NAME}
    OUTPUT_DIR ${SPACE_BIN_CONFIG_DIR}
)

set_vkimow_custom_target_dir(
    TARGET ${PROJECT_NAME}
    VARIABLE Shaders
    DIR ${SPACE_CURRENT_SOURCE_DIR}/Shaders
)

set_vkimow_custom_target_dir(
    TARGET ${PROJECT_NAME}
    VARIABLE Configs
    DIR ${SPACE_CURRENT_SOURCE_DIR}/Configs
)

#variables
set_vkimow_target_variable(
    TARGET ${PROJECT_NAME}
    VARIABLE SHADERS_RELATIVE_PATH
    VALUE "Shaders/${PROJECT_NAME}"
)

#configs
process_vkimow_configure_folder(
    FILES_DIR ${SPACE_CURRENT_CONFIGS_DIR}
    OUTPUT_DIR ${SPACE_CURRENT_CONFIGS_DIR}
    EXTENSIONS .in
)

#files
find_vkimow_auto_files(
    TARGET ${PROJECT_NAME}
    ROOT_DIR ${SPACE_CURRENT_SOURCE_DIR}
    EXCLUDE_DIRS ${SPACE_CURRENT_SHADERS_DIR}
    VARIABLE Sources
    EXTENSIONS .cpp .h .in
)

find_vkimow_auto_files(
    TARGET ${PROJECT_NAME}
    ROOT_DIR ${SPACE_CURRENT_SHADERS_DIR}
    VARIABLE Shaders
    EXTENSIONS .frag .vert .geom
)

set_vkimow_target_files(
    VARIABLE Sources
    TARGET ${PROJECT_NAME}
    FILES_DIR ${SPACE_CURRENT_SOURCE_DIR}
    FILES ${SPACE_CURRENT_AUTO_SOURCES} ${SPACE_CURRENT_AUTO_SHADERS}
    )


# executable
add_vkimow_executable(
    NAME ${PROJECT_NAME}
    SOLUTION_FOLDER ${SPACE_CURRENT_SUBSOLUTION_RELATIVE_PATH}
    SOURCES ${SPACE_CURRENT_SOURCES}
    PRIVATE_LINK_LIBS space::engine::main
)

# copy targets
add_vkimow_copy_target(
    NAME CopyShaders
    INPUT_DIR ${SPACE_CURRENT_SHADERS_DIR}
    OUTPUT_DIR ${SPACE_BIN_CONFIG_DIR}/${SPACE_CURRENT_SHADERS_RELATIVE_PATH}
    REQUIRED_FOR ${PROJECT_NAME}
    COMMENT "Copying shaders into bin directory"
)