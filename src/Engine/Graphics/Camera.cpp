#include "Engine/Graphics/Camera.h"
#include "Engine/Main/Modules/TimeModule.h"
#include "Engine/Tools/Log/Logger.h"

namespace Engine::Graphics
{
    Camera::Camera()
        : position(0.0f)
        , up(0.0f)
        , yaw(0.0f)
        , pitch(0.0f)
        , front(0.0f)
        , worldUp(0.0f)
        , right(0.0f)
        , movementSpeed(0.0f)
        , turnSpeed(0.0f)
        , movementInput(nullptr)
        , rotationInput(nullptr)
    {}

    Camera::Camera(Camera &&rhs) noexcept
        : position(std::move(rhs.position))
        , up(std::move(rhs.up))
        , yaw(std::move(rhs.yaw))
        , pitch(std::move(rhs.pitch))
        , front(std::move(rhs.front))
        , worldUp(std::move(rhs.worldUp))
        , right(std::move(rhs.right))
        , movementSpeed(rhs.movementSpeed)
        , turnSpeed(rhs.turnSpeed)
        , movementInput(rhs.movementInput)
        , rotationInput(rhs.rotationInput)
    {
        rhs.movementInput = nullptr;
        rhs.rotationInput = nullptr;
    }

    Camera &Camera::operator=(Camera && rhs) noexcept
    {
        position = std::move(rhs.position);
        up = std::move(rhs.up);
        yaw = std::move(rhs.yaw);
        pitch = std::move(rhs.pitch);
        front = std::move(rhs.front);
        worldUp = std::move(rhs.worldUp);
        right = std::move(rhs.right);
        movementSpeed = rhs.movementSpeed;
        turnSpeed = rhs.turnSpeed;

        Input::Vector *previousMovementInput = movementInput;
        Input::Vector *previousRotationInput = rotationInput;

        movementInput = rhs.movementInput;
        rotationInput = rhs.rotationInput;

        rhs.movementInput = nullptr;
        rhs.rotationInput = nullptr;

        return *this;
    }

    Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed,
                    Input::Vector *movementInput, Input::Vector *rotationInput)
        : position(position)
        , up(up)
        , yaw(yaw)
        , pitch(pitch)
        , front(glm::vec3(0.0f, 0.0f, -1.0f))
        , worldUp(glm::vec3(0.0f, 1.0f, 0.0f))
        , right(glm::vec3(1.0f, 0.0f, 0.0f))
        , movementSpeed(moveSpeed)
        , turnSpeed(turnSpeed)
        , movementInput(movementInput)
        , rotationInput(rotationInput)
    {}
    
    Camera::~Camera()
    {}

    void Camera::Update()
    {
        if (movementInput && movementInput->IsNotZero())
        {
            UpdatePosition(movementInput->GetVector());
        }
        if (rotationInput && rotationInput->IsNotZero())
        {
            UpdateRotation(rotationInput->GetVector());
        }
    }

    glm::vec3 Camera::GetCameraPosition()
    {
        return position;
    }

    glm::vec3 Camera::GetCameraDirection()
    {
        return front;
    }

    glm::mat4 Camera::GetViewMatrix()
    {
        return glm::lookAt(position, position + front, up);
    }

    void Camera::UpdatePosition(glm::vec2 movement)
    {
        glm::vec2 delta = movement * movementSpeed * TimeModule::GetDeltaTime();
        position += front * movement.y;
        position += right * movement.x;
        LOG_DEBUG("New position = {}.{}.{}", position.x, position.y, position.z);
    }

    void Camera::UpdateRotation(glm::vec2 rotation)
    {
        rotation *= turnSpeed;
        yaw += rotation.x;
        pitch += rotation.y;

        if (pitch > 89.0f)
        {
            pitch = 89.0f;
        }

        if (pitch < -89.f)
        {
            pitch = -89.0f;
        }

        LOG_DEBUG("New Yaw={} and Pitch={}", yaw, pitch);
        UpdateView();
    }

    void Camera::UpdateView()
    {
        front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        front.y = sin(glm::radians(pitch));
        front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        front = glm::normalize(front);

        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
        LOG_DEBUG("Update View");
    }
}