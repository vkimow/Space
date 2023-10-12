#pragma once

#include <glm/glm.hpp>
#include "Engine/Tools/Events/Action.h"
#include "Engine/Tools/Events/MemberFunction.h"
#include "Engine/Input/Main/Element.h"
#include "GLFW/glfw3.h"

namespace Engine::Input
{
    class Vector;

    class Mouse : Element
    {
        friend class InputModule;
        friend class Scheme;

    private:
        Mouse(GLFWwindow* const window);
        Mouse() = delete;
        ~Mouse();

    public:
        glm::vec2 GetPosition() const;
        glm::vec2 GetScroll() const;
        float GetHorizontalScroll() const;
        float GetVerticalScroll() const;
        bool IsCursorEnabled();
        void EnableCursor(bool value);

    private:
        void SetPosition(float x, float y);
        void SetScroll(float horizontal, float vertical);
        void SetCallbacks();
        void RemoveCallbacks();

    public:
        CREATE_ACTION(glm::vec2, OnPositionChange)
        CREATE_ACTION(glm::vec2, OnScrollChange)

    private:
        GLFWwindow * const window;
        Vector *const position;
        Vector *const scroll;
        bool isCursorEnabled;
    };
}
