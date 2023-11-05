#pragma once
#include <glm/glm.hpp>
#include "Engine/Graphics/Elements/Shader.h"

namespace Engine::Graphics
{
    class ITexture
    {
    public:
        virtual void Use(Shader *shader) = 0;
    };
}