#include "Engine/Graphics/Projection.h"
#include "Engine/Main/Window.h"

namespace Engine::Graphics
{
    Projection::Projection()
        : window(nullptr)
        , fovDegrees(0.0f)
        , aspectRatio(0.0f)
        , near(0.0f)
        , far(0.0f)
        , updateAspectByFramebuffer(this, &Projection::UpdateAspectByFramebuffer)
        , projection()
    {}

    Projection::Projection(Window *const window, float fovDegrees, float near, float far)
        : Projection(window, fovDegrees, window->GetResolution(), near, far)
    {}

    Projection::Projection(Window *const window, float fovDegrees, glm::vec2 framebuffer, float near, float far)
        : Projection(window, fovDegrees, framebuffer.x, framebuffer.y , near, far)
    {}

    Projection::Projection(Window *const window, float fovDegrees, glm::ivec2 framebuffer, float near, float far)
        : Projection(window, fovDegrees, static_cast<float>(framebuffer.x), static_cast<float>(framebuffer.y), near, far)
    {}

    Projection::Projection(Window *const window, float fovDegrees, float width, float height, float near, float far)
        : Projection(window, fovDegrees, width / height, near, far)
    {}

    Projection::Projection(Window *const window, float fovDegrees, float aspectRatio, float near, float far)
        : window(window)
        , fovDegrees(fovDegrees)
        , aspectRatio(aspectRatio)
        , near(near)
        , far(far)
        , updateAspectByFramebuffer(this, &Projection::UpdateAspectByFramebuffer)
    {
        window->AddListenerOnFramebufferResize(updateAspectByFramebuffer);
        UpdateProjection();
    }

    Projection::Projection(Projection &&rhs) noexcept
        : window(rhs.window)
        , fovDegrees(rhs.fovDegrees)
        , aspectRatio(rhs.aspectRatio)
        , near(rhs.near)
        , far(rhs.far)
        , updateAspectByFramebuffer(this, &Projection::UpdateAspectByFramebuffer)
    {
        UpdateProjection();
        rhs.window = nullptr;
        if (window)
        {
            window->RemoveListenerOnFramebufferResize(rhs.updateAspectByFramebuffer);
            window->AddListenerOnFramebufferResize(updateAspectByFramebuffer);
        }
    }

    Projection &Projection::operator=(Projection &&rhs) noexcept
    {
        Window *previousWindow = this->window;
        this->window = rhs.window;
        fovDegrees = rhs.fovDegrees;
        aspectRatio = rhs.aspectRatio;
        near = rhs.near;
        far = rhs.far;
        UpdateProjection();

        rhs.window = nullptr;
        if (window)
        {
            window->RemoveListenerOnFramebufferResize(rhs.updateAspectByFramebuffer);
        }
        if (previousWindow != window)
        {
            if (previousWindow)
            {
                previousWindow->RemoveListenerOnFramebufferResize(updateAspectByFramebuffer);
            }
            if (window)
            {
                window->AddListenerOnFramebufferResize(updateAspectByFramebuffer);
            }
        }

        return *this;
    }

    Projection::~Projection()
    {
        if (window)
        {
            window->RemoveListenerOnFramebufferResize(updateAspectByFramebuffer);
        }
    }

    glm::mat4 Projection::GetProjectionMatrix() const
    {
        return projection;
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

    void Projection::UpdateProjection()
    {
        projection = glm::perspective(glm::radians(fovDegrees), aspectRatio, near, far);
    }
}