#include <GL/glew.h>
#include "Engine/Main/EngineHeader.h"

namespace Engine
{
    Engine::Engine(Window* const window)
        : time(new TimeModule())
        , input(new InputModule(window->GetInnerWindow()))
        , ui(new UIModule(window->GetInnerWindow()))
        , graphics(new GraphicsModule(window))
    {
        window->engine = this;
    }

    Engine::~Engine()
    {
        delete graphics;
        delete ui;
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

    UIModule *const Engine::GetUI()
    {
        return ui;
    }

    InputModule *const Engine::GetInput()
    {
        return input;
    }

    void Engine::StartTick()
    {
        time->Update();
        input->PollEvents();
        ui->NewFrame();
        ui->Update();
    }

    void Engine::EndTick()
    {
    }

    void Engine::StartRender()
    {
        graphics->StartRender();
    }

    void Engine::Render()
    {
        graphics->Render();
        graphics->PostProcessing();
        ui->Render();
    }

    void Engine::EndRender()
    {
        graphics->EndRender();
    }
}