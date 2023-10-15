#include "Engine/Main/Engine.h"

namespace Engine
{
    Engine::Engine(Window* const window)
        : modules(new Modules(window->GetInnerWindow()))
    {}

    Engine::~Engine()
    {
        delete modules;
    }

    Modules * const Engine::GetModules()
    {
        return modules;
    }
}