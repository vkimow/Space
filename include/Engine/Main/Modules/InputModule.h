#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include <memory>


namespace Game
{
    class App;
}

namespace Engine
{
    namespace Input
    {
        class Scheme;
        class Element;
    }

    class  InputModule final
    {
        friend class Game::App;
        friend class Input::Element;
        friend class Engine;

    private:
        InputModule(GLFWwindow *const window);
        InputModule() = delete;
        InputModule(const InputModule &rhs) = delete;
        InputModule(InputModule &&rhs) = delete;
        InputModule &operator=(const InputModule &rhs) = delete;
        InputModule &operator=(InputModule &&rhs) = delete;

    private:
        void Update();
        void LateUpdate();

    public:
        void SetScheme(std::shared_ptr<Input::Scheme> scheme);
        std::shared_ptr<Input::Scheme> GetScheme();

    private:
        void HandleInput();
        void HandleKeyboard();
        void HandleMouse();

        static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
        static void CursorPosCallback(GLFWwindow *window, double xPos, double yPos);
        static void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset);

    private:
        GLFWwindow * const window;
        static std::shared_ptr<Input::Scheme> scheme;
    };
}