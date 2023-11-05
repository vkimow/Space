#include "Shaders/ShaderCreator.h"
#include "Shaders/Configs/CMakeConfig.h"
#include "Engine/Tools/Other/Files.h"
#include <unordered_set>

namespace Main::Shaders
{
    static std::unordered_set<Engine::GraphicsModule *> initializedGraphics;

    void InitializeShaders(Engine::GraphicsModule *graphics)
    {
        if (!initializedGraphics.contains(graphics))
        {
            graphics->GetContainer()->AddShader("MainShader", Configs::SHADER_VERT_RELATIVE_PATH, Configs::SHADER_FRAG_RELATIVE_PATH);
            initializedGraphics.insert(graphics);
        }
    }
}