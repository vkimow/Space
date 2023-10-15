#include "Engine/Main/Modules/InputModule.h"
#include "Engine/Input/Main/Scheme.h"
#include "Engine/Input/Main/Element.h"
#include "Engine/Input/Elements/Press/PressableKey.h"
#include <vector>


namespace Engine
{
    std::shared_ptr<Input::Scheme> InputModule::scheme = nullptr;

    InputModule::InputModule(GLFWwindow *const window)
        : window(window) 
    {
        scheme = std::make_shared<Input::Scheme>(window);
        HandleInput();
    };

    void InputModule::Update()
    {
        scheme->UpdateBeforePolling();
        glfwPollEvents();
        scheme->UpdateAfterPolling();
    }

    void InputModule::SetScheme(std::shared_ptr<Input::Scheme> scheme)
    {
        this->scheme = scheme;
    }

    std::shared_ptr<Input::Scheme> InputModule::GetScheme()
    {
        return scheme;
    }

    void InputModule::HandleInput()
    {
        HandleKeyboard();
        HandleMouse();
    }

    void InputModule::HandleKeyboard()
    {
        glfwSetKeyCallback(window, KeyCallback);
    }

    void InputModule::HandleMouse()
    {
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
        glfwSetCursorPosCallback(window, CursorPosCallback);
        glfwSetScrollCallback(window, ScrollCallback);
    }

    void InputModule::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if (scheme->ContainsPressableKey(key))
        {
            auto pressableKey = scheme->GetPressableKey(key);

            if (action == GLFW_PRESS)
            {
                pressableKey->Press();
            }
            else if (action == GLFW_RELEASE)
            {
                pressableKey->Release();
            }
        }
    }

    void InputModule::MouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
    {
        if (scheme->ContainsPressableMouse(button))
        {
            auto pressableMouse = scheme->GetPressableMouse(button);

            if (action == GLFW_PRESS)
            {
                pressableMouse->Press();
            }
            else if (action == GLFW_RELEASE)
            {
                pressableMouse->Release();
            }
        }
    }

    void InputModule::CursorPosCallback(GLFWwindow * window, double xPos, double yPos)
    {
        if (scheme->HasMouse())
        {
            auto mouse = scheme->GetMouse();
            mouse->SetPosition(xPos, -yPos);
        }
    }

    void InputModule::ScrollCallback(GLFWwindow * window, double xOffset, double yOffset)
    {
        if (scheme->HasMouse())
        {
            auto mouse = scheme->GetMouse();
            mouse->SetScroll(xOffset, yOffset);
        }
    }
}