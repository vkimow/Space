project(Graphics_Tests CXX)

#directories
set_vkimow_default_target_dirs(
    TARGET ${PROJECT_NAME}
    SOURCE_DIR ${SPACE_CURRENT_TESTS_DIR}
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

# executable
add_vkimow_executable(
    NAME ${PROJECT_NAME}
    SOLUTION_FOLDER ${SPACE_CURRENT_SUBSOLUTION_TESTS_RELATIVE_PATH}
    SOURCES ${SPACE_CURRENT_SOURCES}
    PRIVATE_LINK_LIBS   space::engine::graphics
                        Catch2::Catch2WithMain
    PRIVATE_INCLUDE_DIRS ${SPACE_INCLUDE_DIR}
)

catch_discover_tests(${PROJECT_NAME})