#pragma once

#include <memory>
#include <mutex>
#include "GL/glew.h"
#include "GlFW/glfw3.h"
#include "Engine/Main/Modules.h"
#include "Engine/Main/Window.h"

namespace Engine
{
    class Engine
    {
    public:

        Engine(Window *const window);
        Engine() = delete;
        ~Engine();

    public:
        Modules * const GetModules();

    private:
        Modules * const modules;
    };
}