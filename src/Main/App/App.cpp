#include "App/App.h"
#include "Game/GameHeader.h"

namespace Main
{
    App::App()
        : window("Space", 1280, 720)
        , engine(&window)
        , gameManager(&window, &engine)
    {}

    App::~App()
    {}

    void App::Start()
    {
        while (!ShouldExit())
        {
            engine.StartTick();
            gameManager.Update();
            engine.EndTick();

            engine.StartRender();
            engine.Render();
            gameManager.scene->Render();
            engine.EndRender();
        }
    }

    bool App::ShouldExit()
    {
        return window.ShouldClose();
    }
}