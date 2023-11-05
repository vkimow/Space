#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine/Input/InputHeader.h"
#include "Engine/Graphics/Camera/Projection.h"
#include "Engine/Graphics/Camera/IVirtualCamera.h"
#include "Engine/Graphics/Elements/Shader.h"

namespace Engine::Graphics
{
    class Camera
    {
        friend class CameraManager;

    private:
        Camera();
        ~Camera();

    public:
        Camera(const Camera &rhs) = delete;
        Camera(Camera &&rhs) noexcept = delete;
        Camera &operator=(const Camera &rhs) = delete;
        Camera &operator=(Camera &&rhs) noexcept = delete;

    public:
        const glm::vec3 &GetPosition() const;
        const glm::mat4& GetViewMatrix() const;
        const glm::mat4 &GetProjectionMatrix() const;
        glm::mat4 GetViewProjectionMatrix() const;
        bool InTransition();

    public:
        void SetTarget(IVirtualCamera *value, bool forced = false);
        void Update();
        void Use(Shader *shader);

    private:
        IVirtualCamera *target;

    private:
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;

    private:
        bool inTransition;
        float transitionElapsedTime;
        static const float TransitionTime;

    private:
        glm::vec3 currentPosition;
        glm::vec3 currentDirection;
        glm::vec3 currentUp;
        Projection currentProjection;
        glm::vec3 previousPosition;
        glm::vec3 previousDirection;
        glm::vec3 previousUp;
        Projection previousProjection;

    };
}