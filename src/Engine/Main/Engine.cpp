#include "Engine/Main/Engine.h"

namespace Engine
{
    Engine::Engine(Window* const window)
        : time(new TimeModule())
        , input(new InputModule(window->GetInnerWindow()))
        , graphics(new GraphicsModule(window->GetInnerWindow()))
    {}

    Engine::~Engine()
    {

        delete graphics;
        delete input;
        delete time;
    }

    GraphicsModule *const Engine::GetGraphics()
    {
        return graphics;
    }

    TimeModule *const Engine::GetTime()
    {
        return time;
    }

    InputModule *const Engine::GetInput()
    {
        return input;
    }
}