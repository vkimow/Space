#include "Engine/Main/Engine.h"

namespace Engine
{
    Engine::Engine(Window* const window)
        : modules(window->GetInnerWindow())
    {}

    Modules &Engine::GetModules()
    {
        return modules;
    }
}