#include "Engine/Graphics/Camera/Camera.h"
#include "Engine/Main/Modules/TimeModule.h"
#include "Engine/Tools/Log/Logger.h"

namespace Engine::Graphics
{
    Camera::Camera(const std::string &name, glm::vec3 position)
        : Camera(name, position, Projection())
    {}

    Camera::Camera(const std::string &name, const Projection &projection)
        : Camera(name, glm::vec3(0.0f), projection)
    {}

    Camera::Camera(const std::string &name, glm::vec3 position, const Projection &projection)
        : name(name)
        , position(position)
        , up(glm::vec3(0.0f, 1.0f, 0.0f))
        , front(glm::vec3(0.0f, 0.0f, -1.0f))
        , projection(projection)
        , viewMatrix()
        , projectionMatrix()
        , viewProjectionMatrix()
        , isViewUpdated(false)
        , isProjectionUpdated(false)
        , isViewProjectionUpdated(false)
        , updateProjectionMatrix(this, &Camera::UpdateProjectionMatrix)
    {
        SetCallbacks();
    }

    Camera::Camera(const Camera &rhs)
        : name(rhs.name)
        , position(rhs.position)
        , up(rhs.up)
        , front(rhs.front)
        , projection(rhs.projection)
        , viewMatrix(rhs.viewMatrix)
        , projectionMatrix(rhs.projectionMatrix)
        , viewProjectionMatrix(rhs.viewProjectionMatrix)
        , isViewUpdated(rhs.isViewUpdated)
        , isProjectionUpdated(rhs.isProjectionUpdated)
        , isViewProjectionUpdated(rhs.isViewProjectionUpdated)
        , updateProjectionMatrix(this, &Camera::UpdateProjectionMatrix)
    {
        SetCallbacks();
    }

    Camera::Camera(Camera &&rhs) noexcept
        : name(rhs.name)
        , position(std::move(rhs.position))
        , up(std::move(rhs.up))
        , front(std::move(rhs.front))
        , projection(std::move(rhs.projection))
        , viewMatrix(std::move(rhs.viewMatrix))
        , projectionMatrix(std::move(rhs.projectionMatrix))
        , viewProjectionMatrix(std::move(rhs.viewProjectionMatrix))
        , isViewUpdated(rhs.isViewUpdated)
        , isProjectionUpdated(rhs.isProjectionUpdated)
        , isViewProjectionUpdated(rhs.isViewProjectionUpdated)
        , updateProjectionMatrix(this, &Camera::UpdateProjectionMatrix)
    {
        rhs.ClearCallbacks();
        SetCallbacks();
    }

    Camera::~Camera()
    {
        ClearCallbacks();
    }

    glm::vec3 Camera::GetPosition()
    {
        return position;
    }

    glm::vec3 Camera::GetDirection()
    {
        return front;
    }

    Projection &Camera::GetProjection()
    {
        return projection;
    }

    const std::string &Camera::GetName() const
    {
        return name;
    }

    glm::mat4 Camera::GetViewMatrix()
    {
        if (!isViewUpdated)
        {
            viewMatrix = glm::lookAt(position, position + front, up);
            isViewUpdated = true;
        }
        return glm::lookAt(position, position + front, up);
    }

    glm::mat4 Camera::GetProjectionMatrix()
    {
        if (!isProjectionUpdated)
        {
            projectionMatrix = projection.GetProjectionMatrix();
            isProjectionUpdated = true;
        }
        return projectionMatrix;
    }

    glm::mat4 Camera::GetViewProjectionMatrix()
    {
        if (!isViewProjectionUpdated)
        {
            viewProjectionMatrix = GetProjectionMatrix() * GetViewMatrix();
            isProjectionUpdated = true;
        }
        return viewProjectionMatrix;
    }

    void Camera::SetPosition(const glm::vec3& value)
    {
        position = value;
        isViewUpdated = false;
        isViewProjectionUpdated = false;
    }

    void Camera::SetFront(const glm::vec3& value)
    {
        front = glm::normalize(value);
        isViewUpdated = false;
        isViewProjectionUpdated = false;
    }

    void Camera::SetUp(const glm::vec3 &value)
    {
        up = glm::normalize(value);
        isViewUpdated = false;
        isViewProjectionUpdated = false;
    }

    void Camera::SetProjection(const Projection &value)
    {
        projection = value;
        isProjectionUpdated = false;
        isViewProjectionUpdated = false;
    }

    void Camera::UpdateProjectionMatrix()
    {
        isProjectionUpdated = false;
        isViewProjectionUpdated = false;
    }

    void Camera::SetCallbacks()
    {
        projection.AddListenerOnProjectionUpdated(updateProjectionMatrix);
    }

    void Camera::ClearCallbacks()
    {
        projection.RemoveListenerOnProjectionUpdated(updateProjectionMatrix);
    }
}