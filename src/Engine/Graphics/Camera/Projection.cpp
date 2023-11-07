#include "Engine/Graphics/Camera/Projection.h"

namespace Engine::Graphics
{
    Projection::Projection()
        : window(nullptr)
        , fov(0.0f)
        , aspectRatio(0.0f)
        , near(0.0f)
        , far(0.0f)
        , setAspect(this, &Projection::SetAspect)
        , OnProjectionUpdated()
    {}


    Projection::Projection(Window *const window)
        : window(window)
        , fov(0.0f)
        , aspectRatio(static_cast<float>(window->GetResolution().x)/ static_cast<float>(window->GetResolution().y))
        , near(0.0f)
        , far(0.0f)
        , setAspect(this, &Projection::SetAspect)
        , OnProjectionUpdated()
    {
        window->AddListenerOnFramebufferResize(setAspect);
    }

    Projection::Projection(Window *const window, float fovDegrees, float near, float far)
        : window(window)
        , fov(glm::radians(fovDegrees))
        , aspectRatio(static_cast<float>(window->GetResolution().x) / static_cast<float>(window->GetResolution().y))
        , near(near)
        , far(far)
        , setAspect(this, &Projection::SetAspect)
        , OnProjectionUpdated()
    {
        window->AddListenerOnFramebufferResize(setAspect);
    }

    Projection::Projection(float fovDegrees, glm::vec2 framebuffer, float near, float far)
        : Projection(fovDegrees, framebuffer.x, framebuffer.y , near, far)
    {}

    Projection::Projection(float fovDegrees, float width, float height, float near, float far)
        : window(nullptr)
        , fov(glm::radians(fovDegrees))
        , aspectRatio(width/height)
        , near(near)
        , far(far)
        , setAspect(this, &Projection::SetAspect)
        , OnProjectionUpdated()
    {}

    Projection::Projection(const Projection &rhs)
        : window(rhs.window)
        , fov(rhs.fov)
        , aspectRatio(rhs.aspectRatio)
        , near(rhs.near)
        , far(rhs.far)
        , setAspect(this, &Projection::SetAspect)
        , OnProjectionUpdated()
    {
        if (window)
        {
            window->AddListenerOnFramebufferResize(setAspect);
        }
    }

    Projection::Projection(Projection &&rhs) noexcept
        : window(rhs.window)
        , fov(rhs.fov)
        , aspectRatio(rhs.aspectRatio)
        , near(rhs.near)
        , far(rhs.far)
        , setAspect(this, &Projection::SetAspect)
        , OnProjectionUpdated()
    {
        if (window)
        {
            window->AddListenerOnFramebufferResize(setAspect);
        }
    }

    Projection &Projection::operator=(const Projection &rhs)
    {
        fov = rhs.fov;
        aspectRatio = rhs.aspectRatio;
        near = rhs.near;
        far = rhs.far;
        OnProjectionUpdated();
        return *this;
    }

    Projection &Projection::operator=(Projection &&rhs) noexcept
    {
        fov = rhs.fov;
        aspectRatio = rhs.aspectRatio;
        near = rhs.near;
        far = rhs.far;
        OnProjectionUpdated();
        return *this;
    }


    Projection::~Projection()
    {
        if (window)
        {
            window->RemoveListenerOnFramebufferResize(setAspect);
        }
    }

    glm::mat4 Projection::GetProjectionMatrix() const
    {
        return glm::perspective(fov, aspectRatio, near, far);
    }

    float Projection::GetFov() const
    {
        return fov;
    }

    float Projection::GetFovInDegrees() const
    {
        return glm::degrees(fov);
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