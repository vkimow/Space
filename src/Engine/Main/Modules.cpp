#include "Engine/Main/Modules.h"

namespace Engine
{
    Modules::Modules(GLFWwindow * window)
        : time()
        , input(window)
        , graphics(window)
    {}

    GraphicsModule &Modules::GetGraphics()
    {
        return graphics;
    }

    TimeModule &Modules::GetTime()
    {
        return time;
    }

    InputModule &Modules::GetInput()
    {
        return input;
    }
}