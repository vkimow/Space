#include "Engine/Graphics/Projection.h"

namespace Engine::Graphics
{
    Projection::Projection()
        : fovDegrees(0.0f)
        , aspectRatio(0.0f)
        , near(0.0f)
        , far(0.0f)
        , OnProjectionUpdated()
    {}

    Projection::Projection(float fovDegrees, glm::vec2 framebuffer, float near, float far)
        : Projection(fovDegrees, framebuffer.x, framebuffer.y , near, far)
    {}

    Projection::Projection(float fovDegrees, glm::ivec2 framebuffer, float near, float far)
        : Projection(fovDegrees, static_cast<float>(framebuffer.x), static_cast<float>(framebuffer.y), near, far)
    {}

    Projection::Projection(float fovDegrees, float width, float height, float near, float far)
        : Projection(fovDegrees, width / height, near, far)
    {}

    Projection::Projection(float fovDegrees, float aspectRatio, float near, float far)
        : fovDegrees(fovDegrees)
        , aspectRatio(aspectRatio)
        , near(near)
        , far(far)
        , OnProjectionUpdated()
    {}

    Projection::Projection(const Projection &rhs)
        : fovDegrees(rhs.fovDegrees)
        , aspectRatio(rhs.aspectRatio)
        , near(rhs.near)
        , far(rhs.far)
        , OnProjectionUpdated()
    {}

    Projection::Projection(Projection &&rhs) noexcept
        : fovDegrees(rhs.fovDegrees)
        , aspectRatio(rhs.aspectRatio)
        , near(rhs.near)
        , far(rhs.far)
        , OnProjectionUpdated()
    {}

    Projection &Projection::operator=(const Projection &rhs)
    {
        fovDegrees = rhs.fovDegrees;
        aspectRatio = rhs.aspectRatio;
        near = rhs.near;
        far = rhs.far;
        OnProjectionUpdated();
        return *this;
    }

    Projection &Projection::operator=(Projection &&rhs) noexcept
    {
        fovDegrees = rhs.fovDegrees;
        aspectRatio = rhs.aspectRatio;
        near = rhs.near;
        far = rhs.far;
        OnProjectionUpdated();
        return *this;
    }

    Projection::~Projection()
    {}

    glm::mat4 Projection::GetProjectionMatrix() const
    {
        return glm::perspective(glm::radians(fovDegrees), aspectRatio, near, far);
    }

    float Projection::GetFovDegrees() const
    {
        return fovDegrees;
    }

    float Projection::GetAspectRatio() const
    {
        return aspectRatio;
    }

    float Projection::GetNear() const
    {
        return near;
    }

    float Projection::GetFar() const
    {
        return far;
    }
}