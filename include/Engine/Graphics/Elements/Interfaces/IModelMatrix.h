#pragma once

#include "Engine/Graphics/Elements/Shader.h"
#include <glm/glm.hpp>

namespace Engine::Graphics
{
    class IModelMatrix
    {
    public:
        virtual const glm::mat4 &GetModelMatrix() const = 0;

    public:
        virtual void Use(Shader* shader) = 0;
    };
}