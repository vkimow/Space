#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Engine/Tools/Events/EventsHeader.h"

namespace Engine
{
    class Window final
    {
    public:
        Window(const char *title, unsigned int width, unsigned int height);
        Window() = delete;
        Window(const Window &rhs) = delete;
        Window(Window &&rhs) = delete;
        Window &operator=(const Window &rhs) = delete;
        Window &operator=(Window &&rhs) = delete;

        ~Window();

    public:
        GLFWwindow *const GetInnerWindow();

    public:
        void Resize(unsigned int width, unsigned int height);
        glm::ivec2 GetResolution() const;

    private:
        void TerminateGLFW();

    private:
        static void FramebufferResizeCallback(GLFWwindow *window, int width, int height);

    public:
        CREATE_ACTION(glm::ivec2, OnFramebufferResize);

    private:
        bool isTerminated;
        GLFWwindow *glfwWindow;

    private:
        static int width;
        static int height;
    };
}
