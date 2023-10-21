#pragma once

#include <memory>
#include <mutex>
#include "GL/glew.h"
#include "GlFW/glfw3.h"
#include "Engine/Main/Window.h"
#include "Engine/Main/Modules/ModulesHeader.h"

namespace Engine
{
    class Engine
    {
    public:

        Engine(Window *const window);
        Engine() = delete;
        Engine(const Engine &rhs) = delete;
        Engine(Engine &&rhs) = delete;
        Engine &operator=(const Engine &rhs) = delete;
        Engine &operator=(Engine &&rhs) = delete;
        ~Engine();

    public:
        GraphicsModule *const GetGraphics();
        TimeModule *const GetTime();
        InputModule *const GetInput();

    private:
        TimeModule *const  time;
        InputModule *const  input;
        GraphicsModule *const graphics;
    };
}