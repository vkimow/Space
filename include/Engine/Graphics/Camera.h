#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine/Input/InputHeader.h"

namespace Engine::Graphics
{
    class Camera
    {

    public:
        Camera();
        Camera(const Camera &rhs) = delete;
        Camera &operator=(const Camera &rhs) = delete;
        Camera(Camera &&rhs) noexcept;
        Camera &operator=(Camera &&rhs) noexcept;
        Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed,
                Input::Vector* movementInput, Input::Vector* rotationInput);
        ~Camera();

    public:
        void Update();

    public:
        glm::vec3 GetCameraPosition();
        glm::vec3 GetCameraDirection();
        glm::mat4 GetViewMatrix();

    private:
        void UpdatePosition(glm::vec2 movement);
        void UpdateRotation(glm::vec2 rotation);
        void UpdateView();

    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;

        GLfloat yaw;
        GLfloat pitch;

    private:
        GLfloat movementSpeed;
        GLfloat turnSpeed;
        Input::Vector *movementInput;
        Input::Vector *rotationInput;
    };
}