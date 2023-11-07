#include <GL/glew.h>
#include "Engine/Graphics/Camera/VirtualCamera.h"
#include "Engine/Tools/Log/Logger.h"
#include "Engine/Main/Modules/TimeModule.h"
#include "glm/mat4x4.hpp"

namespace Engine::Graphics
{
    VirtualCamera::VirtualCamera(const std::string &name)
        : name(name)
        , position(0.0f)
        , up(glm::vec3(0.0f, 1.0f, 0.0f))
        , direction(glm::vec3(0.0f, 0.0f, 0.0f))
        , projection()
        , shouldUpdateView(true)
        , shouldUpdateProjection(true)
        , updateProjectionMatrix(this, &VirtualCamera::UpdateProjectionMatrix)
    {
        SetCallbacks();
    }

    VirtualCamera::VirtualCamera(const std::string &name, const Projection &projection)
        : name(name)
        , position(0.0f)
        , up(glm::vec3(0.0f, 1.0f, 0.0f))
        , direction(glm::vec3(0.0f, 0.0f, 0.0f))
        , projection(projection)
        , shouldUpdateView(true)
        , shouldUpdateProjection(true)
        , updateProjectionMatrix(this, &VirtualCamera::UpdateProjectionMatrix)
    {
        SetCallbacks();
    }

    VirtualCamera::VirtualCamera(const VirtualCamera &rhs)
        : name(rhs.name)
        , position(rhs.position)
        , up(rhs.up)
        , direction(rhs.direction)
        , projection(rhs.projection)
        , shouldUpdateView(rhs.shouldUpdateView)
        , shouldUpdateProjection(rhs.shouldUpdateProjection)
        , updateProjectionMatrix(this, &VirtualCamera::UpdateProjectionMatrix)
    {
        SetCallbacks();
    }

    VirtualCamera::VirtualCamera(VirtualCamera &&rhs) noexcept
        : name(rhs.name)
        , position(std::move(rhs.position))
        , up(std::move(rhs.up))
        , direction(std::move(rhs.direction))
        , projection(std::move(rhs.projection))
        , shouldUpdateView(rhs.shouldUpdateView)
        , shouldUpdateProjection(rhs.shouldUpdateProjection)
        , updateProjectionMatrix(this, &VirtualCamera::UpdateProjectionMatrix)
    {
        SetCallbacks();
    }

    VirtualCamera::~VirtualCamera()
    {
        ClearCallbacks();
    }

    const glm::vec3 &VirtualCamera::GetPosition() const
    {
        return position;
    }

    const glm::vec3 &VirtualCamera::GetDirection() const
    {
        return direction;
    }

    const glm::vec3 &VirtualCamera::GetUp() const
    {
        return up;
    }

    const Projection &VirtualCamera::GetProjection() const
    {
        return projection;
    }

    const std::string &VirtualCamera::GetName() const
    {
        return name;
    }

    glm::mat4 VirtualCamera::GetViewMatrix()
    {
        shouldUpdateView = false;
        return glm::lookAt(position, position + direction, up);
    }

    glm::mat4 VirtualCamera::GetProjectionMatrix()
    {
        shouldUpdateProjection = false;
        return projection.GetProjectionMatrix();
    }

    bool VirtualCamera::ShouldUpdateView() const
    {
        return shouldUpdateView;
    }

    bool VirtualCamera::ShouldUpdateProjection() const
    {
        return shouldUpdateProjection;
    }

    void VirtualCamera::SetPosition(const glm::vec3 &value)
    {
        position = value;
        shouldUpdateView = true;
    }

    void VirtualCamera::SetDirection(const glm::vec3 &value)
    {
        direction = glm::normalize(value);
        shouldUpdateView = true;
    }

    void VirtualCamera::SetTarget(const glm::vec3 &value)
    {
        direction = value - position;
        shouldUpdateView = true;
    }

    void VirtualCamera::SetUp(const glm::vec3 &value)
    {
        up = glm::normalize(value);
        shouldUpdateView = true;
    }

    void VirtualCamera::SetProjection(const Projection &value)
    {
        ClearCallbacks();
        projection = value;
        SetCallbacks();
        shouldUpdateProjection = true;
    }

    void VirtualCamera::SetProjection(Projection &&value)
    {
        ClearCallbacks();
        projection = std::move(value);
        SetCallbacks();
        shouldUpdateProjection = true;
    }

    void VirtualCamera::SetFov(float value)
    {
        projection.SetFov(value);
    }

    void VirtualCamera::SetFovInDegrees(float value)
    {
        projection.SetFovInDegrees(value);
    }

    void VirtualCamera::SetAspect(float value)
    {
        projection.SetAspect(value);
    }

    void VirtualCamera::SetNear(float value)
    {
        projection.SetNear(value);
    }

    void VirtualCamera::SetFar(float value)
    {
        projection.SetFar(value);
    }

    void VirtualCamera::UpdateProjectionMatrix()
    {
        shouldUpdateProjection = true;
    }

    void VirtualCamera::SetCallbacks()
    {
        projection.AddListenerOnProjectionUpdated(updateProjectionMatrix);
    }

    void VirtualCamera::ClearCallbacks()
    {
        projection.RemoveListenerOnProjectionUpdated(updateProjectionMatrix);
    }
}