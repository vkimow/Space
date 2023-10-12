#include "App.h"

namespace Game
{
    App::App()
        : isActive(false)
        , window("Space", 1280, 720)
        , engine(&window)
    {
        scene = new Scene_1("First Scene", &engine.GetModules());
    }

    App::~App()
    {
        delete scene;
    }

    void App::Start()
    {
        isActive = true;
        while (!ShouldExit())
        {
            engine.GetModules().GetInput().Update();
            engine.GetModules().GetTime().Update();

            scene->Update();

            engine.GetModules().GetGraphics().StartUpdate();
            scene->UpdateVisuals();
            engine.GetModules().GetGraphics().EndUpdate();
        }
    }

    void App::Quit()
    {
        isActive = false;
    }

    bool App::ShouldExit()
    {
        return glfwWindowShouldClose(window.GetInnerWindow()) || !isActive || !window.IsActive();
    }
}