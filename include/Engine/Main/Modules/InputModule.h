#pragma once

struct GLFWwindow;
namespace Engine
{
    namespace Input
    {
        class Scheme;
        class Element;
    }

    class  InputModule final
    {
        friend class Input::Element;
        friend class Engine;

    private:
        InputModule(GLFWwindow *const window);
        InputModule() = delete;
        InputModule(const InputModule &rhs) = delete;
        InputModule(InputModule &&rhs) = delete;
        InputModule &operator=(const InputModule &rhs) = delete;
        InputModule &operator=(InputModule &&rhs) = delete;
        ~InputModule();

    private:
        void PollEvents();

    private:
        void SetActive(bool value);

    public:
        Input::Scheme *const GetScheme() const;
        bool IsActive() const;

    private:
        void HandleInput(GLFWwindow *const window);
        void HandleKeyboard(GLFWwindow *const window);
        void HandleMouse(GLFWwindow *const window);

        static void KeyCallback(GLFWwindow *glfwWindow, int key, int scancode, int action, int mods);
        static void MouseButtonCallback(GLFWwindow *glfwWindow, int button, int action, int mods);
        static void CursorPosCallback(GLFWwindow *glfwWindow, double xPos, double yPos);
        static void ScrollCallback(GLFWwindow *glfwWindow, double xOffset, double yOffset);

    private:
        Input::Scheme* const scheme;
        bool isActive;
    };
}