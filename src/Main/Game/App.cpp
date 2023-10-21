#include "App.h"

namespace Game
{
    App::App()
        : isActive(false)
        , window(new Engine::Window("Space", 1280, 720))
        , engine(new Engine::Engine(window))
    {
        scene = new Scene_1("First Scene", window, engine->GetModules());
    }

    App::~App()
    {
        delete scene;
        delete engine;
        delete window;
    }

    void App::Start()
    {
        isActive = true;
        while (!ShouldExit())
        {
            engine->GetModules()->GetInput().Update();
            engine->GetModules()->GetTime().Update();

            scene->Update();

            engine->GetModules()->GetGraphics().StartUpdate();
            scene->Render();
            engine->GetModules()->GetGraphics().EndUpdate();

            engine->GetModules()->GetInput().LateUpdate();
        }
    }

    void App::Quit()
    {
        isActive = false;
    }

    bool App::ShouldExit()
    {
        return glfwWindowShouldClose(window->GetInnerWindow()) || !isActive;
    }
}