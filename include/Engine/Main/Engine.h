#pragma once

#include <memory>
#include "Engine/Main/Modules/ModulesHeader.h"

namespace Engine
{
    class Window;

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
        UIModule *const GetUI();
        InputModule *const GetInput();

    public:
        void StartTick();
        void EndTick();
        void Render();
        void StartRender();
        void EndRender();
        void FullRender();

    private:
        TimeModule *const  time;
        InputModule *const  input;
        UIModule *const ui;
        GraphicsModule *const graphics;
    };
}