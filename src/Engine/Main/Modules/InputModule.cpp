#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Engine/Main/Modules/InputModule.h"
#include "Engine/Main/Modules/UIModule.h"

#include "Engine/Input/InputHeader.h"
#include "Engine/Window/Window.h"
#include "Engine/Main/Engine.h"
#include "Engine/Tools/Log/Logger.h"

namespace Engine
{
    InputModule::InputModule(GLFWwindow *const window)
        : scheme(new Input::Scheme(window))
        , isActive(true)
    {
        HandleInput(window);
    };

    InputModule::~InputModule()
    {
        delete scheme;
    }

    void InputModule::PollEvents()
    {
        scheme->UpdateBeforePolling();
        glfwPollEvents();
        scheme->UpdateAfterPolling();
    }

    void InputModule::SetActive(bool value)
    {
        isActive = value;
    }

    Input::Scheme *const InputModule::GetScheme() const
    {
        return scheme;
    }

    bool InputModule::IsActive() const
    {
        return isActive;
    }

    void InputModule::HandleInput(GLFWwindow *const window)
    {
        HandleKeyboard(window);
        HandleMouse(window);
    }

    void InputModule::HandleKeyboard(GLFWwindow *const window)
    {
        glfwSetKeyCallback(window, KeyCallback);
    }

    void InputModule::HandleMouse(GLFWwindow *const window)
    {
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
        glfwSetCursorPosCallback(window, CursorPosCallback);
        glfwSetScrollCallback(window, ScrollCallback);
    }

    void InputModule::KeyCallback(GLFWwindow *glfwWindow, int key, int scancode, int action, int mods)
    {
        Window *const window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
        InputModule *const inputModule = window->GetEngine()->GetInput();
        UIModule *const uiModule = window->GetEngine()->GetUI();
        if (!inputModule->isActive || uiModule->WantCaptureKeyboard())
        {
            return;
        }

        Input::Scheme *const scheme = inputModule->scheme;
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

    void InputModule::MouseButtonCallback(GLFWwindow *glfwWindow, int button, int action, int mods)
    {
        Window *const window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
        InputModule *const inputModule = window->GetEngine()->GetInput();
        UIModule *const uiModule = window->GetEngine()->GetUI();
        if (!inputModule->isActive || uiModule->WantCaptureMouse())
        {
            return;
        }

        Input::Scheme *const scheme = inputModule->scheme;
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

    void InputModule::CursorPosCallback(GLFWwindow *glfwWindow, double xPos, double yPos)
    {
        Window *const window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
        InputModule *const inputModule = window->GetEngine()->GetInput();
        UIModule *const uiModule = window->GetEngine()->GetUI();
        if (!inputModule->isActive || uiModule->WantCaptureMouse())
        {
            return;
        }

        Input::Scheme *const scheme = inputModule->scheme;
        if (scheme->HasMouse())
        {
            auto mouse = scheme->GetMouse();
            mouse->SetPosition(xPos, yPos);
        }
    }

    void InputModule::ScrollCallback(GLFWwindow *glfwWindow, double xOffset, double yOffset)
    {
        Window *const window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
        InputModule *const inputModule = window->GetEngine()->GetInput();
        UIModule *const uiModule = window->GetEngine()->GetUI();
        if (!inputModule->isActive || uiModule->WantCaptureMouse())
        {
            return;
        }

        Input::Scheme *const scheme = inputModule->scheme;
        if (scheme->HasMouse())
        {
            auto mouse = scheme->GetMouse();
            mouse->SetScroll(xOffset, yOffset);
        }
    }
}