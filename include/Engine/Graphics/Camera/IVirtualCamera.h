#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Engine/Graphics/Camera/Projection.h"

namespace Engine::Graphics
{
    class IVirtualCamera
    {
    public:
        virtual const std::string &GetName() const = 0;
        virtual const glm::vec3 &GetPosition() const = 0;
        virtual const glm::vec3 &GetDirection() const = 0;
        virtual const glm::vec3 &GetUp() const = 0;
        virtual const Projection &GetProjection() const = 0;

    public:
        virtual glm::mat4 GetViewMatrix() = 0;
        virtual glm::mat4 GetProjectionMatrix() = 0;

    public:
        virtual bool ShouldUpdateView() const = 0;
        virtual bool ShouldUpdateProjection() const = 0;
    };
}