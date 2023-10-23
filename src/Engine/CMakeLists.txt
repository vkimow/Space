set_vkimow_subsolution(Engine)
add_subdirectory(Tools)
add_subdirectory(Objects)
add_subdirectory(Input)
add_subdirectory(Audio)
add_subdirectory(Graphics)
add_subdirectory(Main)


if(SPACE_ENABLE_TESTS)
    add_vkimow_custom_build_target(
        NAME            Main_Tests
        SOLUTION_FOLDER ${SPACE_CURRENT_SUBSOLUTION_TESTS_RELATIVE_PATH}
        DEPENDENCIES    Tools_Tests
                        Objects_Tests
                        Input_Tests
                        Graphics_Tests
                        Audio_Tests
    )
endif()