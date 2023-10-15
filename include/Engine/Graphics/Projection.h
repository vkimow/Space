#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine/Input/InputHeader.h"
#include <type_traits>

namespace Engine
{
    class Window;
}

namespace Engine::Graphics
{
    class Projection
    {

    public:
        Projection();
        Projection(const Projection &rhs) = delete;
        Projection(Projection &&rhs) noexcept;
        Projection &operator=(const Projection &rhs) = delete;
        Projection &operator=(Projection &&rhs) noexcept;

        Projection(Window *const window, float fovDegrees, float aspectRatio, float near, float far);
        Projection(Window *const window, float fovDegrees, float width, float height, float near, float far);
        Projection(Window *const window, float fovDegrees, float near = 0.01f, float far = 100.0f);
        Projection(Window *const window, float fovDegrees, glm::vec2 framebuffer, float near = 0.01f, float far = 100.0f);
        Projection(Window *const window, float fovDegrees, glm::ivec2 framebuffer, float near = 0.01f, float far = 100.0f);

        ~Projection();


    public:
        glm::mat4 GetProjectionMatrix() const;
        float GetFovDegrees() const;
        float GetAspectRatio() const;
        float GetNear() const;
        float GetFar() const;


    public:
        template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        void UpdateFov(T fovDegrees) { this->fovDegrees = static_cast<float>(fovDegrees); UpdateProjection(); }

        template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        void UpdateAspectByFramebuffer(glm::vec<2,T> framebuffer) { UpdateAspect(static_cast<float>(framebuffer.x) / static_cast<float>(framebuffer.y)); UpdateProjection(); }
        template<typename T_1, typename T_2, typename = std::enable_if_t<std::is_arithmetic_v<T_1>>, typename = std::enable_if_t<std::is_arithmetic_v<T_2>>>
        void UpdateAspect(T_1 width, T_2 height) { UpdateAspect(static_cast<float>(width) / static_cast<float>(height)); UpdateProjection(); }
        template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        void UpdateAspect(T aspectRatio) { this->aspectRatio = static_cast<float>(aspectRatio); UpdateProjection(); }

    private:
        void UpdateProjection();

    private:
        Window * window;
        Engine::Tools::Events::MemberFunction<Projection, glm::ivec2> updateAspectByFramebuffer;

    private:
        float fovDegrees;
        float aspectRatio;
        float near;
        float far;

    private:
        glm::mat4 projection;
    };
}