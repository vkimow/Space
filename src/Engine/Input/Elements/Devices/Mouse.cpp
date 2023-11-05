#include "Engine/Input/Elements/Devices/Mouse.h"
#include "Engine/Input/Elements/Vector/Vector.h"
#include "Engine/Tools/Log/Logger.h"

namespace Engine::Input
{
    Mouse::Mouse(GLFWwindow* window)
        : window(window)
        , position(new Vector())
        , deltaPosition(new Vector())
        , scroll(new Vector())
    {
        EnableCursor(true);
    }

    Mouse::~Mouse()
    {
        delete position;
        delete deltaPosition;
        delete scroll;
    }

    glm::vec2 Mouse::GetPosition() const
    {
        return position->GetVector();
    }

    glm::vec2 Mouse::GetScroll() const
    {
        return scroll->GetVector();
    }

    glm::vec2 Mouse::GetDeltaPosition() const
    {
        return deltaPosition->GetVector();
    }

    float Mouse::GetHorizontalScroll() const
    {
        return scroll->GetVector().x;
    }

    float Mouse::GetVerticalScroll() const
    {
        return scroll->GetVector().y;
    }

    bool Mouse::IsCursorEnabled()
    {
        return isCursorEnabled;
    }

    void Mouse::EnableCursor(bool value)
    {
        isCursorEnabled = value;
        if (value)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }

    Vector *const Mouse::GetPositionInput() const
    {
        return position;
    }

    Vector *const Mouse::GetDeltaPositionInput() const
    {
        return deltaPosition;
    }

    Vector *const Mouse::GetScrollInput() const
    {
        return scroll;
    }

    void Mouse::SetPosition(float x, float y)
    {
        glm::vec2 newPos(x, y);
        glm::vec2 previousPos = position->GetVector();
        position->ChangeVector(newPos);
        deltaPosition->ChangeVector(newPos.x - previousPos.x, previousPos.y - newPos.y);
    }

    void Mouse::SetScroll(float horizontal, float vertical)
    {
        scroll->ChangeVector(horizontal, vertical);
    }
    void Mouse::ClearDelta()
    {
        if (deltaPosition->IsNotZero())
        {
            deltaPosition->ChangeVector(0.0f, 0.0f);
        }
    }
}

