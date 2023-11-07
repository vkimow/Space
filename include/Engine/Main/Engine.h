#pragma once

namespace Engine
{
    class Window;
    class TimeModule;
    class InputModule;
    class UIModule;
    class GraphicsModule;

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

        void StartRender();
        void Render();
        void EndRender();

    private:
        TimeModule *const  time;
        InputModule *const  input;
        UIModule *const ui;
        GraphicsModule *const graphics;
    };
}