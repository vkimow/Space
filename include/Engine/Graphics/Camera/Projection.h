#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <type_traits>
#include "Engine/Tools/Events/Action.h"
#include "Engine/Tools/Events/MemberFunction.h"
#include "Engine/Window/Window.h"

namespace Engine::Graphics
{
    class Projection
    {

    public:
        Projection();
        Projection(Window *const window);
        Projection(const Projection &rhs);
        Projection(Projection &&rhs) noexcept;
        Projection &operator=(const Projection &rhs);
        Projection &operator=(Projection &&rhs) noexcept;

        Projection(Window *const window, float fovDegrees = 90.0f, float near = 0.01f, float far = 100.0f);
        Projection(float fovDegrees, float width, float height, float near = 0.01f, float far = 100.0f);
        Projection(float fovDegrees, glm::vec2 framebuffer, float near = 0.01f, float far = 100.0f);

        ~Projection();

    public:
        glm::mat4 GetProjectionMatrix() const;
        float GetFov() const;
        float GetFovInDegrees() const;
        float GetAspectRatio() const;
        float GetNear() const;
        float GetFar() const;

    public:
        template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        void SetFov(T value) { fov = static_cast<float>(value); OnProjectionUpdated(); }
        template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        void SetFovInDegrees(T value) { SetFov(glm::radians(static_cast<float>(value))); }
        template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        void SetAspect(glm::vec<2, T> frame) { SetAspect(static_cast<float>(frame.x) / static_cast<float>(frame.y)); }
        template<typename T_1, typename T_2, typename = std::enable_if_t<std::is_arithmetic_v<T_1>>, typename = std::enable_if_t<std::is_arithmetic_v<T_2>>>
        void SetAspect(T_1 width, T_2 height) { SetAspect(static_cast<float>(width) / static_cast<float>(height)); }
        template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        void SetAspect(T value) { aspectRatio = static_cast<float>(value); OnProjectionUpdated(); }
        template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        void SetNear(T value) { near = static_cast<float>(value); OnProjectionUpdated(); }
        template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        void SetFar(T value) { far = static_cast<float>(value); OnProjectionUpdated(); }

    private:
        Tools::Events::MemberFunction<Projection, glm::ivec2> setAspect;
        CREATE_ACTION(void, OnProjectionUpdated);

    private:
        Window *const window;
        float fov;
        float aspectRatio;
        float near;
        float far;
    };
}