#pragma once
#include <glm/glm.hpp>
#include "Engine/Graphics/Elements/Shader.h"

namespace Engine::Graphics
{
    class IMaterial
    {
    public:
        virtual void Use(Shader *shader) = 0;
        virtual void Disable(Shader *shader) = 0;
    };
}