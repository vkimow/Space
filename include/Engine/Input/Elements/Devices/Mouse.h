#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Engine/Tools/Events/Action.h"
#include "Engine/Tools/Events/MemberFunction.h"
#include "Engine/Input/Main/Element.h"

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
        glm::vec2 GetDeltaPosition() const;
        glm::vec2 GetScroll() const;
        float GetHorizontalScroll() const;
        float GetVerticalScroll() const;
        bool IsCursorEnabled();
        void EnableCursor(bool value);

        Vector* const GetPositionInput() const;
        Vector *const GetDeltaPositionInput() const;
        Vector* const GetScrollInput() const;

    private:
        void SetPosition(float x, float y);
        void SetScroll(float horizontal, float vertical);
        void ClearDelta();

    private:
        GLFWwindow * const window;
        Vector *const position;
        Vector *const deltaPosition;
        Vector *const scroll;
        bool isCursorEnabled;
    };
}
