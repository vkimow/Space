#include <GL/glew.h>
#include "Engine/Graphics/Camera/Camera.h"
#include "Engine/Tools/Log/Logger.h"
#include "Engine/Main/Modules/TimeModule.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/ext/quaternion_common.hpp>

namespace Engine::Graphics
{
    const float Camera::TransitionTime = 2.0f;

    Camera::Camera()
        : target(nullptr)
        , viewMatrix()
        , projectionMatrix()
        , inTransition()
        , transitionElapsedTime(0.0f)
        , currentPosition()
        , currentDirection()
        , currentUp()
        , currentProjection()
        , previousPosition()
        , previousDirection()
        , previousUp()
        , previousProjection()
    {}

    Camera::~Camera()
    {}

    const glm::vec3 &Camera::GetPosition() const
    {
        if (inTransition)
        {
            return currentPosition;
        }
        else
        {
            return target->GetPosition();
        }
    }

    const glm::mat4 &Camera::GetViewMatrix() const
    {
        return viewMatrix;
    }

    const glm::mat4 &Camera::GetProjectionMatrix() const
    {
        return projectionMatrix;
    }

    glm::mat4 Camera::GetViewProjectionMatrix() const
    {
        return GetProjectionMatrix() * GetViewMatrix();
    }

    bool Camera::InTransition()
    {
        return inTransition;
    }

    void Camera::SetTarget(IVirtualCamera *value, bool forced)
    {
        if (forced)
        {
            inTransition = false;
        }
        else if (inTransition)
        {
            previousPosition = currentPosition;
            previousDirection = currentDirection;
            previousUp = currentUp;
            previousProjection = currentProjection;
            inTransition = true;
            transitionElapsedTime = 0.0f;
        }
        else if (target)
        {
            previousPosition = target->GetPosition();
            previousDirection = target->GetDirection();
            previousUp = target->GetUp();
            previousProjection = target->GetProjection();
            inTransition = true;
            transitionElapsedTime = 0.0f;
        }

        target = value;
    }

    void Camera::Update()
    {
        if (inTransition)
        {
            transitionElapsedTime += TimeModule::GetDeltaTime();
            float t = transitionElapsedTime / TransitionTime;
            if (transitionElapsedTime >= TransitionTime)
            {
                t = 1.0f;
                inTransition = false;
            }

            t -= 1.0f;
            t = 1.0f - t * t * t * t;
            currentPosition = glm::mix(previousPosition, target->GetPosition(), t);
            currentDirection = glm::mix(previousDirection, target->GetDirection(), t);
            currentUp = glm::mix(previousUp, target->GetUp(), t);
            viewMatrix = glm::lookAt(currentPosition, currentPosition + currentDirection, currentUp);

            float aspectRatio = target->GetProjection().GetAspectRatio();

            float prevFov = previousProjection.GetFov();
            float prevFar = previousProjection.GetFar();
            float prevNear = previousProjection.GetNear();
            float tarFov = target->GetProjection().GetFov();
            float tarFar = target->GetProjection().GetFar();
            float tarNear = target->GetProjection().GetNear();
            float fov = prevFov + ((tarFov - prevFov) * t);
            float far = prevFar + ((tarFar - prevFar) * t);
            float near = prevNear + ((tarNear - prevNear) * t);

            currentProjection = Projection(target->GetProjection().GetAspectRatio(), fov, aspectRatio, near, far);
            projectionMatrix = currentProjection.GetProjectionMatrix();
        }
        else
        {
            if (target->ShouldUpdateView())
            {
                viewMatrix = target->GetViewMatrix();
            }
            if (target->ShouldUpdateProjection())
            {
                projectionMatrix = target->GetProjectionMatrix();
            }
        }
    }

    void Camera::Use(Shader *shader)
    {
        shader->SetMatrix4("View", GetViewMatrix());
        shader->SetMatrix4("Projection", GetProjectionMatrix());
        shader->SetMatrix4("ViewProjection", GetViewProjectionMatrix());
        shader->SetVector3f("EyePosition", GetPosition());
    }
}