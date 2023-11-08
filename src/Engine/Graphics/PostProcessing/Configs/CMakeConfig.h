#ifndef SPACE_ENGINE_GRAPHICS_POSTPROCESSING_CONFIGS_CMAKE
#define SPACE_ENGINE_GRAPHICS_POSTPROCESSING_CONFIGS_CMAKE

#include <string>

namespace Engine::Graphics::Configs
{
    const std::string BLUR_DOWNSAMPLE_FRAG_RELATIVE_PATH = "Shaders/PostProcessing/blur_downsample.frag";
    const std::string BLUR_UPSAMPLE_FRAG_RELATIVE_PATH = "Shaders/PostProcessing/blur_upsample.frag";
    const std::string BRIGHTNESS_FRAG_RELATIVE_PATH = "Shaders/PostProcessing/brightness.frag";
    const std::string COLOR_CORRECTION_FRAG_RELATIVE_PATH = "Shaders/PostProcessing/color_correction.frag";
    const std::string POSTPROCESSING_FRAG_RELATIVE_PATH = "Shaders/PostProcessing/postprocessing.frag";
    const std::string BLUR_DOWNSAMPLE_VERT_RELATIVE_PATH = "Shaders/PostProcessing/blur_downsample.vert";
    const std::string BLUR_UPSAMPLE_VERT_RELATIVE_PATH = "Shaders/PostProcessing/blur_upsample.vert";
    const std::string BRIGHTNESS_VERT_RELATIVE_PATH = "Shaders/PostProcessing/brightness.vert";
    const std::string COLOR_CORRECTION_VERT_RELATIVE_PATH = "Shaders/PostProcessing/color_correction.vert";
    const std::string POSTPROCESSING_VERT_RELATIVE_PATH = "Shaders/PostProcessing/postprocessing.vert";
}

#endif
