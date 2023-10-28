#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine/Input/InputHeader.h"
#include "Engine/Graphics/Camera/Projection.h"

namespace Engine::Graphics
{
    class Camera
    {
        friend class CameraManager;

    private:
        Camera() = delete;
        Camera(const std::string &name);
        Camera(const std::string &name, glm::vec3 position);
        Camera(const std::string &name, const Projection &projection);
        Camera(const std::string &name, glm::vec3 position, const Projection &projection);

        Camera(const Camera &rhs);
        Camera(Camera &&rhs) noexcept;
        ~Camera();

    public:
        Camera &operator=(const Camera &rhs) = delete;
        Camera &operator=(Camera &&rhs) noexcept = delete;

    public:
        glm::vec3 GetPosition();
        glm::vec3 GetDirection();
        Projection &GetProjection();
        const std::string &GetName() const;

    public:
        glm::mat4 GetViewMatrix();
        glm::mat4 GetProjectionMatrix();
        glm::mat4 GetViewProjectionMatrix();

    public:
        void SetPosition(const glm::vec3 &value);
        void SetFront(const glm::vec3 &value);
        void SetUp(const glm::vec3 &value);
        void SetProjection(const Projection &value);

    private:
        void UpdateProjectionMatrix();
        ::Engine::Tools::Events::MemberFunction<Camera, void> updateProjectionMatrix;

    private:
        void SetCallbacks();
        void ClearCallbacks();

    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;

    private:
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::mat4 viewProjectionMatrix;

        bool isViewUpdated;
        bool isProjectionUpdated;
        bool isViewProjectionUpdated;

    private:
        const std::string name;
        Projection projection;
    };
}