#include "Engine/Main/Window.h"
#include "Engine/Tools/Log/Logger.h"

namespace Engine
{
    int Window::width = 0;
    int Window::height = 0;

    Window::Window(const char* title, unsigned int width, unsigned int height)
        : glfwWindow(nullptr)
        , isTerminated(false)
    {
        if (!glfwInit())
        {
            LOG_CRITICAL("GLFW initialisation failed!");
            TerminateGLFW();
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
            TerminateGLFW();
            return;
        }

        glfwSetWindowUserPointer(glfwWindow, this);
        glfwMakeContextCurrent(glfwWindow);
        glewExperimental = GL_TRUE;

        if (glewInit() != GLEW_OK)
        {
            LOG_CRITICAL("GLEW initialisation failed");
            TerminateGLFW();
            return;
        }

        int framebufferWidth, framebufferHeight;
        glfwGetFramebufferSize(glfwWindow, &framebufferWidth, &framebufferHeight);
        FramebufferResizeCallback(glfwWindow, framebufferWidth, framebufferHeight);
        glfwSetFramebufferSizeCallback(glfwWindow, FramebufferResizeCallback);
    }

    Window::~Window()
    {
        TerminateGLFW();
    }

    void Window::Resize(unsigned int width, unsigned int height)
    {
        glfwSetWindowSize(glfwWindow, width, height);
    }

    glm::ivec2 Window::GetResolution() const
    {
        return glm::ivec2(width, height);
    }

    void Window::TerminateGLFW()
    {
        if (glfwWindow)
        {
            glfwSetWindowUserPointer(glfwWindow, NULL);
            glfwSetFramebufferSizeCallback(glfwWindow, NULL);
            glfwDestroyWindow(glfwWindow);
            glfwWindow = nullptr;
        }

        if (!isTerminated)
        {
            glfwTerminate();
            isTerminated = true;
        }
    }


    void Window::FramebufferResizeCallback(GLFWwindow *glfwWindow, int width, int height)
    {
        Window::width = width;
        Window::height = height;
        glViewport(0, 0, width, height);
        auto window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->OnFramebufferResize(glm::uvec2(width, height));
    }

    GLFWwindow *const Window::GetInnerWindow()
    {
        return glfwWindow;
    }
}