#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <type_traits>
#include "Engine/Tools/Events/Action.h"

namespace Engine::Graphics
{
    class Projection
    {

    public:
        Projection();
        Projection(const Projection &rhs);
        Projection(Projection &&rhs) noexcept;
        Projection &operator=(const Projection &rhs);
        Projection &operator=(Projection &&rhs) noexcept;

        Projection(float fovDegrees, float aspectRatio, float near, float far);
        Projection(float fovDegrees, float width, float height, float near, float far);
        Projection(float fovDegrees, float near = 0.01f, float far = 100.0f);
        Projection(float fovDegrees, glm::vec2 framebuffer, float near = 0.01f, float far = 100.0f);
        Projection(float fovDegrees, glm::ivec2 framebuffer, float near = 0.01f, float far = 100.0f);

        ~Projection();

    public:
        glm::mat4 GetProjectionMatrix() const;
        float GetFovDegrees() const;
        float GetAspectRatio() const;
        float GetNear() const;
        float GetFar() const;

    public:
        template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        void UpdateFov(T fovDegrees) { this->fovDegrees = static_cast<float>(fovDegrees); OnProjectionUpdated(); }
        template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        void UpdateAspectByFramebuffer(glm::vec<2,T> framebuffer) { UpdateAspect(static_cast<float>(framebuffer.x) / static_cast<float>(framebuffer.y));}
        template<typename T_1, typename T_2, typename = std::enable_if_t<std::is_arithmetic_v<T_1>>, typename = std::enable_if_t<std::is_arithmetic_v<T_2>>>
        void UpdateAspect(T_1 width, T_2 height) { UpdateAspect(static_cast<float>(width) / static_cast<float>(height));}
        template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        void UpdateAspect(T aspectRatio) { this->aspectRatio = static_cast<float>(aspectRatio); OnProjectionUpdated(); }
        template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        void UpdateNear(T near) { this->near = static_cast<float>(near); OnProjectionUpdated(); }
        template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        void UpdateFar(T far) { this->far = static_cast<float>(far); OnProjectionUpdated(); }

    private:
        CREATE_ACTION(void, OnProjectionUpdated);

    private:
        float fovDegrees;
        float aspectRatio;
        float near;
        float far;
    };
}