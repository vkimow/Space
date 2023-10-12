#include "Engine/Input/Elements/Devices/Mouse.h"
#include "Engine/Input/Elements/Vector/Vector.h"
#include "GLFW/glfw3.h"

namespace Engine::Input
{
    Mouse::Mouse(GLFWwindow* window)
        : window(window)
        , position(new Vector())
        , scroll(new Vector())
    {
        SetCallbacks();
        EnableCursor(true);
    }

    Mouse::~Mouse()
    {
        RemoveCallbacks();
        delete position;
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
        if (value)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }

    void Mouse::SetPosition(float x, float y)
    {
        position->ChangeVector(x, y);
    }

    void Mouse::SetScroll(float horizontal, float vertical)
    {
        scroll->ChangeVector(horizontal, vertical);
    }

    void Mouse::SetCallbacks()
    {
        position->AddListenerOnVectorChange(&OnPositionChange);
        scroll->AddListenerOnVectorChange(&OnScrollChange);
    }

    void Mouse::RemoveCallbacks()
    {
        position->RemoveListenerOnVectorChange(&OnPositionChange);
        scroll->RemoveListenerOnVectorChange(&OnScrollChange);
    }
}

