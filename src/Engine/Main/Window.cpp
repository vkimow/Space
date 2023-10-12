#include "Engine/Main/Window.h"
#include "Engine/Tools/Log/Logger.h"

namespace Engine
{
    Window::Window(const char* title, unsigned int width, unsigned int height)
    {
        if (!glfwInit())
        {
            LOG_CRITICAL("GLFW initialisation failed!");
            glfwTerminate();
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!glfwWindow)
        {
            LOG_CRITICAL("GLFW window creation failed!");
            glfwTerminate();
            return;
        }

        glfwSetWindowUserPointer(glfwWindow, this);
        glfwMakeContextCurrent(glfwWindow);
        glewExperimental = GL_TRUE;

        if (glewInit() != GLEW_OK)
        {
            LOG_CRITICAL("GLEW initialisation failed");
            glfwDestroyWindow(glfwWindow);
            glfwTerminate();
            return;
        }

        int framebufferWidth, framebufferHeight;
        glfwGetFramebufferSize(glfwWindow, &framebufferWidth, &framebufferHeight);
        glViewport(0, 0, framebufferWidth, framebufferHeight);

        glfwSetFramebufferSizeCallback(glfwWindow, FramebufferResizeCallback);
        isActive = true;
    }

    Window::~Window()
    {
        glfwDestroyWindow(glfwWindow);
        glfwTerminate();
    }

    void Window::Resize(unsigned int width, unsigned int height)
    {
        glfwSetWindowSize(glfwWindow, width, height);
    }

    void Window::FramebufferResizeCallback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    bool Window::IsActive()
    {
        return isActive;
    }

    GLFWwindow *const Window::GetInnerWindow()
    {
        return glfwWindow;
    }
}